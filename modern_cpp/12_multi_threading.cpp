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
    void operator()() {
        cout << "functor run" << endl;
    }
};

class FunctorWithParam{
public:
    void operator()(string msg) {
        msg = "modified by thread";
    }
};

int main(int argc, char const *argv[])
{
    system("sleep 2");
    
    std::thread t1(runner); // thread started;
    //t1.join();  // main trhead waits t1, bloking
    t1.detach();    // t1 will become daemon process

    if(t1.joinable()) {
        t1.join();
    }

    Functor functor;
    std::thread t2(functor);
    
    // 下面这种也能编译通过，但是不会运行
    std::thread t3(Functor);

    // 下面这种不能编译通过，会被看成是一个函数声明，functor一定要实例化好
    // std::thread t4(Functor());
    std::thread t4((Functor()));

    // 对线程的传参，永远是pass-by-value
    FunctorWithParam functor_withparam;
    string msg = "msg from main";
    
    // c++14之后不允许传引用了？
    // std::thread t5(functor_withparam, msg);
    // cout << "after thread execute, msg:" << msg << endl;
    // t5.join();
    
    // 按引用传递的正确做法
    std::thread t5(functor_withparam, std::ref(msg));
    cout << "after thread execute, msg:" << msg << endl;
    t5.join();

    // move 之后msg 就为空了
    std::thread t6(functor_withparam, std::move(msg));
    cout << "after thread execute, msg:" << msg << endl;
    t6.join();


    /* 如果没有这一行，程序报错 
        './12_multi_threading' terminated by signal SIGABRT (Abort)
    */
    t2.join();

    system("sleep 3");

    return 0;
}
