#include <iostream>
#include <vector>
#include <string>
using namespace std;


// c++ 03
class Dog {
public:
    Dog() {
        init();
    }
    Dog(int a) {
        init();
        cout << "construct with int " << a << endl;
    }
    
    void init()
    {
        cout << "initing ..." << endl;
    }
};

// c++ 11
class Cat {
public:
    Cat() {
        cout << "cat default constructor" << endl;
    }

    Cat(int a):Cat() {
        cout << "cat construct with int " << a << endl;
    }
    
    Cat(string a){
        Cat();
        cout << "cat construct with string " << a << endl;
    }

    Cat(char a){
        cout << "cat construct with char " << a << endl;
        Cat();
    }
};


int main(int argc, char const *argv[])
{
    Dog dog1;
    Dog dog2(2);

    cout << endl;
    Cat cat_int(1);
    cout << endl;
    
    Cat cat_string("fadfa");
    cout << endl;

    Cat cat_char('c');
    cout << endl;

    return 0;
}
