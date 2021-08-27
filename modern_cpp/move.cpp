#include <iostream>
#include <vector>
using namespace std;


/*
 	 https://segmentfault.com/a/1190000020744971?utm_source=tag-newest

	 这要看 move 的实现了：
		typename remove_reference<_Tp>::type&&
		move(_Tp&& __t) _NOEXCEPT
		{
			typedef _LIBCPP_NODEBUG_TYPE typename remove_reference<_Tp>::type _Up;
			return static_cast<_Up&&>(__t);
		}

	其中 remove_reference 的实现如下(也就是不论是什么引用，都转化为类型本身，也即是去掉类型的引用)：
		template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_reference        {typedef _LIBCPP_NODEBUG_TYPE _Tp type;};
		template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_reference<_Tp&>  {typedef _LIBCPP_NODEBUG_TYPE _Tp type;};
		template <class _Tp> struct _LIBCPP_TEMPLATE_VIS remove_reference<_Tp&&> {typedef _LIBCPP_NODEBUG_TYPE _Tp type;};

	所以 move 中 的 typedef _LIBCPP_NODEBUG_TYPE typename remove_reference<_Tp>::type _Up; 相当于类型的本身了

	而 return static_cast<_Up&&>(__t); 也就等价于 return static_cast<T&&>(__t); (T 也就是基础类型)

	所以move所作的就是把 给定类型 转换成 右值引用类型

	具体的数据拷贝在对应的构造函数中

 */

void bad()
{
	cout << __FUNCTION__ << "()" << endl;
	std::string str = "xxxxxxxxxx";
	string&& r = std::move(str);


	cout << "\t" << " new str from move: " << r << endl;

	/*
	  为什么移动后原 str 还有值 ?
	 */
	cout << "\t" << " origin str after move: " << str << endl;

	cout << endl;
}


void good()
{
	cout << __FUNCTION__ << "()" << endl;
	std::string str = "xxxxxxxxxx";
	string&& r = std::move(str);


	string rr = std::move(std::move(r));	// 右值的拷贝构造函数
	string r2(std::move(r));	// 移动构造函数

	cout << "\t" << " new str from move: " << rr << endl;
	cout << "\t" << " origin str after move(shoud be empty): " << str << endl;

	cout << endl;
}


int main(int argc, char const *argv[])
{
	bad();

	good();

    return 0;
}
