#include <iostream>
#include <vector>
#include <string>
using namespace std;


/*
  override 是一个标识符，不是一个关键字。

  被 override 修饰的函数，编译器会检查确定重写了基类中的对应函数。
	防止出现，我们想重写，但是因为类型传错了，反而新定义了一个新的函数
 */

// c++ 03
class Dog {
public:
    virtual void A(int) {
        cout << "Base Dog::A(int)" << endl;
    }
    
    virtual void B() const {
        cout << "Base Dog::B() const" << endl;
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
        cout << "Base Cat::A(int)" << endl;
    }
    
    virtual void B() const {
        cout << "Base Cat::B() const" << endl;
    }
    
    virtual void C() {
        cout << "Base Cat::C() const" << endl;
    }
};

class BlueCat: public Cat {
public:
	/*
     	 following functions will got compile error
     	 因为我们指定了 override 关键字，但是基类中并没有对应的函数签名
	 */
//    virtual  void A(float)  override {
//        cout << "BlueCat::A(float)" << endl;
//    }
//

	virtual void B() {
        cout << "BlueCat::B()" << endl;
    }

    virtual void C() override {
        cout << "BulueCat::C() const" << endl;
    }
};


int main(int argc, char const *argv[])
{
    Dog* p_base_dog = new Dog;
    p_base_dog->A(1);
    p_base_dog->B();

    cout << endl;

    Dog* p_yellow_dog = new YellowDog;
    // 以下两个调用的都是基类的方法，因为子类签名变了，但是编译器确没有提示我们
    p_yellow_dog->A(1);
    p_yellow_dog->B();

    cout << endl;

    Cat* p_base_cat = new Cat;
    p_base_cat->A(1);
    p_base_cat->B();

    cout << endl;
    
    Cat* p_cat = new BlueCat;
    p_cat->A(1);
    p_cat->B();		// 注意这里并没有调用 BlueCat 的 B() 函数，因为并没有重写：差了一个 const 导致签名不一样
    p_cat->C();		// 这个调用的是子类的函数，因为签名一样，函数重写成功了

    return 0;
}

/*
Base Dog::A(int)
Base Dog::B() const

Base Dog::A(int)
Base Dog::B() const

Base Cat::A(int)
Base Cat::B() const

Base Cat::A(int)
Base Cat::B() const
BulueCat::C() const
 */
