/*******************************************************************************
 * net.h 
 *
 * @fcopyright  Copyright 2020 hua qing yuan jian .
 * @fauthor     [Zhou ZhenQuan] [zhouzhenquan0310@qq.com]
 * @fversion    1.0
 *
 * @fhistory    [2020-08-08] Create file.
 ******************************************************************************/

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
#include "staff.h"

#define PORT 8888
#define IP "192.168.0.200"

#define EPOLL_SIZE 100

class NET{
	public:
		/*socket api function*/
		int socket_init(void);
		int bind_init(void);
		int cbind_init(void);
		int listen_init(void);
		int accept_init(void);
		int connect_init(void);

		/*epoll api function*/
		int epoll_init(void);
		int sepoll_add(void);
		int cepoll_add(void);
		int epoll_waits(void);

		/*staff api function*/
		int add_staff(void);
		int del_staff(void);
		int change_staff(void);

		/*解析信息api*/
		int anal_staff(void);
		int R_staff(void);
		int L_staff(void);
		int Q_staff(void);
		int H_staff(void);
		int C_staff(void);

	private:
		/* socket data*/
		int fd,cfd,dfd;
		struct sockaddr_in servaddr,cliaddr;
		socklen_t len;
		char buf[128];


		/* epoll data*/
		int efd;
		int nfds;
		struct epoll_event evt;
		struct epoll_event evts[EPOLL_SIZE];

		/*staff dtat*/
		struct staff sd;

		/*用于封装sqlite命令*/
		char sql[128];
};
#endif
