//���Բ��ԵĻ��࣬��������fd�ͷ������ݣ�test()Ҳ�������ദ��
#ifndef CTESTBASE_H
#define CTESTBASE_H
#include "cJSON.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
#include <sys/select.h>
#include <errno.h>
#include <vector>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>

class CTestBase
{
public:
    enum
	{
		DATA=0x520139,
		RESULT,
		END
	};
    void sendJSON(int data, char ch[]);
    virtual int test(int fd)=0;
    void setFd(int i);
    CTestBase();
protected:
	int m_iFd;
private:

};

#endif // CTESTBASE_H
