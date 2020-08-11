/*
 * Name : tcp.h
 * Date : 2020年8月7日
 * Description : tcp功能实现
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/

#ifndef TCP_H
#define TCP_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<errno.h>
#include<unistd.h>
#include"poll.h"
#include"../protocol.h"

typedef struct
{
    int fd;
    char ip[16];
    short port;
}sClientInfo;

class cMyTcp{
    static const int PollNum=20;

    private:
        int fd;
        int cfd;
        int ClientNum;
        struct sockaddr_in Sin;
        int AddrLen;
        void TcpServer(void);
        struct pollfd Pollfd[PollNum];
        sClientInfo NewClient;
    public:

        cMyTcp(short port);
        ~cMyTcp();

        void WaitClient();
        void SendMsg(sPrtcls *Buf, size_t len);
        void RecvMsg(sPrtcls *Buf, size_t len);
};

#endif // TCP_H
