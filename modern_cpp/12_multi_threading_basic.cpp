#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <fstream>


using namespace std;

class A{
public:
    ~A() {
        cout << "A's destructor" << endl;
    }
};


void runner() 
{
    // 内存泄露了
    A* leak = new A;

    for (int i=0; i< 3; ++i) {
        cout << "func run" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

class Functor{
public:
    void operator()(string msg) {
        for (int i=0; i<3; ++i) {
            cout << msg << " from thread: "<< this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
        msg = "modified by thread:";
    }
};

int main(int argc, char const *argv[])
{
    system("sleep 2");

    /*
        detach 线程，使得子线程不在被其他线程等待完成
        
        1. The pthread_join() function suspends execution of the calling thread 
            until the target thread terminates unless the target thread has already terminated.
        2. On return from a successful pthread_join() call with a non-NULL value_ptr argument, 
            the value passed to pthread_exit() by the terminating thread is stored in the location referenced by value_ptr.  When a
     pthread_join() returns successfully, the target thread has been terminated.  The results of multiple simultaneous calls to pthread_join() specifying the same target thread are undefined.  If the thread calling
     pthread_join() is cancelled, then the target thread is not detached.
    */  
    std::thread t1(runner); // thread started;
    //t1.join();  // main trhead waits t1, bloking
    t1.detach();    // t1 will become daemon process

    // 此时线程是不可join的
    if(t1.joinable()) {
        t1.join();
    }

    /*
        functor 的方式, 传引用的方式
    */
    // 对线程的传参方式，默认是 pass-by-value
    Functor functor_withparam;
    string msg = "test parameter passing";
    
    // c++14之后不允许传引用了？
    // std::thread t5(functor_withparam, msg);
    // cout << "after thread execute, msg:" << msg << endl;
    // t5.join();
    
    // 按引用传递的正确做法
    std::thread t2(functor_withparam, std::ref(msg));
    cout << "after thread execute, msg:" << msg << endl;
    t2.join();

    // move 之后msg 就为空了
    std::thread t3(functor_withparam, std::move(msg));
    cout << "after msg-moved, msg:" << msg << endl;
    t3.join();


    /* 如果没有执行join，程序报错 
        './12_multi_threading' terminated by signal SIGABRT (Abort)
    */
    std::thread t4(functor_withparam, "test thead-object-move");
    cout << "t4.tid: " << t4.get_id() << endl;

    this_thread::sleep_for(std::chrono::seconds(1));
    /*
        move线程,这个几乎没什么用吧, move之后tid没有变
    */
    std::thread t5 = std::move(t4);
    // t4.join(); t4已经不存在了
    cout << "t5.tid: " << t5.get_id() << endl;
    t5.join();
   
    cout << "hardware concurrency: " << thread::hardware_concurrency() << endl;

    system("sleep 3");

    return 0;
}
