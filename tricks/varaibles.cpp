/*
 * varaibles.cpp
 *
 *  Created on: Dec 16, 2016
 *      Author: liuyanan
 */

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;


/*
 	 说一下 get_str1 和 get_str2 的区别

 	 get_str1:
 	 	 str 指向的是一个数组，这个数组在栈里边； 9个字节，包含'\0'， str是这个数组的首地址
 	 	 程序是可以修改数组中的元素的

	 get_str2:
 	 	 str 是一个指针，这个指针在栈里边； 但是"abcd1234"是常量，在静态存储区
 	 	 其中str 这个指针占用一个机器字的长度(64bit在64位机器上)， "abcd1234" 占用9个字节的长度
 	 	 因为是常量，程序不可以修改str指向的数据
 */
char* get_str1() {

	// 这句话，计算机都做了哪些操作？
	char str[] = "abcd1234";

	return str;
}

char* get_str2() {

	// 这句话，计算机都做了哪些操作？
	char *str = "abcd1234";

	return str;
}


void test_order() {
	int i = 5;
	int j = i++;

	cout << "{int i = 5; int j = i++;}:\t" << "i = " << i << ", j = " << j << endl;
	

	int a = 5;
	int b = ++a;

	cout << "{int a = 10; int b = ++a;}:\t" << "a = " << a << ", b = " << b << endl;
}


/*
 *  1) #define是预处理指令，在编译预处理时进行简单的替换，不作正确性检查，不关含义是否正确照样带入，只有在编译已被展开的源程序时才会发现可能的错误并报错。例如：
		#define PI 3.1415926
		程序中的：area=PI*r*r 会替换为3.1415926*r*r
		如果你把#define语句中的数字9 写成字母g 预处理也照样带入。

	2）typedef是在编译时处理的。它在自己的作用域内给一个已经存在的类型一个别名，但是You cannot use the typedef specifier inside a function definition。

	3）typedef int * int_ptr;
		与
	   #define int_ptr int *
	  作用都是用int_ptr代表 int * ,但是二者不同，正如前面所说 ，#define在预处理 时进行简单的替换，而typedef不是简单替换 ，而是采用如同定义变量的方法那样来声明一种类型。也就是说;

	//refer to (xzgyb(老达摩))
	#define int_ptr int *
	int_ptr a, b; //相当于int * a, b; 只是简单的宏替换

	typedef int* int_ptr;
	int_ptr a, b; //a, b 都为指向int的指针,typedef为int* 引入了一个新的助记符

	这也说明了为什么下面观点成立
	//QunKangLi(维护成本与程序员的创造力的平方成正比)
	typedef int * pint ;
	#define PINT int *

	那么：
	const pint p ;//p不可更改，但p指向的内容可更改
	const PINT p ;//p可更改，但是p指向的内容不可更改。

	pint是一种指针类型 const pint p 就是把指针给锁住了 p不可更改
	而const PINT p 是const int * p 锁的是指针p所指的对象。

	4）也许您已经注意到#define 不是语句 不要在行末加分号，否则 会连分号一块置换。
 */
void test_define_newtype()
{
	typedef int* int_ptr_typedef;
	#define int_ptr_define int*

	int_ptr_define a, b;
	cout << "using macro define, type(a)=" << typeid(a).name() << ", type(b)=" << typeid(b).name() << endl;

	int_ptr_typedef c, d;
	cout << "using typedef define, type(c)=" << typeid(c).name() << ", type(d)=" << typeid(d).name() << endl;
}

void test_unsigned_varaible()
{
	vector<int> buf = {};
	size_t sz = buf.size();

	/* 这个判断永远是真的*/
	// while(--sz >= 0 ){
	/* 这个判断还是不容易读懂*/
	// while(sz-- > 0 ){
	/*最完美的方式*/
	for(int i=0; i < sz; ++i)
		cout << "in loop" << endl;
	}
}


int main(int argc, char **argv) {
	cout << "get_str1():" << get_str1() << endl;
	cout << "get_str2():" << get_str2() << endl;

	test_define_newtype();

	test_order();

	test_unsigned_varaible();
}



