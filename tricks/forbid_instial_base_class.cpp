/*
 * @Author: liuyanan 
 * @Date: 2019-08-15 17:45:56 
 * @Last Modified by: liuyanan
 * @Last Modified time: 2019-08-15 18:08:53
 */

/*
    把 构造函数 或是 析构函数 声明成: 
        1. protected 可以不让其实例化，这样就只能够实例化它的派生类
        2. private 既不能实例化，有不能被继承
    这种方法是在编译阶段检查的

    运行时检查的是不是调用的基类的方法，可以在接口中throw，返回默认值
    使用静态检查的方法，可以所有的接口都拿出来，组成一个接口类，将 构造/析构函数 声明为protected
*/
#include <vector>

#if 0
class Base {
public:
    Base() {}

protected:
    ~Base() {}
};

class Base {
public:
    ~Base() {}

protected:
    Base() {}
};
#else
class Base {
public:
    ~Base() {}

private:
    Base() {}
};
#endif

/*
class Derive: public Base {
public:
    Derive() {}
};
*/

// stl中的容器可以继承
using namespace std;
template<typename T>
class DVec: public vector<long> {

};

int main(int argc, char const *argv[])
{
    //Base obj;
    // Derive obj;
    Base private_desctructure;

    std::vector<long> vec;

    /* code */
    return 0;
}
