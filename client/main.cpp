#include <QCoreApplication>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<errno.h>
#include"../protocol.h"


#define BUFFER_SIZE 64
#define SERVER_ADDR "192.168.50.53"
#define SERVER_PORT 11111

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int fd;
    struct sockaddr_in sin;
    struct in_addr dst;

    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd == -1)
    {
        perror("socket");
        exit(1);
    }

    inet_pton(AF_INET, SERVER_ADDR, (void *)&dst);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SERVER_PORT);
    sin.sin_addr = dst;

    if (connect(fd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        perror("connect");
        exit(1);
    }

    sPrtcls buf;

    while(1)
    {
        recv(fd,&buf,sizeof(buf),0);
       cout<<(buf.type)<<endl;
       cout<<(buf.buf)<<endl;
    }
    return a.exec();
}
