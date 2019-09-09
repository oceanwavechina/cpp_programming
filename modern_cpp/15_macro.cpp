/*
 * @Author: liuyanan 
 * @Date: 2019-08-21 10:14:43 
 * @Last Modified by: liuyanan
 * @Last Modified time: 2019-08-21 10:41:54
 */

#include <iostream>

using namespace std;


/*
    从c++11 开始，宏定义可以接收变参的类型，在定义里边用__VA_ARGS__ 接收所有参数
*/

#define INITIALIZE_OBJ(classname, ...) classname(__VA_ARGS__)

// 
//#define INITIALIZE_OBJ_WITH_DEFAULT_VAL(classname, ...) classname("__stranger", "earth", __VA_OPT__(,) __VA_ARGS__)


class Person {
public:
    Person() {}

    Person(string name, string country)
        :_name(name), _country(country) {
    }

    Person(int a)
        :_age(a) {
    }

    void output() {
        cout << "person " << _name << " come from " << _country << ", and " << _age << " years old" << endl;
    }

private:
    string _name;
    string _country;
    int _age;
};



int main(int argc, char const *argv[])
{
    Person myself = INITIALIZE_OBJ(Person, "liuyanan", "China");
    myself.output();

    Person other = INITIALIZE_OBJ(Person, 16);
    other.output();

    return 0;
}
