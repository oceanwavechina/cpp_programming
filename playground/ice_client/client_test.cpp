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
			 * 初衷是：
			 * 		当ice的调用不是很均衡的时候，比如单线程，有什么办法可以让他绝对均衡？
			 *
			 *
			 * 思路是：
			 * 		1. getProxyByQuey 由我们自己的分配node的策略，是从所有的replica中选择一个来执行调用，
			 * 			**它获取的是xml中配置的所有replica，不管有效与否**
			 *
			 * 		2. getProxy 是使用ice默认的机制，有 自动重连 和 剔除无效的节点 的功能
			 *
			 * 		3. getProxyByQuey 调用是有可能失败的(就是node挂掉的情况)，当失败的时候我们就用 getProxy 来重新获取proxy，
			 * 			也就是回退到ice默认的方式（保证可以及时过滤掉坏的节点，而不影响服务）
			 *
			 * 		4. 用两种策略结合的方式，能较完善的实现自定义分配node，同时又不在维护node列表上花太多精力
			 *
			 * 新问题：
			 * 		1. 当多线程使用自定义分配方式（即，getProxyByQuey）做均衡时，我们还需要有一个counter来确定当前的轮询到哪个node，
			 * 			这个counter就要用保证线程安全，这样以来，性能多少又要受影响
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
