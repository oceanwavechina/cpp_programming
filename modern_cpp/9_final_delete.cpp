#include <iostream>
#include <vector>
#include <string>
using namespace std;

// c++ 11
class Cat {
public:

    Cat(int a) {}
    Cat() = default;    // 需要编译器创建默认构造函数

    virtual void A(int)  final{
        cout << "Cat::A(int)" << endl;
    }
    
    virtual void B() const {
        cout << "Cat::B() const" << endl;
    }
    
};

class BlueCat: public Cat {
public:
    // 因为基类中指定的final，所以不能覆盖
    /*
    virtual  void A(int)  override {
        cout << "BlueCat::A(float)" << endl;
    }
    */
    
    virtual void B()  const {
        cout << "BlueCat::B()" << endl;
    }

    void C(int value) {
        cout << "C got value: " << value << endl;
    }

    // 加上这一句表示该函数不在接受隐士类型转换了
    // void C(float) = delete;
};


int main(int argc, char const *argv[])
{
    Cat cat;
    cat.A(1);
    cat.B();
    
    BlueCat blue_dog;
    blue_dog.A(1);
    blue_dog.B();
    blue_dog.C(1);
    blue_dog.C(1.2);

    return 0;
}
