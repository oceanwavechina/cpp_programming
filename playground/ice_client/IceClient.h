/*
 * IceClient.h
 *
 *  Created on: Apr 19, 2017
 *      Author: liuyanan
 */

#ifndef ICECLIENT_H_
#define ICECLIENT_H_

#include <Ice/Ice.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <IceGrid/IceGrid.h>
#include <cstdlib>
#include <atomic>

#include "Hello.h"

#define OBJID_TEST_HELLO	"hello"


class IceClient {

public:
	template <typename T>
	static T getProxy(const std::string& identity) {
		Ice::ObjectPrx prx = IceClient::_communicator->stringToProxy(identity);

		prx->ice_connectionCached(false);
		prx->ice_locatorCacheTimeout(0);
		/* 用模除的方法:
		 * 1. 既可以保证在多线程时并发执行
		 * 2. 又可以控制链接的上限，保证每个链接的利用率不至于太低
		 */
		std::stringstream connectionId;
		connectionId << std::rand() % _conn_num << std::endl;
		//std::cout << "\n\ninter getProxy(), " << "max conn num: " << _conn_num << ", current connId:" << connectionId.str();

		return T::uncheckedCast(prx->ice_connectionId(connectionId.str()));
	}

	template <typename T>
	static T getProxyByQuey(const std::string& identity) {
		IceGrid::QueryPrx query = IceGrid::QueryPrx::checkedCast(IceClient::_communicator->stringToProxy("HiGrid/Query"));

		::Ice::ObjectProxySeq seq = query->findAllReplicas(IceClient::getProxy<T>(identity));

#if 0
		int idx = std::rand()% _conn_num %seq.size();
#else
		static std::atomic<int> counter = ATOMIC_VAR_INIT(0);
		counter.fetch_add(1);
		int idx = counter % seq.size();
#endif

		if (0){
			std::cout << "all proxy by type [" << seq.size() <<  "]:" << std::endl;
			for (auto item : seq) {
				std::cout << item->ice_getConnection()->toString() << std::endl;
			}
			std::cout << "all proxy by type done !!!" << std::endl << std::endl;

			std::cout << "current idx: " << idx << std::endl;
		}

		return T::uncheckedCast(seq[idx]);
	}

	// NOT thread-safe, MUST be called at application startup
	static void setup(const std::string & config_file);

private:
	IceClient();
	virtual ~IceClient();

private:
	static Ice::CommunicatorPtr _communicator;
	static int	_conn_num;

};

#endif /* ICECLIENT_H_ */
