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
     delete MyServer ;
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
     cfd = accept(fd,NULL,NULL);
     cout<<"aaaaaa"<<endl;
 };

 void cMyTcp::SendMsg(sPrtcls *Buf, size_t len)
 {
    send(cfd,Buf,len,0);
 };

 void RecvMsg(sPrtcls *Buf, size_t len)
 {
     recv(cfd,Buf,len,0);
 }


