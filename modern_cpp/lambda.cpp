#include <iostream>
#include <vector>
#include <string>
using namespace std;


/*
    lambda 函数作为参数传递时，会比较有用
    function programming
*/
template <typename FUNC>
int passing_lambda_function(FUNC f, vector<int> values) {
    int ret = 0;
    for(auto i : values) {
        ret +=  f(i);
    }
    return ret;
}


/*
参数捕捉：
	也就是引用闭包之外的变量

 */

void captures_by_ref() {

    int y = 4;
    int a = 4;

    cout << __FUNCTION__ << " before lambda actual &y: " << &y << ", y: " << y << ", a: " << a << ", &a: " << &a << endl;

    /*
     使用[&]告诉编译器我们要引用本地变量,
     	 其中 a 是值传递，其余的是按引用传递

     注意按值拷贝捕获变量，默认是不可以修改的。如果需要修改需要加 mutable 关键字修饰


	captures_by_ref before lambda actual &y: 0x7ffee98d95bc, y: 4, a: 4, &a: 0x7ffee98d95b8
	in lambda closure &y: 0x7ffee98d95bc, y: 4, a: 4, &a: 0x7ffee98d95a8
	captures_by_ref after  lambda actual &y: 0x7ffee98d95bc, y: 5, a: 4, &a: 0x7ffee98d95b8

     */
    [&, a](int x) mutable {
    	cout << "in lambda closure &y: " << &y << ", y: " << y << ", a: " << a << ", &a: " << &a << endl;
    	++y;
    	++a;
    } (3);


    cout << __FUNCTION__ << " after  lambda actual &y: " << &y << ", y: " << y << ", a: " << a << ", &a: " << &a << endl;

    cout << endl;
}

void captures_by_copy() {

    int y = 4;
    int a = 4;

    cout << __FUNCTION__ << " before lambda actual &y: " << &y << ", y: " << y << ", a: " << a << ", &a: " << &a << endl;

    /*
     使用[=]告诉编译器我们要引用本地变量, 包括this指针
     	 其中 a 是引用传递，其余的是按值拷贝传递

     注意按值拷贝捕获变量，默认是不可以修改的。如果需要修改需要加 mutable 关键字修饰


	captures_by_copy before lambda actual &y: 0x7ffee98d95bc, y: 4, a: 4, &a: 0x7ffee98d95b8
	 in lambda closure &y: 0x7ffee98d95b0, y: 4, a: 4, &a: 0x7ffee98d95b8
	captures_by_copy after  lambda actual &y: 0x7ffee98d95bc, y: 4, a: 5, &a: 0x7ffee98d95b8

     */
    [=, &a](int x) mutable {
    	cout << " in lambda closure &y: " << &y << ", y: " << y << ", a: " << a << ", &a: " << &a << endl;
    	++y;
    	++a;
    } (3);


    cout << __FUNCTION__ << " after  lambda actual &y: " << &y << ", y: " << y << ", a: " << a << ", &a: " << &a << endl;

    cout << endl;
}

int main(int argc, char const *argv[])
{
    cout << "lambda add: " << [](int x, int y) {return x+y;} (3, 4) << endl;
    auto multiply = [](int x, int y) {return x*y;};
    cout << "lambda multiply: " << multiply(3, 4) << endl;

    auto square = [](int x) {return x*x;};
    int result = passing_lambda_function(square, {1, 2, 3, 4, 5});
    cout << "square sum of {1,2,3,4,5} = " << result << endl;

    cout << endl;

    captures_by_ref();

    captures_by_copy();

    int x = 5;
    auto foo = [r = x+1]{return r;};
    cout << "foo=" << foo() << endl;





}
