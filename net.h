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


class NET{
public:
	int socket_init(void);
	int bind_init(char **a, char **p);
	int linsten_init(void);
	int accept_init(void);
	int connect_init(void);
	int epoll_init(void);
	int epoll_add(int fd);
	int epoll_wait(void);
	int epoll_del(void);
private:
	int serfd,clifd;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	int epoll_fd;
	int nfds;
	struct epoll_event ev, evs[EPOLL_SIZE];

};

#endif
