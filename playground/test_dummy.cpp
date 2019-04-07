#include "stdio.h"
#include <iostream>
#include <sstream>
#include <json/json.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <map>
#include <algorithm>
#include <iterator>
#include <vector>
#include <queue>
#include <set>
#include <boost/thread.hpp>
#include <map>
#include <bitset>
#include <string>
#include <exception>
#include <uuid/uuid.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;

unsigned long TimeStampOfMondayMidnight() {

	boost::gregorian::date d = boost::gregorian::day_clock::universal_day();
	int cur_day = d.day_of_week();
	if(0 == cur_day) {
		cur_day = 7;
	}

    time_t t = time(0);
    struct tm * zeroTm= localtime(&t);
    zeroTm->tm_hour = 0;
    zeroTm->tm_min = 0;
    zeroTm->tm_sec = 0;
    long  ret = mktime(zeroTm) - (cur_day-1) * 86400;
    cout << "timestamp of last monday midnight: " << ret << endl;
    return ret;
}


unsigned long IntervalToMidnight() {

    time_t t = time(0);
    struct tm * zeroTm= localtime(&t);
    zeroTm->tm_hour = 23;
    zeroTm->tm_min = 59;
    zeroTm->tm_sec = 58;
    zeroTm= localtime(&t);
    unsigned long long zeroTime = mktime(zeroTm);
    cout << "midnight Time: " << zeroTime << endl;
    cout << "current Time: " << time(0) << endl;
    return zeroTime - time(0);
}

unsigned long TodayDatestamp() {
    time_t t = time(0);
    struct tm * zeroTm= localtime(&t);
    zeroTm->tm_hour = 0;
    zeroTm->tm_min = 0;
    zeroTm->tm_sec = 0;
    return mktime(zeroTm);
}

void test_jsoncpp() {
	// std::string strValue = "{\"key1\":\"value1\",\"array\":[{\"key2\":\"value2\"},{\"key2\":\"value3\"},{\"key2\":\"value4\"}]}";
	std::string strValue = "{\"key1\":23,\"array\":[{\"key2\":\"value2\"},{\"key2\":\"value3\"},{\"key2\":\"value4\"}]}";
	// std::string strValue = "{\"array\":[{\"key2\":\"value2\"},{\"key2\":\"value3\"},{\"key2\":\"value4\"}]}";

	Json::Reader reader;
	Json::Value value;

	assert(value.isNull());
	value["type"] = 1;
	assert(!value.isNull());

	if (reader.parse(strValue, value)) {

		// std::string out = value["key1"].asString();
		int out1 = value["key1111"].asInt();
		std::cout << out1 << std::endl;

		std::string out = value["key1"].asString();
		const Json::Value arrayObj = value["array"];

		for (int i=0; i<arrayObj.size(); i++) {

			out = arrayObj[i]["key2"].asString();
			std::cout << out;
			if (i != arrayObj.size() - 1 )
			std::cout << std::endl;
		}
	}
}

void test_json_writer() {
	Json::Value root;
	Json::FastWriter writer;
	root["purchased"] = Json::Value::Int(1);
	root["leftdays"] = Json::Value::Int(2);

	std::cout << writer.write(root) << std::endl;
}


void test_and() {
	int a=8;
	int b=9;
	if(b >0 && (a&8)) {
		std::cout << "true" << endl;
	}

}

void max() {

	std::cout << "(unsigned long long): " << (unsigned long long)-1 << std::endl;
	std::cout << "(unsigned short): " << (unsigned short)-1 << std::endl;
}

void test_stream()  {
    ostringstream oss;
    oss << "the stream content exist";
    cout << oss.str();
    cout << oss.str();
}

void test_boost_helper() {

	enum MISSION_IDX {
		USER_PAY_STAGE_1,			// = 7, ���յ��γ�ֵ 1-9 Ԫ
		USER_PAY_STAGE_2,			// = 8, ���յ��γ�ֵ 10-29 Ԫ
		USER_PAY_STAGE_3,			// = 9, ���յ��γ�ֵ 30-99 Ԫ
		USER_PAY_STAGE_4,			// = 10, ���յ��γ�ֵ 100 Ԫ����

	};

	map<int/*mission_id*/,int/*gift_num*/> mission_pay_map = boost::assign::map_list_of(USER_PAY_STAGE_1,1)(USER_PAY_STAGE_2,20)\
					(USER_PAY_STAGE_3,50)(USER_PAY_STAGE_4,200);

	for(auto it : mission_pay_map) {
		std::cout << it.first << " : " << it.second << std::endl;
	}
}

