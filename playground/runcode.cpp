#define BOOST_STACKTRACE_USE_BACKTRACE
#include <iostream>
#include <boost/atomic.hpp>
#include <boost/stacktrace.hpp>
#include <boost/exception/all.hpp>

using namespace std;


int main(int argc, char const *argv[])
{
    /* code */
    
    int retry = 3;
    try {
        throw runtime_error("my_error!");
    } catch (std::exception& e) {
        const boost::stacktrace::stacktrace *st = boost::get_error_info<traced>(e);
        if (st)
        {
          //打印堆栈
            cerr << *st;
        }
    }
    
    return 0;
}
