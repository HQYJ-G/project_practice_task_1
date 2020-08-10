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
#include"../protocol.h"

class cMyTcp{
    private:
        int fd;
        int cfd;
        struct sockaddr_in Sin;
        int AddrLen;
        void TcpServer(void);

    public:

        cMyTcp(short port);
        ~cMyTcp();

        void WaitClient();
        void SendMsg(sPrtcls *Buf, size_t len);
        void RecvMsg(sPrtcls *Buf, size_t len);
};

#endif // TCP_H
