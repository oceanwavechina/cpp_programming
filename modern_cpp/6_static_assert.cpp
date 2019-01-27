#include <iostream>
#include <vector>
using namespace std;


int main(int argc, char const *argv[])
{
    // run-time assert
    char* p = "asdf";
    assert(p != nullptr);

    // compile time assert (c++ 11)
    static_assert(sizeof(int) == 4);

    // 编译不通过
    // static_assert(sizeof(long) == 4);

    return 0;
}
