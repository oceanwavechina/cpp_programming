#include <iostream>
#include <vector>
using namespace std;

/*
 *   1. auto type
 */
void test_auto_type()
{
    vector<int> vec = {2, 3, 4, 5};

    // c++03
    for(vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // c++11 left value
    for(auto it = vec.begin(); it != vec.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;

    auto a = 6;
    auto b = 9.5;
    auto c = 'c';
    auto d = "fadf";
    auto e = string("fadf");
    // error, f 不能被推导出来 (所以不能分配空间)
    // auto f;

    cout << "type of [" << a << "] is: " << typeid(a).name() << endl;
    cout << "type of [" << b << "] is: " << typeid(b).name() << endl;
    cout << "type of [" << c << "] is: " << typeid(c).name() << endl;
    cout << "type of [" << d << "] is: " << typeid(d).name() << endl;
    cout << "type of [" << e << "] is: " << typeid(e).name() << endl;
}

int main(int argc, char const *argv[])
{
    // 1. 
    test_auto_type();

    return 0;
}
