/*
 * cTestNetworkInterface.cpp
 *
 *  Created on: 2018��7��21��
 *      Author: tarena
 */

#include "cTestNetworkInterface.h"

CTestNetworkInterface::CTestNetworkInterface() {
	// TODO Auto-generated constructor stub
}

//����ӿڲ���
int CTestNetworkInterface::test(int fd)
{
	setFd(fd);
	char buffer[1024];
	memset(buffer,0,sizeof(buffer));
	strcpy(buffer,"SUCCESSFUL:Network Interface is correct");
	sendJSON(RESULT,buffer);
	memset(buffer,0,sizeof(buffer));
	strcpy(buffer,"Network Interface test end");
	sendJSON(END,buffer);
};


CTestNetworkInterface::~CTestNetworkInterface() {
	// TODO Auto-generated destructor stub
}

