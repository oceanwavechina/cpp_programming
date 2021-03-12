/*
 * sizeof_impl.cpp
 *
 *  Created on: Mar 12, 2021
 *      Author: liuyanan
 */


#include <iostream>

using namespace std;

/*
 	 sizeof 处理类型 和处理变量的实现

 	 注意处理变量的实现时指针 求两个值的差 的不同
 	 	 1. 指针想运算得到的是二者相差几个对象
 	 	 	 比如我们计算两个不同对象的指针，有什么结果？
 	 	 	 	 结果是编译不通过
 	 	 2. 如果求占的内存大小，要先把指针类型转换成普通数值类型比如 size_t
 */

#define SIZEOF_TYPE(T) (size_t)((T*)0+1)

#if 1
	#define SIZEOF_VAR(V) ((size_t)(&V+1)-(size_t)(&V))
#else
	#define SIZEOF_VAR(V) ((&V+1)-(&V))
#endif


int main(int argc, char **argv)
{
	int int_var;
	long long_var;
	char char_var;

	cout << "sizeof int type:" << SIZEOF_TYPE(int) << endl;
	cout << "sizeof long type:" << SIZEOF_TYPE(long) << endl;
	cout << "sizeof char type:" << SIZEOF_TYPE(char) << endl;

	cout << "sizeof int var:" << SIZEOF_VAR(int_var) << endl;
	cout << "sizeof long var:" << SIZEOF_VAR(long_var) << endl;
	cout << "sizeof char var:" << SIZEOF_VAR(char_var) << endl;

	// 相同类型的 指针和指针对应的数值的计算
	cout << "&int_var+1:" << (&int_var+1) << endl;
	cout << "&int_var:" << (&int_var) << endl;
	cout << "&int_var+1 - &int_var:" << (&int_var+1) - (&int_var) << endl;
	cout << "(size_t)&int_var+1 - (size_t)&int_var:" << (size_t)(&int_var+1) - (size_t)(&int_var) << endl;

#if 0
	// 不同类型的 指针的计算, 编译不通过，不同类型的指针不能进行加减运算
	cout << "&int_var:" << (&int_var) << endl;
	cout << "&long_var:" << (&long_var) << endl;
	cout << "&int_var+1 - &long_var:" << (&int_var) - (&long_var) << endl;
#endif

	return 0;
}
