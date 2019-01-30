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
        main函数执行到 {throw 32;} 是程序开始unwinding 的地方，然后a对象销毁调用A的析构函数
    
    详见 c++ 文档中 throw 的 Stack unwinding
    As the control flow moves up the call stack, 
    destructors are invoked for all objects with automatic storage duration constructed, 
    but not yet destroyed, since the corresponding try-block was entered, 
    in reverse order of completion of their constructors. 
    If an exception is thrown from a destructor of a local variable or of a temporary used in a return statement, 
    the destructor for the object returned from the function is also invoked. (since C++14)
*/


#include <iostream>

using namespace std;

class A {
public:
    A(){}
    ~A(){
        cout << "~A()" << endl;
        throw 42;
    }
    
};

int main(int argc, char const *argv[])
{
    try{
        A a;
        cout << "main()" << endl;
        throw 32;
    } catch(int a) {
        std::cout << a;
    }
    
    return 0;
}
