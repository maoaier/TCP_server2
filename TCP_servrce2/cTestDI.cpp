/*
 * ctestdi.cpp
 *
 *  Created on: 2018��7��18��
 *      Author: tarena
 */

#include "cTestDI.h"

CTestDI::CTestDI() {
	// TODO Auto-generated constructor stub

}

CTestDI::~CTestDI() {
	// TODO Auto-generated destructor stub
}
//DI����
int CTestDI::test(int fd)
{
	setFd(fd);
	//_setGpioValue(GPIO_DI_PORT,0);
	int value=_readGpioState(GPIO_DI_PORT);
	char buf[1024];
	memset(buf,0,sizeof(buf));
	if(value!=0)
	{
		sprintf(buf,"SUCCESSFUL:GPIO value is %d ",value);
	}
	else
	{
		sprintf(buf,"ERROR:GPIO value is %d ",value);
	}
	sendJSON(RESULT,buf);
	memset(buf,0,sizeof(buf));
	strcpy(buf,"DI test END");
	sendJSON(END,buf);
	return 0;
}

//����GPIO�ڵ�ֵ
void CTestDI::_setGpioValue(int gpio,int value)
{

	printf("Please input gpio number: ");
	gpio_register(gpio, GPIO_MODE_INPUT);
	gpio_set_value(gpio, value);
	gpio_unregister(gpio);
	return ;
}


//��ȡGPIO�ڵ�ֵ
int CTestDI::_readGpioState(int gpio)
{
	printf("Please input gpio number: ");
	gpio_register(gpio,GPIO_MODE_INPUT);//
	char buf[1024];
	memset(buf,0,sizeof(buf));
	int value;
	value=gpio_get_value(gpio);
	sprintf(buf,"Read gpio %d initial value: %d GPIO_MODE_INPUT=%d", gpio,value,GPIO_MODE_INPUT);
	sendJSON(DATA,buf);
	gpio_unregister(gpio);
	return value;
}


