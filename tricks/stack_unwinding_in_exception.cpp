/*
 * @Author: liuyanan 
 * @Date: 2019-01-30 18:19:57 
 * @Last Modified by: liuyanan
 * @Last Modified time: 2019-01-30 20:38:50
 */

/*  
    TODO: 
        1. 这个问题是考察栈调用的顺序和异常如何处理的
        2. 这个还是要断点跟一下

    这个顺序是
        1. main函数执行到 {throw 32;} 是程序开始unwinding 的地方，
        2. thorow所在的作用域开始unwinding
        3. 然后a对象销毁，并调用A的析构函数
        4. 在调用析构函数时再次throw，程序退出

    
    https://stackoverflow.com/questions/2331316/what-is-stack-unwinding
    You have the following issues related to stack unwinding:
        1. avoiding memory leaks (anything dynamically allocated that is not managed by a local object 
            and cleaned up in the destructor will be leaked) - see RAII referred to by Nikolai, 
            and the documentation for boost::scoped_ptr or this example of using boost::mutex::scoped_lock.

        2. program consistency: the C++ specifications state that you should never throw an exception 
            before any existing exception has been handled. 
            This means that the stack unwinding process should never throw an exception 
            (either use only code guaranteed not to throw in destructors, 
            or surround everything in destructors with try { and } catch(...) {}).

        If any destructor throws an exception during stack unwinding you end up in the land of 
        undefined behavior which could cause your program to treminate unexpectedly (most common behavior) 
        or the universe to end (theoretically possible but has not been observed in practice yet).


*/


#include <iostream>

using namespace std;

class A {
public:
    A(){}
    ~A(){
        // 如果不加 endl，连缓存到中断的机会都没有
        // cout << "~A()" << endl;
        cout << "~A()";
        throw 42;
    }
    
};

void test_memory_leak_when_unwinding()
{
    try{
        A* p_a = new A;
        cout << "in function: " << __FUNCTION__ << endl;
        throw 22;
    } catch(int a) {
        std::cout << "caught except in function " << __FUNCTION__ << ": " << a << endl;
    }
}

void test_stack_unwiding_twice()
{
    try{
        A a;
        cout << "in function: " << __FUNCTION__ << endl;
        throw 32;
    } catch(int a) {
        std::cout << "caught except in function " << __FUNCTION__ << ": " << a << endl;
    }
}

int main(int argc, char const *argv[])
{

    test_memory_leak_when_unwinding();

    cout << "didnt call A's destructor, memory leak!" << endl;
    
    test_stack_unwiding_twice();
    
    return 0;
}
