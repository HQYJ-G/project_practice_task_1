#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/epoll.h>


#define  EPOLL_SIZE 500
#define  PORT 7777
#define  IP "192.168.0.103"


class NET{
public:
#if 0
/*NET(char *a,char *p){
		this->a = a;
		this->p = p;
		printf("%s %s\n",a,p);
	};*/
/*
 * function:    创建套接子
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int socket_init(void){
	if((serfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		printf("socket failed\n");
		return -1;
	}

	int i = 1;
	setsockopt(serfd,SOL_SOCKET,SO_REUSEADDR,&i, sizeof(i));
	return 0;
}
/*
 * function:    套接子地址绑定
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int bind_init(){
	bzero(&servaddr,0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr(IP);

	if(bind(serfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1){
		perror("bind failed\n");
		return -1;
	}

	return 0;
}


/*
 * function:    监听套接字
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */
int linsten_init(void){
	if(listen(serfd, 5) != 0){
		printf("listen failed\n");
		return -1;
	}

	return 0;
}

/*
 * function:    等待客户端连接
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int accept_init(void){
	len = sizeof(cliaddr);
	
	if((clifd = accept(serfd,(struct sockaddr*)&cliaddr,&len)) < 0){
		printf("accept failed\n");
		return -1;
	}

	return 0;
}


/*
 * function:    连接服务器
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int connect_init(void){
	if(connect(serfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) != 0){
		printf("connect failed\n");
		return -1;
	}
	
	return 0;
}

/*
 * function:    epoll 初始化
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int epoll_init(void){
	if((epoll_fd = epoll_create(1)) == -1){
		printf("epoll_create failed\n");
		return -1;
	}

	return 0;
}

/*
 * function:    
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int epoll_add(void){
	
	fd = serfd > clifd ? serfd : clifd;

	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = fd;
	if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1){
		printf("epoll_ctl_add fd failed\n");
		return -1;
	}

	printf("%d\n",ev.data.fd);
	return 0;
}

/*
 * function:    
 * @param [ in] 
 * @param [out] 
 * @return      
 */

int epoll_del(void){
	if(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, serfd, &ev) == -1){
		printf("epoll_ctl_del fd failed\n");
		return -1;
	}

	return 0;
}

/*
 * function:    
 * @param [ in] 
 * @param [out] 
 * @return      
 */

int epoll_waits(void){
	if((nfds = epoll_wait(epoll_fd, evs, EPOLL_SIZE, -1)) == -1){
		printf("epoll_wait failed\n");
		return -1;
	}

	return 0;
}
#else 
public:
	int socket_init(void);
	int bind_init(void);
	int linsten_init(void);
	int accept_init(void);
	int connect_init(void);
	int epoll_init(void);
	int epoll_add(void);
	int epoll_waits(void);
	int epoll_del(void);
#endif
private:
	int serfd,clifd,fd;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	int epoll_fd;
	int nfds;
	struct epoll_event ev, evs[EPOLL_SIZE];
	char *a,*p;
};

#endif
