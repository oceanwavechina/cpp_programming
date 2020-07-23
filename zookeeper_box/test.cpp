/*
 * @Author: liuyanan 
 * @Date: 2020-07-23 15:50:59 
 * @Last Modified by: liuyanan
 * @Last Modified time: 2020-07-23 16:21:39
 */

#include <zookeeper/zookeeper.h>
#include <iostream>
#include <thread>


using namespace std;

void watcher_callback(zhandle_t* zh, int type, int state, const char* path, void* watch_context) {
    if(type == ZOO_SESSION_EVENT) {
        if(state == ZOO_CONNECTED_STATE) {
            cout << "watcher_callback: connected to zookeeper successfully !" << endl;
        } else if (state == ZOO_EXPIRED_SESSION_STATE) {
            cout << "watcher_callback: zookeeper session expired !" << endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    zoo_set_debug_level(ZOO_LOG_LEVEL_DEBUG);

    const char* HOST = "localhost:2181,localhost:2182,localhost:2183";
    int TIMEOUT = 30000;

    const char* watch_context = "hello zookeeper";
    zhandle_t* zkhandle = zookeeper_init(HOST, watcher_callback, TIMEOUT, 0, (void *) watch_context, 0);
    if(!zkhandle) {
        cerr << "zookeeper_init failed!" << endl;
        exit(1);
    }

    this_thread::sleep_for(10s);

    zookeeper_close(zkhandle);

    return 0;
}
