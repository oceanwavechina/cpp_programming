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


int main(int argc, char const *argv[])
{
    cout << "lambda add: " << [](int x, int y) {return x+y;} (3, 4) << endl;
    auto multiply = [](int x, int y) {return x*y;};
    cout << "lambda multiply: " << multiply(3, 4) << endl;

    auto square = [](int x) {return x*x;};
    int result = passing_lambda_function(square, {1, 2, 3, 4, 5});
    cout << "square sum of {1,2,3,4,5} = " << result << endl;

    // 使用[&]告诉编译器我们要引用本地变量
    int y = 4;
    cout << "lambda sub: " << [&](int x) {return x-y;} (3) << endl;
    return 0;

}
