/*
 * object_initialize_list_order.cpp
 *
 *  Created on: Jul 6, 2021
 *      Author: liuyanan
 */

#include <iostream>


/*
  主要考察 c++ 对象初始化列表中变量初始化的顺序,
  	  是按声明的顺序执行初始化操作，还是按实现时候的顺序

  看一下，下面的代码会输出什么
 */


class A {
public:
	A(): n2(0), n1(n2+2)
	{ }

	void print()
	{
		std::cout << "n1: " << n1 << ", n2: " << n2 << std::endl;
	}

private:
	int n1;
	int n2;
};


int main(int argc, char **argv)
{
	A a;
	a.print();

	return 0;
}


/*
  c++ 对象初始化列表的执行顺序是按声明的顺序执行的，
  	  只要编译下这份代码就会看到编译器的警告提示
  	  	  	  warning: field 'n2' is uninitialized when used here [-Wuninitialized]
  	  所以会先执行 n1(n2+2), 此时 n2 是个随机值，则 n1 也是随机值
  	  然后在执行 n2(0)，n2 最终为0
 */
