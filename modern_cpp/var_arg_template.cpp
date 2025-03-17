/*
 * var_arg_template.cpp
 *
 *  Created on: Sep 9, 2021
 *      Author: liuyanan
 */

#include <iostream>
#include <tuple>
#include <vector>


using namespace std;


template <class... T>
void arg_count(T... args) {
	// 获取参数包的个数
	cout << "get arg count: " << sizeof...(args) << endl;
}


/* ************************ 参数展开 (递归)	************************ */

/*
  关于参数展开的的递归流程：
  	  当遇到第一个不含可变参数包的的函数时，就认为是终止函数
 */

void unfold_args()
{
	// 终止函数
	cout << "arg-pack end" << endl;
}

template <typename T>
void unfold_args(T head)
{
	// 终止函数
	cout << "cur arg-pack head: " << head << endl;
}

template <typename T, typename X>
void unfold_args(T head, X next)
{
	// 终止函数
	cout << "cur arg-pack head: " << head << ", next: " << next << endl;
}

template <typename T, class ...Args>
void unfold_args(T head, Args... rest)
{
	cout << "cur arg-pack head: " << head << endl;
	unfold_args(rest...);
}


int main(int argc, char **argv) {

	arg_count("param1", 2, 3.0, 4, 5);

	cout << endl;

	unfold_args("param1", 2, 3.0, 4, 5);

	cout << endl;

	return 0;
}
