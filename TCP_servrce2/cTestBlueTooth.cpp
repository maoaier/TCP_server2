/*
 * cTestBlueTooth.cpp
 *
 *  Created on: 2018��7��23��
 *      Author: tarena
 */
using namespace std;
#include "cTestBlueTooth.h"
static const char *s_gBlueToothDev="/dev/ttyS4";

CTestBlueTooth::CTestBlueTooth() {
	// TODO Auto-generated constructor stub
	m_iFd=0;
}

CTestBlueTooth::~CTestBlueTooth() {
	// TODO Auto-generated destructor stub
}

//���Կ��ƺͽ���жϴ���
int CTestBlueTooth::test(int fd)
{
	char buffer[1024]={0};
	setFd(fd);
	int flag=0;
	flag=blueToothTest();
	if(flag==0)
	{
		strcpy(buffer,"Bluetooth test successful");
	}
	else
	{
		strcpy(buffer,"Bluetooth test failed");
	}
	sendJSON(RESULT,buffer);
	memset(buffer,0,sizeof(buffer));
	strcpy(buffer,"BlueTooth test END");
	sendJSON(END,buffer);
	return flag;
}

//�������ԣ�������������ָ�����ָ��
int CTestBlueTooth::blueToothTest()
{
	char buffer[1024]={0};
	//���ļ�
	m_iFd = open("/dev/ttyS4", O_RDWR|O_NOCTTY|O_NDELAY);
	if (m_iFd<1)
	{
		sprintf(buffer,"ad dev can not open %s",s_gBlueToothDev);
		sendJSON(DATA,buffer);
		closeBlue();
		return -1;
	}
	_setGpioValue(GPIO_BT_POWER,1);
	//����������ָ��ģʽ

	usleep(1000*100);
	_setGpioValue(GPIO_BT_KEY,1);
	usleep(1000*100);
	_setGpioValue(GPIO_BT_POWER,0);
	usleep(1000*100);
	//���ô���
	if (!SetSeriOpt(m_iFd))
	{
		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"set seriopt error");
		sendJSON(DATA,buffer);
		close(m_iFd);
		closeBlue();
		return -1;
	}
	usleep(1000*2000);
	char buf[1024];
	memset(buf,0,sizeof(buf));
	sprintf(buf,"AT+VERSION?\r\n");
	//����ָ��
	int wrdata=strlen(buf);
	int wrSize = write(m_iFd, buf, strlen(buf));
	if (wrSize != wrdata)
	{
		//printf("ad uart write error, wrsize is %d, errno is %d", wrSize, errno);
		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"ad uart write error, wrsize is %d, errno is %d", wrSize, errno);
		sendJSON(DATA,buffer);
		close(m_iFd);
		closeBlue();
		return -1;
	}
	sleep(2);
	memset(buf,0,sizeof(buf));
	string res;
	char recBuf[1024] = { 0 };
	unsigned long readCnt = 0;
	//��������
	while (ReadData(recBuf, 1024, readCnt))
	{
		for (unsigned long i = 0; i != readCnt; i++)
			res += recBuf[i];
	}
	cout<<"\nres= "<<res<<endl;
	if(res.find("OK")==string::npos)
	{
		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"read data error");
		sendJSON(DATA,buffer);
		closeBlue();
		return -1;
	}
	const char *data=res.data();
	memset(buf,0,sizeof(buf));
	strcpy(buf,data);
	sendJSON(DATA,buf);

	//�ڶ��η���ָ��s
	memset(buf,0,sizeof(buf));
	sprintf(buf,"AT+NAME?\r\n");
	wrdata=strlen(buf);
	wrSize = write(m_iFd, buf, strlen(buf));
	if (wrSize != wrdata)
	{
		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"ad uart write error, wrsize is %d, errno is %d", wrSize, errno);
		sendJSON(DATA,buffer);
		close(m_iFd);
		closeBlue();
		return -1;
	}
	sleep(1);
	memset(buf,0,sizeof(buf));
	string res1;
	memset(recBuf,0,sizeof(recBuf));
	readCnt = 0;
	while (ReadData(recBuf, 1024, readCnt))
	{
		for (unsigned long i = 0; i != readCnt; i++)
			res1 += recBuf[i];
	}
	cout<<"res1= "<<res1<<endl;
	if(res1.find("OK")==string::npos)
	{
		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"read data error");
		sendJSON(DATA,buffer);
		closeBlue();
		return -1;
	}
	const char *data1=res1.data();
	memset(buf,0,sizeof(buf));
	strcpy(buf,data1);
	sendJSON(DATA,buf);
	closeBlue();
	return 0;
}
//����������
bool CTestBlueTooth::ReadData(char *buf, unsigned long bufSize, unsigned long &readSize)
{
	fd_set fs_read;
	struct timeval time;
	FD_ZERO(&fs_read);
	FD_SET(m_iFd, &fs_read);
	memset(buf, 0, bufSize);

	time.tv_sec = 1;
	time.tv_usec = 0;
	readSize = 0;

	//ʹ��selectʵ�ִ��ڵĶ�·ͨ��
	int fs_sel = select(m_iFd + 1, &fs_read, NULL, NULL, &time);
	printf("fs_sel==%d %d\n",fs_sel,m_iFd);
	if(fs_sel)
	{
		int rdSize = read(m_iFd, buf, bufSize);
		printf("161buf==%s\n",buf);
		if (rdSize < 0)
			return false;
		readSize = rdSize;
		//DebugLog("bluetooth read data %s", buf);
	}
	else
	{
		//ErrorLog("bluetooth read data error");
		return false;
	}
	return true;
}

