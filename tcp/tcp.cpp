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

/*
  *名称：      服务器的构造函数
  *功能：      初始化服务器；
  * 参数：     short Port 端口号；
  * 返回值： 无
*/
 cMyTcp::cMyTcp(short Port)
 {
     Sin.sin_addr.s_addr = htonl(INADDR_ANY);
     Sin.sin_family = AF_INET;
     Sin.sin_port = htons(Port);
    TcpServer();

 };

 cMyTcp::~cMyTcp()
 {
    close(fd);
 };

 /*
   *名称：      TcpServer
   *功能：      初始化服务器；在构造函数中调用
   * 参数：     无
   * 返回值： 无
 */
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

     memset(Pollfd,0,sizeof(Pollfd));
     Pollfd[0].fd = fd;
     Pollfd[0].events = POLLIN;
     ClientNum = 1;
 };

 /*
   *名称：      WaitClient
   *功能：      等待客户端连接
   * 参数：     无；
   * 返回值： 无
 */
 void cMyTcp::WaitClient()
 {
     struct sockaddr_in tSin;
     socklen_t l = sizeof(struct sockaddr_in);
     cout<<"wait client connect"<<endl;

     poll(Pollfd,ClientNum,-1);

     if (Pollfd[0].revents == POLLIN)
     {
         /*添加新连接到监控表*/
        Pollfd[ClientNum].fd = accept(fd,(struct sockaddr *)&tSin,&l);
        Pollfd[ClientNum].events = POLLIN;

        /*记录连接的信息*/
        NewClient.fd = Pollfd[ClientNum].fd;
        NewClient.port = ntohs(tSin.sin_port);
        inet_ntop(AF_INET, (void *)&tSin.sin_addr, NewClient.ip, sizeof(NewClient.ip));
        cout<<NewClient.ip<<":"<<NewClient.port<<":"<<NewClient.fd<<endl;
        ClientNum++;
     }


 };

 /*
   *名称：      SendMsg
   *功能：      发送消息
   * 参数：     sPrtcls *Buf 发送信息首地址, size_t len发送信息的长度
   * 返回值： 无
 */
 void cMyTcp::SendMsg(sPrtcls *Buf, size_t len)
 {
     printf("BUF%d\n",Buf->type);
     if(!((Buf->type==DISCONNECT) |(Buf->type == CONNECT)))
     {
        if (send(cfd,Buf,len,0) == -1)
        {
             cout<<"send failed"<<endl;
         }
        cout<<"send ok"<<endl;
     }
 }

 /*
   *名称：      SendMsg
   *功能：      发送消息
   * 参数：     sPrtcls *Buf 接收缓存区首地址, size_t len接收信息的长度
   * 返回值： 无
 */
 void cMyTcp::RecvMsg(sPrtcls *Buf, size_t len)
 {
    int i;
//    char a[256] ={};

     for(i = 1;i<ClientNum;i++)
     {
        if(Pollfd[i].revents == POLLIN)
        {
            cfd = Pollfd[i].fd;
             if (recv(Pollfd[i].fd,Buf,len,0) == -1)
             {
                  cout<<"recv failed"<<endl;
            }
             cout<<"recv ok"<<endl;
             break;

//            recv(Pollfd[i].fd,a,256,0);
 //           cout<<a<<endl;
        }
        Buf->type = CONNECT;//如果新连接触发POLL则会触发此标志
     }
 }

 /*
   *名称：      CloseNow
   *功能：      清除刚刚接受过数据的fd;
   * 参数：     无
   * 返回值： 无
 */
void cMyTcp::CloseNow()
{
    int i;
    for(i=0;i<ClientNum;i++)
    {

        if(cfd == Pollfd[i].fd)
        {
            Pollfd[i].fd = Pollfd[ClientNum-1].fd;
            ClientNum--;
//       Pollfd[ClientNum].fd = 0;
            close(cfd);
//            cout<<"close"<<cfd<<endl;
            break;
        }
    }
}

