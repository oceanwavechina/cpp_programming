/*
 * reference_member.cpp
 *
 *  Created on: Jul 20, 2021
 *      Author: liuyanan
 */


#include <iostream>
#include <string>


using namespace std;


/*
  	  c++ 中可以定义 reference-member, 也就是数据成员的类型是引用
  	  但是该类数据成员要在初始化列表中初始化

  	  注意
  	  	  可以把引用成员理解成指向数据的指针，通过sizeof可以知道，
  	  	  没多一个成员就会多一个指针的大小(64bit机器上是8个字节)
 */


class A {
public:
#if 1
	A(string& str, long& lval, char& ch)
		: _r_str(str), _r_long(lval), _r_char(ch), _r_char2(ch) { }
#else
	A(string str, long lval, char ch)
		: _r_str(str), _r_long(lval), _r_char(ch) { }
#endif

public:
	void display(const string& msg)
	{
		cout << "msg:\n";
		cout << "\tstr: " << _r_str <<  "\n";
		cout << "\tlong: " << _r_long <<  "\n";
		cout << "\tchar: " << _r_char <<  "\n";
	}

private:
	string& _r_str;
	long& _r_long;
	char& _r_char;
	char& _r_char2;
};


int main(int argc, char **argv) {

	string str("origin_str");
	long lval = 0;
	char ch = 'a';

	A a(str, lval, ch);

	a.display("origin");

	str = "modified str";
	lval = 99;
	ch = 'z';

	a.display("after modify");

	cout << "sizeof a(A): " << sizeof(a) << endl;

	cout << "sizeof str(string): " << sizeof(str) << endl;

	return 0;
}
