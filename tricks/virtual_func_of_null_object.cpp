/*
 * null_and_virtual_func.cpp
 *
 *  Created on: May 14, 2018
 *      Author: liuyanan
 */

#include <iostream>

using namespace std;

/*
 *  TODO: 请从原理和c++的底层实现上解释
 *
 */


class A
{
public:
    void fun() {
        cout << "fun()" << endl;
    }

    virtual void fun1(){
        cout << "virtual fun()" << endl;
    }
};

class Parent {
public:
	Parent(): a(0) {}

	void incre() {
		++a;
	}

private:
	int a;
};

int main(int argc, char **argv) {

#ifdef TEST
    A* pa = NULL;

    pa->fun();//调用成功

    pa->fun1();//程序崩溃，报错：引发一场，读取访问权限冲突
#endif


    /* ****************** ****************** */
    // Parent* const p = new Parent();		// 这个是常量指针，它不能再指向别的东西
    const Parent*  p = new Parent();		// 指针指向的是常量，也就是执行的东西不可以改，但指针本身可以在指向别的东西

    // NOTE:
    // 		这里是不可以的:  'this' argument to member function 'incre' has type 'const Parent', but function is not marked const
    // 		const 修饰的是 parent 的 this 指针， 所以这个对象是 const 的，所以对象的函数也要求是const 的
    p->incre();

    return 0;
}
