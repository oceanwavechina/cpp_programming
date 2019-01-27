#include <iostream>
#include <vector>
using namespace std;

void foo(int i)
{
    cout << "foo_int" << endl;
}

void foo(char *pc)
{
    cout << "foo_char*" << endl;
}


int main(int argc, char const *argv[])
{
    // this call is ambigous, compile error
    // foo(NULL);
    foo(nullptr);
    foo(0);

    return 0;
}
