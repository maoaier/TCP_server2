#include "cTestBase.h"
//����json��ʽ������
void CTestBase::sendJSON(int data, char ch[])
{
    char buf[1024];
    memset(buf,0,1024);
    strcpy(buf,ch);
    cJSON *usr;
    usr=cJSON_CreateObject();
    if(data==DATA)
    {
        cJSON_AddStringToObject(usr,"DATA",buf);
    }
    if(data==END)
    {
         cJSON_AddStringToObject(usr,"END",buf);
    }
    if(data==RESULT)
    {
        cJSON_AddStringToObject(usr,"RESULT",buf);
    }
    char* tmp=cJSON_Print(usr);
    char buffur[1024];
    memset(buffur,0,1024);
    strcpy(buffur,tmp);
    printf("sockSend %s\n",buffur);
    printf("json data:%d\n",strlen(buffur));
    buffur[strlen(buffur)]='\b';
    send(m_iFd, buffur, strlen(buffur), 0);
}

void CTestBase::setFd(int i)
{
    m_iFd=i;
}

CTestBase::CTestBase()
{

}
