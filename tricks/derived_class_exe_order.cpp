/*
 * derived_class_exe_order.cpp
 *
 *  Created on: Nov 28, 2016
 *      Author: liuyanan
 */

#include <iostream>

using namespace std;


class A
{
public:
	A (): m_iVal(0) {
		test();
	}

    virtual void func() {
    	std::cout<<m_iVal<<' ';
    }

    void test(){
    	func();
    }

public:
      int m_iVal;
};


class B : public A
{
public:
    B() {
    	test();
    }

    virtual void func() {
    	++m_iVal;
    	std::cout<<m_iVal<<' ';
    }
};


int main(int argc ,char* argv[])
{
	A*p = new B;
	p->test();
	return 0;
}


/*
	本问题涉及到两个方面：
	1.C++继承体系中构造函数的调用顺序。
	2.构造函数中调用虚函数问题。

	C++继承体系中，初始化时构造函数的调用顺序如下
		(1)任何虚拟基类的构造函数按照他们被继承的顺序构造
	(2)任何非虚拟基类的构造函数按照他们被继承的顺序构造
	(3)任何成员对象的函数按照他们声明的顺序构造
	(4)类自己的构造函数
	据此可知 A*p = newB;先调用A类的构造函数再调用B类的构造函数。

	构造函数中调用虚函数,虚函数表现为该类中虚函数的行为，即在父类构造函数中调用虚函数，虚函数的表现就是父类定义的函数的表现。why？原因如下：
	假设构造函数中调用虚函数，表现为普通的虚函数调用行为，即虚函数会表现为相应的子类函数行为，并且假设子类存在一个成员变量int a；子类定义的虚函数的新的行为会操作a变量，在子类初始化时根据构造函数调用顺序会首先调用父类构造函数，那么虚函数回去操作a，而因为a是子类成员变量，这时a尚未初始化，这是一种危险的行为，作为一种明智的选择应该禁止这种行为。所以虚函数会被解释到基类而不是子类。

	据此可以得到答案C正确


	**************************************************************************************************************


	B 继承自 A, 先 A 构造函数，输出 0 ，然后 B 构造函数， B 的 test 继承自 A ，然后找 func 函数找到 B 自己的，所以输出 1 ，然后 p->test() 再执行一次，输出 2
 */
