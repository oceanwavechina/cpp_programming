#include <iostream>
#include <vector>
#include <string>
using namespace std;

int arr[6] = {6, 5, 4, 3, 2, 1};
int A() {
    return 1;
}

/* c++ 11
    force the computation to happen at compile time
 */

constexpr int A_11() {
    return 2;
}


void test_string_literal() 
{
    // c++ 03
    const char* a = "fadfa";

    // c++ 11
    const char* b = u8"中文？";
    // const char16_t*  = u"这是utf16编码";
    const char32_t* c = U"这是utf32编码";

    cout << "b: " << b << endl;
    cout << "c: " << c << endl;
}

int main(int argc, char const *argv[])
{
    int a = arr[A()+3]; // 在11之前的编译器可能会有compile error, 数组中的引用一定是要编译期间能确定的   
    cout << "a = " << a << endl;

    int a_11 = arr[A_11()+3];
    cout << "a_11 = " << a_11 << endl;

    test_string_literal();

    return 0;
}
