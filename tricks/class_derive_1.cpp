/*
 * class_derive.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: liuyanan
 */


#include <iostream>

using namespace std;

int i=0;

class Base
{
public:
	Base(){
		cout << "Base Constructor" << endl;
	}
	virtual ~Base() {
		cout << "Base destructor" << endl;
	}


	//void doSomething() {
	virtual void doSomething() {
		cout << "Base do something" << endl;
	}
};


class Derived : public Base
{
public:
	Derived()
		//
		// 这里我们没有显示的调用基类的构造函数
		//	c++会调用默认的基类构造函数
		//
	{
		_counter = ++i;
		cout << "Derived construct:" << _counter << endl;
	}
	virtual ~Derived() {
		cout << "Derived destructor: " << _counter << endl;
	}

	void doSomething() {
		cout << "Derived do something" << endl;
	}

	string foo() {
		cout << "Derived foo" << endl;
		return "Derived foo";
	}

	void dummy() {
		cout << "Derived dummy" << endl;
	}


private:
	// 对象创建和销毁的顺序
	int _counter;
};


int main()
{
	cout << "\n------------------------------ delete Derived pointer --------------------------------\n " << endl;
	Derived *p_1 = new Derived();
	p_1->doSomething();
	delete p_1;

	cout << "\n------------------------------ delete Base pointer ----------------------------------\n " << endl;

	// 加不加 virtual输出的值是不一样的
	// 看对象是哪个，就是调用哪个的方法
	Base *p_2 = new Derived();
	p_2->doSomething();
	delete p_2;

	cout << "\n------------------------------ delete array pointer ----------------------------------\n " << endl;

	Derived* p_derived_array  = new Derived[3];
	// delete p_derived_array;	// 如果用 delete 去释放一个数组，不仅仅是调用几次析构的问题，而是程序会直接崩溃

	cout << "\n------------------------------ get member func address ----------------------------------\n " << endl;

	Derived d;
	typedef string (Derived::*fun)();
	fun f1 = &Derived::foo;

	// ???为啥都是1
	cout << "nonstatic member function address dummy:" << &Derived::dummy << ", foo:"  << &Derived::foo << endl;

	cout << "nonstatic member function called by fun pointer:" << (d.*f1)() << endl;

	return 0;
}
