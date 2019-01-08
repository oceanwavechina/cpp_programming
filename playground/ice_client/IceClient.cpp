/*
 * IceClient.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: liuyanan
 */

#include <iostream>
#include "IceClient.h"

Ice::CommunicatorPtr IceClient::_communicator = NULL;
int	IceClient::_conn_num;

IceClient::IceClient() {
}

IceClient::~IceClient() {
	try {
		if (this->_communicator) {
			this->_communicator->destroy();
		}
	} catch (const Ice::Exception& ex2) {
		std::cerr << ex2 << std::endl;
	}
}

void IceClient::setup(const std::string & config_file) {
	if (!IceClient::_communicator) {
		try {
			Ice::PropertiesPtr p = Ice::createProperties();
			p->load(config_file);

			IceClient::_conn_num = p->getPropertyAsIntWithDefault("JX.ConnectionNum", 5);

			Ice::InitializationData initData = Ice::InitializationData();
			initData.properties = p;

			IceClient::_communicator = Ice::initialize(initData);

		} catch (const Ice::Exception& ex1) {
			std::cerr << ex1 << std::endl;
			try {
				if (IceClient::_communicator) {
					IceClient::_communicator->destroy();
					IceClient::_communicator = NULL;
				}
			} catch (const Ice::Exception& ex2) {
				std::cerr << ex2 << std::endl;
			}
			exit(1);
		}
	}
}
