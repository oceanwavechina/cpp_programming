/*
 * memory_leak_detection.cpp
 *
 *  Created on: Sep 6, 2021
 *      Author: liuyanan
 */

#include <iostream>
#include <unordered_map>
#include <sstream>

using namespace std;


/*
 检测内存泄露的方法：
 	 用一个对象记录分配的内存
 	 在 new 某个对象的时候记录下，然后在 delete 的时候删除，
 	 如果对象最后不为空，则需要检查是否发生泄露
 */

class PointerRef {
public:
	static void ref(void* data, const string& func, int line) {
		ostringstream oss;
		oss << func << ":" << line;
		_refs.insert({data, oss.str()});
	}

	static void unref(void* data) {
		_refs.erase(data);
	}

	static void display() {
		if(_refs.empty()) {
			cout << "no leak" << endl;
			return;
		}

		cout << "unreleased memory: ";
		for(auto item : _refs) {
			cout << item.second << ", ";
		}
		cout << endl;
	}

private:
	static unordered_map<void*, string> _refs;
};
unordered_map<void*, string> PointerRef::_refs;


int main(int argc, char **argv) {

	int* p = new int(0);

	// TODO 可变参模板？？
	PointerRef::ref(p, __FUNCTION__, __LINE__);
	PointerRef::display();

	PointerRef::unref(p);
	PointerRef::display();

	return 0;
}
