#include <iostream>
#include <vector>
#include <thread>

using namespace std;


/*
 	1. 为什么能把 shared_ptr 赋值给 weak_ptr ?
 	2. 为什么 shared_ptr 赋值给 weak_ptr 后，原有对象的引用计数不会改变？
 	3. shared_ptr 赋值操作会是对象引用计数加1， 赋值操作的过程中到底发生了什么？

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