int map_bound_test()
{
  std::multimap<char,int> mymap;
  std::multimap<char,int>::iterator itlow,itup;

  mymap.insert(make_pair('a', 20));
  mymap.insert(make_pair('a', 20));
  mymap.insert(make_pair('b', 40));
  mymap.insert(make_pair('c', 50));

  // print content:
  std::cout << "content: " << std::endl;
  for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';


  mymap.erase(mymap.begin());


  // print content:
  std::cout << "content: " << std::endl;
  for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

#if 0
  itlow=mymap.lower_bound ('b');  // Ѱ�� 'b' <= ?
  itup=mymap.upper_bound ('d');   // Ѱ�� 'c' < ?

  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  std::cout << "content: " << std::endl;
  for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';


  std::cout << "next low" << std::endl;
  itlow--;
  std::cout << itlow->first << " => " << itlow->second << '\n';

  std::cout << "next up" << std::endl;
  itup++;
  std::cout << itup->first << " => " << itup->second << '\n';
#endif

  return 0;
}


class  A{
public:

	void foo_A() {
		cout<< __func__ <<endl;
	}

    class B{
		public:
			B (char *name):name(name) {
				cout<<"Constructing B:"<<name<<endl;
				// foo_A();// Error
			}
		private:
			char *name;
    };
};

template<class T>
class TimedPriorityQueue
{
public:
    bool Empty() {
        boost::mutex::scoped_lock sl(_locker);
        return _tasks.empty();
    }

    size_t Size() {
        boost::mutex::scoped_lock sl(_locker);
        return _tasks.size();
    }

    void Enqueue(uint time, const T& t){
        boost::mutex::scoped_lock sl(_locker);
        _tasks.insert(make_pair(time, t));
    }

    bool TryDequeue(T& t){
        boost::mutex::scoped_lock sl(_locker);
        if (!_tasks.empty() && _tasks.begin()->first < time(NULL)) {
             t = _tasks.begin()->second;
             _tasks.erase(_tasks.begin());
             return true;
        }

        return false;
    }

    void DeleteOne(const T& t) {
        boost::mutex::scoped_lock sl(_locker);
        EqualRangeType range = _tasks.equal_range(t);
        for (TaskIterator it=range.first; it != range.second; ++it ) {
            if (it->second == t) {
                _tasks.erase(it);
                break;
            }
        }
    }

    bool Exist(const T& t) {
        boost::mutex::scoped_lock sl(_locker);
        EqualRangeType range = _tasks.equal_range(t);
        for (TaskIterator it=range.first; it != range.second; ++it ) {
            if (it->second == t) {
                return true;
            }
        }

        return false;
    }

    void Clear() {
        boost::mutex::scoped_lock sl(_locker);
        _tasks.clear();
    }

private:
    typedef multimap<uint, T> TT;
    TT   _tasks;
    typedef typename TT::iterator TaskIterator;
    typedef typename std::pair<TaskIterator,TaskIterator> EqualRangeType;


    boost::mutex        _locker;
};


void test_set() {
    std::set<int> c = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    c.erase(10);
    std::set<int> b = {10,11};

    c = b;
    cout << c.size() << endl;
}


void test_reopen()
{
	std::string filename("reopen.txt");
	FILE *mp_tag_record_file = fopen(filename.c_str(),"wb");

	mp_tag_record_file = freopen(filename.c_str(), "wb", mp_tag_record_file);

	fclose(mp_tag_record_file);
}

void test_map()
{
	std:map<int, int> test;
	cout << "map default int value: " << test[1] << endl;
}

void test_bitset()
{
    std::bitset<64> b("01110010");
    std::cout << "initial value: " << b << '\n';

//    b <<= 63;
//    std::cout << b << '\n';
//
//    return;
    while (b.any()) {
        while (!b.test(0)) {
            b >>= 1;
        }
        std::cout << b << '\n';
        b >>= 1;
    }

}

void test_shuffle() {
	std::srand(std::time(0));
	std::vector<int> c = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    random_shuffle(c.begin()+c.size()/3*2, c.end());
    std::cout << "after shuffle: " << std::endl;
	for (std::vector<int>::iterator it=c.begin();it!=c.end(); ++it)
		std::cout << *it << " " << std::endl;
}


