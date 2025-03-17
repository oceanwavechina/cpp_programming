/*
 * union.cpp
 *
 *  Created on: Mar 16, 2025
 *      Author: liuyanan
 */


#include <iostream>
#include <vector>
using namespace std;


// 这个太不实用了，尽量不用
union U {
    U() {}
    ~U() {}

    int x1;
    string x2;
};


int main(int argc, char const *argv[])
{
    U u;
    u.x2 = "0";
    u.x1 = 0;

    cout << "u.x1 = " << u.x1 << endl;
    cout << "u.x2 = " << u.x2 << endl;

    return 0;
}