//�ر�����
void CTestBlueTooth::closeBlue()
{
	_setGpioValue(GPIO_BT_POWER,GPIO_BT_CLOSE);
	_setGpioValue(GPIO_BT_KEY,0);
}

//����GPIO�ڵ�ֵ
void CTestBlueTooth::_setGpioValue(int gpio,int value)
{
	printf("Please input gpio number: \n");
	gpio_register(gpio, GPIO_MODE_OUTPUT);
	gpio_set_value(gpio, value);
	usleep(200);
	gpio_unregister(gpio);
	return ;
}

//��ȡGPIO�ڵ�ֵ
int CTestBlueTooth::_readGpioState(int gpio)
{
	printf("Please input gpio number: ");
	gpio_register(gpio,GPIO_MODE_OUTPUT);
	char buf[1024];
	memset(buf,0,sizeof(buf));
	int value;
	value=gpio_get_value(gpio);
	sprintf(buf,"Read gpio %d initial value: %d ", gpio,value);
	sendJSON(DATA,buf);
	gpio_unregister(gpio);
	return value;
}

//���ô���
bool CTestBlueTooth::SetSeriOpt(int fd)
{
	printf("cTestBlueTooth::SetSeriOpt218\n");
	int byteSize=8;
	struct termios options;
	if (tcgetattr(fd, &options) != 0)
	{
		//ErrorLog("bluetooth can not get serial options");
		return false;
	}
	// ���ò�����
	cfsetispeed(&options, B38400);
	cfsetospeed(&options, B38400);
	// �޸����ģʽ��ԭʼ�������
	options.c_cflag |= CLOCAL | CREAD;
	options.c_oflag &= ~OPOST;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

	// ��������λ
	map <int, int> byteMap;
	byteMap[5] = CS5;
	byteMap[6] = CS6;
	byteMap[7] = CS7;
	byteMap[8] = CS8;
	if (byteMap.find(byteSize) == byteMap.end())
	{
		//ErrorLog("bluetooth byteSize = %d error", 8);
		return false;
	}
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= byteMap[byteSize];

	// ����У��λ
	options.c_cflag &= ~PARENB;
	options.c_iflag &= ~INPCK;


	// ����ֹͣλ
	options.c_cflag &= ~CSTOPB;
	// ���õȴ�ʱ�����С�����ַ�
//	options.c_cc[VTIME] = 1; /* ��ȡһ���ַ��ȴ�1*(1/10)s */
//	options.c_cc[VMIN] = 1; /* ��ȡ�ַ������ٸ���Ϊ1 */
	// �����������������������ݣ����ǲ��ٶ�ȡ ˢ���յ������ݵ��ǲ���
	tcflush(fd,TCIFLUSH);

	if (tcsetattr(fd, TCSANOW, &options) != 0)
	{
		return false;
	}
	return true;
}

