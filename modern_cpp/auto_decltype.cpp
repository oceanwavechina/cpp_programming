#include <iostream>
#include <vector>
#include <string>
using namespace std;


auto foo() -> decltype(auto)
{
    return 16;
}

int main(int argc, char const *argv[])
{

    cout << foo() << endl;

    return 0;
}
