#ifndef __NET_H__
#define __NET_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8888
#define IP "192.168.0.103"

class NET{
public:
#if 0
	int socket_init(){
		if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
			return -1;
		}else{
			printf("fd;%d\n",fd);
		}
		return 0;
	};
	int bind_init(){
		bzero(&servaddr,0);
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(PORT);
		servaddr.sin_addr.s_addr = inet_addr(IP);
		if(bind(fd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
			return -1;
		else
			printf("bind ok\n");
		return 0;
	};
	int listen_init(){
		if(listen(fd,5) != 0)
			return -1;
		else
			printf("listen....\n");
		return 0;
	};

	int accept_init(){
		len = sizeof(cliaddr);
			if((cfd = accept(fd,(struct sockaddr*)&cliaddr,&len)) == -1){
				return -1;
			}else{
				printf("cfd : %d\n",cfd);
			}
		while(1){
			bzero(buf,0);
			recv(cfd,buf,sizeof(buf),0);
			printf("buf:%s\n",buf);

			if(strncmp(buf,"quit",4) == 0)
				break;
		}

		close(cfd);
		close(fd);
		return 0;
	};

	int connect_init(){
		if(connect(fd,(struct sockaddr*)&servaddr,sizeof(servaddr)) != 0)
			return -1;
		else
			printf("connect ok\n");

		while(1){
			bzero(buf,0);
			fgets(buf,128,stdin);
			send(fd,buf,128,0);

			if(strncmp(buf,"quit",4) == 0)
				break;
		}

		close(fd);

		return 0;
	};
#else 
	int socket_init(void);
	int bind_init(void);
	int listen_init(void);
	int accept_init(void);
	int connect_init(void);

#endif	
private:
	int fd,cfd;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	char buf[128];
};
#endif