typedef pair<string, int> PAIR;
ostream& operator<<(ostream& out, const PAIR& p) {
  return out << p.first << "\t" << p.second;
}
bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
  return lhs.second < rhs.second;
}

struct CmpByValue {
  bool operator()(const PAIR& lhs, const PAIR& rhs) {
    return lhs.second > rhs.second;
  }
};
void test_sort_map_by_value() {
	map<string, int> name_score_map;
	name_score_map["LiMin"] = 90;
	name_score_map["ZiLinMi"] = 72;
	name_score_map["BoB"] = 90;
	name_score_map.insert(make_pair("Bing",99));
	name_score_map.insert(make_pair("Albert",86));
	//��map��Ԫ��ת�浽vector��
	vector<PAIR> name_score_vec(name_score_map.begin(), name_score_map.end());
	sort(name_score_vec.begin(), name_score_vec.end(), CmpByValue());
	// sort(name_score_vec.begin(), name_score_vec.end(), cmp_by_value);
	for (int i = 0; i != name_score_vec.size(); ++i) {
		cout << name_score_vec[i] << endl;
	}
}

void test_try()
{
	try{
		int *p = NULL;
		*p=3;
	} catch (...) {
		cout << "got exception" << endl;
	}
}

void test_bit_op()
{
	cout << "1<<0 :" << (1<<0) << endl;
	cout << "1<<1 :" << (1<<1) << endl;
	cout << "1<<2 :" << (1<<2) << endl;
}

enum TYPES{
	TYPE_A = 0,
	TYPE_B,
	TYPE_C,
};

void test_enum() {
	int a = 10;
	TYPES type = (TYPES)a;

	cout << "error type: " << type << endl;

//	uuid_t uu;
//	int i;
//	uuid_generate( uu );
//
//	for(i=0;i<16;i++)
//	{
//		printf("%02x",uu[i]);
//	}
//	printf("\n");

//	boost::uuids::random_generator rgen;
//	boost::uuids::uuid u = rgen();
//	string str_uuid = boost::lexical_cast<string>(u);
//
//	boost::replace_all(str_uuid, "-", "");
//	cout << "uuid: " << string(str_uuid) << endl;

	cout << "num: " << boost::lexical_cast<int>("10");



	char array[512];
	cout << "size:" << sizeof(array) << endl;
	memset(array, sizeof(array), 0);


	uint64_t tl_enterroom_csrc = 6100000216;
	ostringstream oss;
	oss << "6100000216 -> " << tl_enterroom_csrc;
	cout << oss.str() << endl;

}

int test_switchf()
{
	int n = 1;
	switch(n)
	{
	case 1:
	{
		if(!0) {
			cout << "break" << endl;
			break;
		}

		else
			cout << "not break" << endl;

		break;
	}
	case 2:
	{
		cout << "2" << endl;

		break;
	}

	}
	return 0;
}



void test_array(char* p[])
{
	//char* p[] = {"1234", "456", "789"};
	cout << sizeof(p) / sizeof(char*) << endl;
	cout << sizeof(p[0]) << endl;
}

void test_boost_uuid()
{
	boost::uuids::uuid a_uuid = boost::uuids::random_generator()(); // 这里是两个() ，因为这里是调用的 () 的运算符重载
	const string tmp_uuid = boost::uuids::to_string(a_uuid);
	cout << "boost uuid:" << tmp_uuid.substr(0, 16) << endl;
}

int main(void)
{

	// cout << "IntervalToMidnight: " << IntervalToMidnight() << endl;
	// cout << "TodayDatestamp: " << TodayDatestamp() << endl;

	// test_jsoncpp();

	// test_and();

	// max();

	// test_stream();

	// TimeStampOfMondayMidnight();

//	std::cout << (uint)-1 << std::endl;
//
//	try{
//		throw std::runtime_error("my error");
//	} catch (const std::exception& e) {
//		std::cout << e.what() << std::endl;
//	}
//
//	int arr[10];
//	std::cout << sizeof(arr) << std::endl;

//	unsigned long ret = (unsigned long) -1;
//	std::cout << ret << std::endl;

	// test_boost_helper();
	// map_bound_test();
	// map_bound_test();
	//test_set();
	// test_reopen();
	// test_json_writer();

	// test_map();
//	test_bitset();

	// test_shuffle();

	//test_sort_map_by_value();

//	 test_try();
//	test_bit_op();
//	test_enum();
//	test_switchf();

	// char* p[] = {"1234", "456", "789"};
	// test_array(p);

	test_boost_uuid();

    return 0;
}
