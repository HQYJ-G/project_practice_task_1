#ifndef __NET_H__
#define __NET_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>

#define PORT 8888
#define IP "192.168.0.103"

#define EPOLL_SIZE 100
struct data{
	int id;
	char name[32];
	char passwd[128];
};

class NET{
	public:
		/*socket api function*/
		int socket_init(void);
		int bind_init(void);
		int cbind_init(void);
		int listen_init(void);
		int accept_init(void);
		int connect_init(void);
#if 1
		/*epoll api function*/
		int epoll_init(void);
		int sepoll_add(void);
		int cepoll_add(void);
		int epoll_waits(void);
#endif 
	private:
		/* socket data*/
		int fd,cfd,dfd;
		struct sockaddr_in servaddr,cliaddr;
		socklen_t len;
		char buf[128];

		struct data dt;

#if 1
		/* epoll data*/
		int efd;
		int nfds;
		struct epoll_event evt;
		struct epoll_event evts[EPOLL_SIZE];
#endif
};
#endif
