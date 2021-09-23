#include <iostream>
#include <vector>
#include <thread>

using namespace std;


/*
 	1. 为什么能把 shared_ptr 赋值给 weak_ptr ?
 	2. 为什么 shared_ptr 赋值给 weak_ptr 后，原有对象的引用计数不会改变？
 	3. weak_ptr 的 lock 操作的逻辑是什么？
 	3. weak_ptr 和 shared_ptr 的区别是什么？

	问题 1：
 	 	这是因为 weak_ptr 类里边实现了对应的赋值构造函数：
			weak_ptr<_Tp>::operator=(shared_ptr<_Yp> const& __r) _NOEXCEPT
			{
				weak_ptr(__r).swap(*this);
				return *this;
			}
		这个函数通过 shared_ptr 构造出一个 weak_ptr， 然后返回


	问题 2：
		根据问题 1 的答案，当通过 shared_ptr 转成 weak_ptr 的时候，是不会改变对象引用计数的。
			weak_ptr<_Tp>::weak_ptr(shared_ptr<_Yp> const& __r,
                        typename enable_if<is_convertible<_Yp*, _Tp*>::value, __nat*>::type)
                         _NOEXCEPT
				: __ptr_(__r.__ptr_),
				  __cntrl_(__r.__cntrl_)
			{
				if (__cntrl_)
					__cntrl_->__add_weak();
			}

		注意上边的 __cntrl_->__add_weak(); 是 add_weak， 不会改变对象引用计数
		    void __add_weak() _NOEXCEPT {
				__libcpp_atomic_refcount_increment(__shared_weak_owners_);
    		}

    	注意上边 incremnt 的是 __shared_weak_owners_

    问题 3：
		weak_ptr 的lock 操作实现如下：
			template<class _Tp>
			shared_ptr<_Tp>
			weak_ptr<_Tp>::lock() const _NOEXCEPT
			{
				shared_ptr<_Tp> __r;
				__r.__cntrl_ = __cntrl_ ? __cntrl_->lock() : __cntrl_;
				if (__r.__cntrl_)
					__r.__ptr_ = __ptr_;
				return __r;
			}

			可以看到返回的是一个临时的 shared_ptr<_Tp> 对象，这个对象会根据引用计数器是否还在(对象没有被释放)，来确定shared_ptr 中的 __ptr_ 是否有效
			这也就说明了为什么lock 返回值可能是空对象

	问题 4：
		shared_ptr uses an extra "counter" object (aka. "shared count" or "control block") to store the reference count.
		(BTW: that "counter" object also stores the deleter.)

		Every shared_ptr and weak_ptr contains a pointer to the actual pointee, and a second pointer to the "counter" object.

		To implement weak_ptr, the "counter" object stores two different counters:

			The "use count" is the number of shared_ptr instances pointing to the object.
			The "weak count" is the number of weak_ptr instances pointing to the object, plus one if the "use count" is still > 0.

		The pointee is deleted when the "use count" reaches zero.

		The "counter" helper object is deleted when the "weak count" reaches zero (which means the "use count" must also be zero, see above).

		When you try to obtain a shared_ptr from a weak_ptr, the library atomically checks the "use count", and if it's > 0 increments it.
		If that succeeds you get your shared_ptr.
		If the "use count" was already zero you get an empty shared_ptr instance instead.

		EDIT:
			Now, why do they add one to the weak count instead of just releasing the "counter" object when both counts drop to zero? Good question.

			The alternative would be to delete the "counter" object when both the "use count" and the "weak count" drop to zero.

			Here's the first reason:
				Checking two (pointer sized) counters atomically is not possible on every platform,
				and even where it is, it's more complicated than checking just one counter.

			Another reason is that
				the deleter must stay valid until it has finished executing.
				Since the deleter is stored in the "counter" object, that means the "counter" object must stay valid.
				Consider what could happen if there is one shared_ptr and one weak_ptr to some object,
				and they are reset at the same time in concurrent threads.
				Let's say the shared_ptr comes first.
				It decreases the "use count" to zero, and begins executing the deleter.
				Now the weak_ptr decreases the "weak count" to zero, and finds the "use count" is zero as well.
				So it deletes the "counter" object, and with it the deleter. While the deleter is still running.

			Of course there would be different ways to assure that the "counter" object stays alive,
			but I think increasing the "weak count" by one is a very elegant and intuitive solution.
			The "weak count" becomes the reference count for the "counter" object.
			And since shared_ptrs reference the counter object too, they too have to increment the "weak count".

			A probably even more intuitive solution would be to increment the "weak count" for every single shared_ptr,
			since every single shared_ptr hold's a reference to the "counter" object.

			Adding one for all shared_ptr instances is just an optimization
			(saves one atomic increment/decrement when copying/assigning shared_ptr instances).

 */


