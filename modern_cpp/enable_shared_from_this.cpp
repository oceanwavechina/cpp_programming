/*
 * @Author: liuyanan 
 * @Date: 2019-08-19 18:27:30 
 * @Last Modified by: liuyanan
 * @Last Modified time: 2019-08-19 20:58:11
 */

#include <memory>
#include <iostream>

using namespace std;


/*
这个模板的机制就是从 this 得到一个 shared_ptr：

1. 为什么不直接返回 this ?
	因为 this 是底层具体对象实例，而 share_ptr 是一个 wrapper，用来自动管理 this 的周期

2. 为什么不能返回 shared_ptr(this)？
	首先，每次调用 shared_ptr(this)，相当于创建一个新的 shared_ptr 对象，新的意思是，底层的计数器会new一个新的对象
	想想调用多次的情况，就会生成多个计数器，每个计数器都像控制这个this 对象。但是这些计数器有不相关

	要知道 share_ptr 实现的原理是：多个share_ptr对象底层共享一个 计数器，这样才能生效
	要是多个 share_ptr 对象不共享计数器，那当一个释放的时候，其他的 share_ptr 就成了炸弹



template<class _Tp>
class _LIBCPP_TEMPLATE_VIS enable_shared_from_this
{
    mutable weak_ptr<_Tp> __weak_this_;
protected:
    enable_shared_from_this() _NOEXCEPT {}
    enable_shared_from_this(enable_shared_from_this const&) _NOEXCEPT {}
    enable_shared_from_this& operator=(enable_shared_from_this const&) _NOEXCEPT
        {return *this;}
    ~enable_shared_from_this() {}
public:
    shared_ptr<_Tp> shared_from_this()
        {return shared_ptr<_Tp>(__weak_this_);}
    shared_ptr<_Tp const> shared_from_this() const
        {return shared_ptr<const _Tp>(__weak_this_);}

    template <class _Up> friend class shared_ptr;
};

可以看到这个模板的实现就是通过封装该对象的 一个weak_ptr，之后所有需要得到改对象指针的地方动从这个__weak_this__ 转换得来
转换到额方法，就是在share_ptr 这个类中把生成的share_ptr的指针， 传递给了 __e 的 __weak_this__ 对象，
这也就是为什么 enable_shared_from_this 中要把 class shared_ptr 声明成 friend类型了

typename enable_if<is_convertible<_OrigPtr*, const enable_shared_from_this<_Yp>* >::value, void>::type
__enable_weak_this(const enable_shared_from_this<_Yp>* __e, _OrigPtr* __ptr) _NOEXCEPT
{
    typedef typename remove_cv<_Yp>::type _RawYp;
    if (__e && __e->__weak_this_.expired())
    {
        __e->__weak_this_ = shared_ptr<_RawYp>(*this,
            const_cast<_RawYp*>(static_cast<const _Yp*>(__ptr)));
    }
}

理解这个实现，还要知道weak_ptr的机制，这个
std::weak_ptr is a smart pointer that holds a non-owning ("weak") reference to 
    an object that is managed by std::shared_ptr. 
It must be converted to std::shared_ptr in order to access the referenced object.

*/

struct Good: public std::enable_shared_from_this<Good>
{
    shared_ptr<Good> getptr() {
        return shared_from_this();
    }
//private:
    Good() {}

};

struct Bad {
    shared_ptr<Bad> getptr() {
    	/*

    	 */
        return shared_ptr<Bad>(this);
    }
    ~Bad() {
        cout << "Bad::~Bad() called!\n";
    }
};

int main(int argc, char const *argv[])
{
    /* 这里的两个shared_ptr指向了同一个对象，并且对象的计数器是一个
        不会造成一个其中一个指针析构时，造成对象被删除，从而造成安全问题

       也就是这样的情况：
		   shared_ptr \
						 counter -> object
		   shared_ptr /

    */
    std::shared_ptr<Good> gp1 = std::make_shared<Good>();
    std::shared_ptr<Good> gp2 = gp1->getptr();
    cout << "gp2.use_count():" << gp2.use_count() << "\n\n";

#if 0
    try{
        Good not_so_good;
        cout << "before called getptr" << "\n";
        shared_ptr<Good> gp1 = not_so_good.getptr();
        
        // 下边的语句没有执行， getptr执行失败了, 
        // 说明 enable_shared_from_this 模板中的对象没有初始化成功
        cout << "after called getptr" << "\n";
    } catch(bad_weak_ptr& e) {
        cout << "exception:" << e.what() << "\n\n";
    }
#endif


    /* 这里的两个shared_ptr指向了同一个对象，并且有两个 计数器
        其中一个shared_ptr 释放了对象，另个就成了炸弹

       也就是这样的情况：
		   shared_ptr - counter  \
									object
		   shared_ptr - counter  /

    */
    shared_ptr<Bad> bp1 = make_shared<Bad>();
    shared_ptr<Bad> bp2 = bp1->getptr();
    cout << "bp1.use_count():" << bp2.use_count() << "\n\n";

    return 0;
}
/*
 程序在返回时，出现如下错误
14_pointers(26889,0x1131735c0) malloc: *** error for object 0x7ffc8f400658: pointer being freed was not allocated
14_pointers(26889,0x1131735c0) malloc: *** set a breakpoint in malloc_error_break to debug
fish: './14_pointers' terminated by signal SIGABRT (Abort)

只打印了一次  Bad::~Bad() called! ，说明 这个对象被释放了两次 
*/
