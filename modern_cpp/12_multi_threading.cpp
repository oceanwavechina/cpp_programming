#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <fstream>


using namespace std;

class A{
public:
    ~A() {
        cout << "A's destructor" << endl;
    }
};


void runner() 
{
    // 内存泄露了
    A* leak = new A;

    for (int i=0; i< 3; ++i) {
        cout << "func run" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main(int argc, char const *argv[])
{
    system("sleep 2");
    
    std::thread t1(runner); // thread started;
    //t1.join();  // main trhead waits t1, bloking
    t1.detach();    // t1 will become daemon process

    system("sleep 3");

    return 0;
}
