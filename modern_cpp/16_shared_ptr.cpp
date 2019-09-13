/*
 * @Author: liuyanan 
 * @Date: 2019-09-13 17:32:17 
 * @Last Modified by: liuyanan
 * @Last Modified time: 2019-09-13 18:40:12
 */

#include <iostream>
#include <map>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;


/*
TODO: 智能指针多线程安全问题
1. 对于指向同一个 object 的 不同shared_ptr， 其引用计数的变化是安全的
2. 对于 相同的以个 shared_ptr， 多线程对其修改时，是不安全的，会引发问题


第一个问题源码实现 (为什么不同的shared_ptr指针引用计数是安全的)
    1. shared_ptr中，实际实现引用计数的是这 成员 __shared_weak_count* __cntrl_;
    2. 也就是 在shared_ptr拷贝构造函数中，会调用
        shared_ptr<_Tp>::shared_ptr(const shared_ptr& __r) _NOEXCEPT
            : __ptr_(__r.__ptr_),
            __cntrl_(__r.__cntrl_)
        {
            if (__cntrl_)
                __cntrl_->__add_shared();
        }
    3. 最终会调用到  __libcpp_atomic_refcount_increment()函数，
        而这个函数会根据是否开启了多线程来选择使用 __atomic_add_fetch 还是 普通的 +1

第二个问题（为什么同一个shared_ptr修改是不安全的）
    1. 可以看到, 一个shared_ptr 的 构造包括 两个步骤
        一是， 复制 __ptr__ 本身，就是对象真正的地址
        一是， 复制 __cntrl__, 这个是用来计数的对象
    2. 在多线程中修改同一个 shared_ptr 时，这两个步骤 **极有可能** 不是一个原子操作
        这就可能导致，用的是一个对象的地址，而对应的却是另一个对象的计数，就会出问题

    template<class _Tp>
    template<class _Yp>
    shared_ptr<_Tp>::shared_ptr(const weak_ptr<_Yp>& __r,
                                typename enable_if<is_convertible<_Yp*, element_type*>::value, __nat>::type)
        : __ptr_(__r.__ptr_),
        __cntrl_(__r.__cntrl_ ? __r.__cntrl_->lock() : __r.__cntrl_)
    {
        if (__cntrl_ == 0)
            __throw_bad_weak_ptr();
    } 

补充:
    在boost <= 1.4.6 时，对智能指针进行hash，只能获得true 和 false 两个值
    如果 shared_ptr 做为 unorder_map（真正的hah， 而不是map(tree)）时， unorderd_map就会退化成链表
    https://stackoverflow.com/questions/6404765/c-shared-ptr-as-unordered-sets-key/12122314#12122314
*/


class Info {
public:
    Info() { cout << "Info Constructor" << endl;}
    ~Info() { cout << "Info Destructor" << endl; }
private:
    int data;
};
typedef shared_ptr<Info> InfoPtr;


map<int/*id*/, InfoPtr> g_infos;


void thread_func()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    InfoPtr p_info =  g_infos[1];
    InfoPtr p_info2 =  g_infos[1];

    cout << "thread: get info from map, use conunt:" << p_info.use_count() << endl;

    g_infos.erase(1);
    cout << "thread: map erase info, use conunt:" << p_info.use_count() << endl;
}


int main(int argc, char const *argv[])
{
    InfoPtr p_info(new Info);
    cout << "main: fiirst create info, use conunt:" << p_info.use_count() << endl;
    g_infos[1] = p_info; 

    // p_info.reset(); 释放当前的ownershiip

    std::thread t1(thread_func);

    t1.join();

    cout << "main: after thread exit, use conunt:" << p_info.use_count() << endl;

    return 0;
}
