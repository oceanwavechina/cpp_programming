/*
 * inherit_STL_templete.cpp
 *
 *  Created on: Mar 12, 2021
 *      Author: liuyanan
 */

#include <vector>
#include <iostream>

using namespace std;



// stl中的容器可以继承

template<typename T>
class DVec: public vector<T> {
public:
	void push_back( const T& value ) {
		cout << "my_push_back:" << value << endl;
		vector<T>::push_back(value);
	}
};

int main(int argc, char const *argv[])
{
    DVec<int> my_vec;
    my_vec.push_back(1);
    for(size_t i=0; i<my_vec.size(); ++i) {
    	cout <<"in my vec: " << my_vec[i] << endl;
    }

    /* code */
    return 0;
}
