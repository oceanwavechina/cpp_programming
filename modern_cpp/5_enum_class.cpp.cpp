#include <iostream>
#include <vector>
using namespace std;


void test_enum_class() {
    // c++ 03
    enum COLOR {GREEN, RED};
    enum SIZE {BIG, SMALL};
    COLOR c = GREEN;
    SIZE s = BIG;

    if(c == s)
        cout  << "COLOR can compare with SIZE";
    else
        cout  << "COLOR can NOT compare with SIZE";

    // c++ 11 中的enum class有了命名空间的约束
    enum class COLOR_11 {GREEN, RED};
    enum class SIZE_11 {BIG, SMALL};
    COLOR_11 c_11 = COLOR_11::GREEN;
    SIZE_11 s_11 = SIZE_11::BIG;

    /*  以下不能编译通过
    if(c_11 == s_11)
        cout  << "COLOR can compare with SIZE";
    else
        cout  << "COLOR can NOT compare with SIZE";
    */
}




int main(int argc, char const *argv[])
{
    test_enum_class();
    return 0;
}
