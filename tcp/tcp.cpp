/*
 * Name : tcp.cpp
 * Date : 2020年8月7日
 * Description : tcp功能实现
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/


#include"../protocol.h"
#include"tcp.h"

 cMyTcp::cMyTcp(short Port)
 {
     Sin.sin_addr.s_addr = htonl(INADDR_ANY);
     Sin.sin_family = AF_INET;
     Sin.sin_port = htons(Port);

    TcpServer();

 };

 cMyTcp::~cMyTcp()
 {

 };

 void cMyTcp::TcpServer(void)
 {
     fd = socket(AF_INET, SOCK_STREAM, 0);

     if (fd == -1)
     {
         cout<<"socket failed"<<endl;
     }

     if (bind(fd,(struct sockaddr *)&Sin,sizeof(Sin)) == -1)
     {
         perror("bind:");
         cout<<"bind failed"<<endl;
     }

     if (listen(fd,5) == -1)
     {
         cout<<"listen failed"<<endl;
     }

 };

 void cMyTcp::WaitClient()
 {
     cout<<"wait client connect"<<endl;
     cfd = accept(fd,NULL,NULL);

 };

 void cMyTcp::SendMsg(sPrtcls *Buf, size_t len)
 {
    if (send(cfd,Buf,len,0) == -1)
    {
        cout<<"send failed"<<endl;
    }
 };

 void cMyTcp::RecvMsg(sPrtcls *Buf, size_t len)
 {
     if (recv(cfd,Buf,len,0) == -1)
     {
         cout<<"recv failed"<<endl;
     }
 }


