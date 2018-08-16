#include "main.h"
#include "stdio.h"

int main() {
	CTcpSock tcpserver;
	bool bo=tcpserver.sockInit(PORT);
	if(bo==false)
	{
		printf("sock run\n");
		return -1;
	}
	printf("sock run\n");
	tcpserver.sockRun();
   //tcpserver.sockClear();
	printf("end\n");
	return 0;
}


