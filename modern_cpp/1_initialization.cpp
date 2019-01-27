#include <iostream>
#include <vector>
using namespace std;

/*
    Uniform Initialization Search Order:
    1. Initializer_list construct
    2. Regular constructer that takes the appropriete parameters
    3. Aggregate initializer
*/

/*
 *   1. Initializer list
 */
void test_initializer_list(std::initializer_list<int> const &items)
{
    // c++03 初始化列表
    int arr[4] = {3, 2, 4, 5};
    // c++03 ˙中vector是不可以像数组那样初始化的
    vector<int> v03;
    v03.push_back(3);
    v03.push_back(2);
    v03.push_back(4);
    v03.push_back(5);

    // c++11 extend the support
    vector<int> v11 = {3, 4, 11, 9};

    // 参数支持初始化列表
    cout << "initializer_list(size:" << items.size() << "): ";
    for(auto item : items) {
        cout << item << " ";
    }
    cout << endl;
}

template <class T>
class CustomArray {
public:
    CustomArray(initializer_list<T> const &l) 
    : _vec(l)
    {
        cout << "construct CustomArray with size: " << l.size() << endl;
    }

    void append(initializer_list<T> const &l)
    {
        _vec.insert(_vec.end(), l.begin(), l.end());
        cout << "custom array append:";
        for(auto item : l) {
            cout << item << " ";
        }
        cout << endl;
    }

    void display() {
        cout << "display() element:";
        for(auto item : _vec) {
            cout << item << " ";
        }
        cout << "\na = " << a;
        cout << endl;
    }

private:
    vector<T> _vec;
    int a = 9;  // 成员变量可以在类声明的时候指定初始值
};

/*
 *   1. Uniform Initialization
 */
// c++03
class Dog{
public:
    int age;
    string name;
};

// c++11
class Cat{
public:
    Cat(int age, const string& name):age(age), name(name) {

    }
    int age;
    string name;
};


class InitializationOrder{
public:
    // 3rd choice
    int age;

    // 2nd choice
    InitializationOrder(int a) {
        age = a;
    }   

    // 1st choice
    InitializationOrder(const initializer_list<int>& vec) {
        age = *(vec.begin());
    }
};

int main(int argc, char const *argv[])
{
    // 1. 
    test_initializer_list({1,2,3,4,5});  
    CustomArray<char> custom_array = {'a', 'b', 'c'};
    custom_array.display();
    custom_array.append({'d', 'e'});
    custom_array.display();

    // 2. 
    Dog dog = {1, "puppy~"};
    cout << "aggregate initialize dog with age:" << dog.age << ", name:" << dog.name << endl;

    Cat cat{1, "kitty~"};
    cout << "curly brace initialize cat with age:" << cat.age << ", name:" << cat.name << endl;

    return 0;
}
