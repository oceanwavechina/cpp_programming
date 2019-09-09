/*
 * @Author: liuyanan 
 * @Date: 2019-09-09 11:55:19 
 * @Last Modified by: liuyanan
 * @Last Modified time: 2019-09-09 12:47:56
 */
#include <iostream>

using namespace std;

class noncopyable {
protected:
    noncopyable() {}
    ~noncopyable() {}
private:
    noncopyable(const noncopyable&);
    const noncopyable& operator=(const noncopyable&);
};

class CTest: private noncopyable {
public:
    int a;
};

int main(int argc, char const *argv[])
{
    CTest test_obj = CTest();
    CTest copied = test_obj;

    return 0;
}
