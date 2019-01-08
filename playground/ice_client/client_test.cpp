#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

#include "IceClient.h"

#include "Hello.h"


int
main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "usage: " << argv[0] << " <config_file>"<< std::endl;
		exit(2);
	}


	// MUST setup IceClient at startup !
	IceClient::setup(std::string(argv[1]));

	for(int i=0; i<200; ++i) {
		try {

			/*
			 * �����ǣ�
			 * 		��ice�ĵ��ò��Ǻܾ����ʱ�򣬱��絥�̣߳���ʲô�취�����������Ծ��⣿
			 *
			 *
			 * ˼·�ǣ�
			 * 		1. getProxyByQuey �������Լ��ķ���node�Ĳ��ԣ��Ǵ����е�replica��ѡ��һ����ִ�е��ã�
			 * 			**����ȡ����xml�����õ�����replica��������Ч���**
			 *
			 * 		2. getProxy ��ʹ��iceĬ�ϵĻ��ƣ��� �Զ����� �� �޳���Ч�Ľڵ� �Ĺ���
			 *
			 * 		3. getProxyByQuey �������п���ʧ�ܵ�(����node�ҵ������)����ʧ�ܵ�ʱ�����Ǿ��� getProxy �����»�ȡproxy��
			 * 			Ҳ���ǻ��˵�iceĬ�ϵķ�ʽ����֤���Լ�ʱ���˵����Ľڵ㣬����Ӱ�����
			 *
			 * 		4. �����ֲ��Խ�ϵķ�ʽ���ܽ����Ƶ�ʵ���Զ������node��ͬʱ�ֲ���ά��node�б��ϻ�̫�ྫ��
			 *
			 * �����⣺
			 * 		1. �����߳�ʹ���Զ�����䷽ʽ������getProxyByQuey��������ʱ�����ǻ���Ҫ��һ��counter��ȷ����ǰ����ѯ���ĸ�node��
			 * 			���counter��Ҫ�ñ�֤�̰߳�ȫ���������������ܶ�����Ҫ��Ӱ��
			 * */

// #define ONLY_BY_ID
#ifdef ONLY_BY_ID
			Demo::HelloPrx hello = IceClient::getProxy<Demo::HelloPrx>(OBJID_TEST_HELLO);
#else
			Demo::HelloPrx hello = IceClient::getProxyByQuey<Demo::HelloPrx>(OBJID_TEST_HELLO);
#endif

			if (false) {	// debug
				std::cout << "connection info: " << hello->ice_getConnection()->toString() << std::endl << std::endl;
				std::cout << "endpoints info: ";
				Ice::EndpointSeq endpts = hello->ice_getEndpoints();
				for(auto endpt : endpts) {
					std::cout << endpt->toString();
				}
				std::cout << std::endl << std::endl;
			}

			try{
				std::cout << hello->sayHello() << std::endl;
			} catch(const Ice::NoEndpointException& e) {
				std::cerr << e.what() << "getProxyByType failed, try it again with getProxy ..................." <<endl;

				try{
					hello = IceClient::getProxy<Demo::HelloPrx>(OBJID_TEST_HELLO);
					std::cout << hello->sayHello() << std::endl;
				} catch(const exception& e) {
					std::cerr << e.what() << endl;
				}
			}

		} catch(const exception& e) {
			std::cerr << e.what() << endl;
		}

		sleep(1);
	}

    return 0;
}
