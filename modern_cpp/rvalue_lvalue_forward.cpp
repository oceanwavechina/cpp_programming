#include <iostream>
using namespace std;

/*
  注意以下两个函数的区别，一个参数是左值，另一个是右值引用
 */
void F(int a) {
	cout << "calling F(int a): " <<a << endl;
}

void F(int&& a) {
	cout << "calling F(int&& a): " <<a << endl;
}

template<class T>
void G(T &&a) {

	/*
		If a call to wrapper() passes an rvalue std::string,
			then T is deduced to std::string (not std::string&, const std::string&, or std::string&&),
			and std::forward ensures that an rvalue reference is passed to foo.

		If a call to wrapper() passes a const lvalue std::string,
			then T is deduced to const std::string&,
			and std::forward ensures that a const lvalue reference is passed to foo.

		If a call to wrapper() passes a non-const lvalue std::string,
			then T is deduced to std::string&,
			and std::forward ensures that a non-const lvalue reference is passed to foo.

		也就是保证参数按原有的类型传递，因为我们如果用
			T&& x = a;
			F(x)
		此时依然传的是左值，因为 x 本身是左值

	 */
	F(std::forward<T>(a));  //1

	// F(a);		//2
}

int main(int argc, char const *argv[])
{
	{
		/*
		 右值引用是本身是一个左值，只是它绑定了右值对象，能被右值初始化

		 因为右值引用也是左值，所以是可以被修改的
		 */
		int&& my_rvalue = 5;

		my_rvalue = 6;
	}

	int&& ri = 5;      // 5是右值。 ri是右值引用，ri是左值： 右值引用是绑定了右值对象的左值

	// F(5);              // 编译失败，5是右值，即可以被int绑定也可以被int&&绑定

	F(ri);             // ri是左值，只可以被int绑定，无法被int&&绑定，选择重载1

	//F(std::move(ri));  // 编译失败，std::move(ri)是右值，既可以被int绑定也可以被int&&绑定

	// G(std::move(ri));
	G(1);

    return 0;
}
