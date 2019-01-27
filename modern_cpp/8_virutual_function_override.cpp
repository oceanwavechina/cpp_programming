#include <iostream>
#include <vector>
#include <string>
using namespace std;


// c++ 03
class Dog {
public:
    virtual void A(int) {
        cout << "Dog::A(int)" << endl;
    }
    
    virtual void B() const {
        cout << "Dog::B() const" << endl;
    }
};

class YellowDog: public Dog {
public:
    virtual  void A(float) {     // create a new function
        cout << "YellowDog::A(float)" << endl;
    }
    
    virtual void B() {           // create a new function
        cout << "YellowDog::B()" << endl;
    }
};

// c++ 11
class Cat {
public:
    virtual void A(int) {
        cout << "Cat::A(int)" << endl;
    }
    
    virtual void B() const {
        cout << "Cat::B() const" << endl;
    }
    
    virtual void C() {
        cout << "Cat::C() const" << endl;
    }
};

class BlueCat: public Cat {
public:
    /* following functions will got compile error
    virtual  void A(float)  override {
        cout << "BlueCat::A(float)" << endl;
    }
    
    virtual void B()  override {
        cout << "BlueCat::B()" << endl;
    }
    */

    virtual void C() override {
        cout << "BulueCat::C() const" << endl;
    }
};


int main(int argc, char const *argv[])
{
    Dog dog;
    dog.A(1);
    dog.B();
    
    YellowDog yellow_dog;
    yellow_dog.A(1);
    yellow_dog.B();

    cout << endl;

    Cat cat;
    cat.A(1);
    cat.B();
    
    BlueCat blue_dog;
    blue_dog.A(1);
    blue_dog.B();
    blue_dog.C();

    return 0;
}
