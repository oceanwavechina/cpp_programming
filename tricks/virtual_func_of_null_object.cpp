/*
 * null_and_virtual_func.cpp
 *
 *  Created on: May 14, 2018
 *      Author: liuyanan
 */

#include <iostream>

using namespace std;

/*
 *	TODO: ���ԭ���c++�ĵײ�ʵ���Ͻ���
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

int main(int argc, char **argv) {

	A* pa = NULL;

	pa->fun();//���óɹ�

	pa->fun1();//�����������������һ������ȡ����Ȩ�޳�ͻ

	return 0;
}
