/*
 * deadlock_avoid.cpp
 *
 *  Created on: Sep 9, 2021
 *      Author: liuyanan
 */

#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

class DeadLockDemo {
public:
	static void func_a() {
		// 持有a， 申请b
		mutex_a.lock();
		this_thread::sleep_for(chrono::seconds(1));

		cout << "thread a waiting for mutex b ..." << endl;

		mutex_b.lock();
	}

	static void func_b() {
		// 持有b， 申请a
		mutex_b.lock();
		this_thread::sleep_for(chrono::seconds(1));

		cout << "thread b waiting for mutex a ..." << endl;

		mutex_a.lock();
	}

	static void show_deadlock() {
		thread threads_a(func_a);
		thread threads_b(func_b);

		threads_a.join();
		threads_b.join();
	}

	static mutex mutex_a;
	static mutex mutex_b;
};
mutex DeadLockDemo::mutex_a;
mutex DeadLockDemo::mutex_b;


class DeadLockAvoid {
public:
	static void func_a() {
		// 持有a， 申请b
		mutex_a.lock();

		cout << "thread a waiting for mutex b ..." << endl;

		if(mutex_b.try_lock_for(chrono::seconds(3))) {
			cout << "thread a got mutex b ..." << endl;
			mutex_b.unlock();
		} else {
			cout << "thread a waiting mutex b timeout, aborting ..." << endl;
		}

		mutex_a.unlock();
	}

	static void func_b() {
		// 持有b， 申请a
		mutex_b.lock();

		cout << "thread b waiting for mutex a ..." << endl;

		if(mutex_a.try_lock_for(chrono::seconds(5))) {
			cout << "thread b got mutex a ..." << endl;
			mutex_a.unlock();
		} else {
			cout << "thread b waiting mutex a timeout, aborting ..." << endl;
		}

		mutex_b.unlock();
	}

	static void show_deadlock_avoid() {
		thread threads_a(func_a);
		thread threads_b(func_b);

		threads_a.join();
		threads_b.join();
	}

	static timed_mutex mutex_a;
	static timed_mutex mutex_b;
};
timed_mutex DeadLockAvoid::mutex_a;
timed_mutex DeadLockAvoid::mutex_b;


int main(int argc, char **argv) {

//	DeadLockDemo deadlock_obj;
//	deadlock_obj.show_deadlock();

	DeadLockAvoid deadlock_avoid_obj;
	deadlock_avoid_obj.show_deadlock_avoid();

	return 0;
}
