#include <iostream>
#include <vector>
using namespace std;

/*
 *   1. auto type
 */
void test_foreach()
{
    vector<int> vec = {2, 3, 4, 5};

    // c++03
    for(vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // c++11
    // works on only class that has begin() and end()
    for(auto/*int not iterator*/ i : vec){     // const
        cout << i << " ";
    }
    cout << endl;
    
    for(auto& i : vec){     // reference, changeble
        i += 1;
    }

    cout << "after incre by 1: ";
    for(auto i : vec){     // const
        cout << i << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    // 1. 
    test_foreach();

    return 0;
}
