/*
 * @Author: liuyanan 
 * @Date: 2019-02-02 15:25:03 
 * @Last Modified by: liuyanan
 * @Last Modified time: 2019-02-02 15:40:11
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

using namespace std;

class LogFile{
public:
    LogFile(){
    }

    void debug(const string& msg) {

        // lazy initialization 推迟到用的时候在创建
        std::call_once(_once_flag, [&](){
            _f.open("multi_threading.log");
            cout << "openning log file" << endl;
        });

        _f << msg << endl;
    }

private:
    mutex _mu;
    once_flag _once_flag;
    ofstream _f;
};


void write_log(const string& msg, LogFile& log){
    for(int i=0; i<100; ++i) {
        log.debug(msg);
    }
}


int main(int argc, char const *argv[])
{
    LogFile log;
    
    string t1_msg = "logging thead-1's msg";
    string t2_msg = "logging thead-2's msg";
    
    thread t1(write_log, std::ref(t1_msg), std::ref(log));
    thread t2(write_log, std::ref(t2_msg), std::ref(log));

    t1.join();
    t2.join();

    return 0;
}
