/*
 * empty_function.cpp
 *
 *  Created on: Aug 24, 2021
 *      Author: liuyanan
 */

#include <iostream>

using namespace std;

int num = 0;

const int* get_num_addr()
{
	return &num;
}

const int get_num_val()
{
	return num;
}


/*
// 编译不过，因为 const 只能修饰 member function
// 当修改一个全局，非成员函数时编译报错
int modify_num_val(int& a) const
{
	a += 1;
	return num;
}
*/


class A {
public:
	/*
	// 在编译层面报错
	int read_member_val() const
	{
		x += 1;
		return x;
	}
	*/

	int read_static_val() const
	{
		// 对 static 类型的修改是可以的
		y += 1;
		return y;
	}

	int modify_parameter(int& z) const
	{
		// 对 参数的修改也是可以
		z += 1;
		return z;
	}

	int get_val() {
		return x;
	}

	/*
	// const 类型的函数不能调用非const 的成员函数
	int call_none_const_func() const
	{
		return get_val();
	}
	*/


private:
	int x;

	static int y;
};

int A::y;



int main(int argc, char **argv) {

	// const 类型的返回一定要用 const 变量接收
	// int* p_a = get_num_addr();
	// int a = get_num_addr();

	// modify_num_val(num);

	A a;
	// a.read_val();
	a.read_static_val();
	int z = 1;
	cout << "modify parameter: " << a.modify_parameter(z) << endl;
	cout << "new z: " << z << endl;

	a.call_none_const_func();

	return 0;
}