class A;
class B;
class A2;
class B2;

class A {
public:
	~A() {
		cout << "A destroyed" << endl;
	}

	shared_ptr<B> peer;	// 这里用 shared_ptr hold B
};

class B {
public:
	~B() {
		cout << "B destroyed" << endl;
	}

	shared_ptr<A> peer;	// 这里用 shared_ptr hold A
};


class A2 {
public:
	~A2() {
		cout << "A2 destroyed" << endl;
	}

	shared_ptr<B2> peer;	// 这里用 shared_ptr hold B
};

class B2 {
public:
	~B2() {
		cout << "WeakB destroyed" << endl;
	}

	weak_ptr<A2> peer;	// 这里用 weak_ptr hold A
};

int main(int argc, char const *argv[])
{
	cycle_ref: {
		cout << "we enterd cycle_ref block" << endl;

		shared_ptr<B> p_b = make_shared<B>();
		shared_ptr<A> p_a = make_shared<A>();
		cout << "after create ref_count(A): " << p_a.use_count() << endl;

		// 建立循环引用
		p_a->peer = p_b;
		p_b->peer = p_a;
		cout << "after ref by p_b ref_count(A): " << p_a.use_count() << endl;
	}
	cout << "we are out of cycle_ref block" << endl << endl;
	/*
	 	 到目前，程序结束的话，p_a, p_b 都不会被释放， 为什么会这样。
	 	 	 1. 首先当我们通过 make_shared<>() 创建完对象后的 p_a，的引用计数是1
	 	 	 2. 当被 p_b 引用后（即 p_b->_ptr_a = p_a;）, p_a 的引用计数变成了2
	 	 	 3. 同理， p_a 也是
	 	 	 4. 当 cycle_ref block 结束后，会释放 p_a, p_b, 此时各自的引用计数减一，
	 	 	 	 并没有归零所以两个对象不能被释放
	 */


	/* ******************************************************************************** */


	break_ref: {
		cout << "we enterd break_ref block" << endl;

		shared_ptr<B2> p_b = make_shared<B2>();
		shared_ptr<A2> p_a = make_shared<A2>();
		cout << "after create ref_count(A2): " << p_a.use_count() << endl;

		// 建立循环引用
		p_a->peer = p_b;
		p_b->peer = p_a;
		cout << "after ref by p_b ref_count(A2): " << p_a.use_count() << endl;
	}
	cout << "we are out of break_ref block" << endl << endl;
	/*
	 	 跟第一个例子的区别：
	 	 	这里的 p_b->pear = p_a 这个操作， 并不会改变 p_a 的引用计数
	 */

	/* ******************************************************************************** */

	weak_ptr<B> p_weak;
	{
		shared_ptr<B> p_b = make_shared<B>();
		p_weak = p_b;
		if(p_weak.lock()) {
			cout << "p_weak holding object" << endl;
		}
	}
	shared_ptr<B> p_share = p_weak.lock();
	assert( p_share == nullptr);
	if(p_share == nullptr) {
		cout << "after shared_ptr released, p_weak did not hold object" << endl << endl;
	}





	this_thread::sleep_for(200s);

    return 0;
}
