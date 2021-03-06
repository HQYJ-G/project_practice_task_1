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
#include "../protocol.h"
#include <iostream>

using namespace std;

#define EPOLL_SIZE 100

class NET{
	public:
		NET(char a[], char b[],int n){
			if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
				perror("socket failed\n");
			}else{
				printf("fd;%d\n",fd);
			}
			int i = 1;
			setsockopt(fd,SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int));

			bzero(&servaddr,0);
			servaddr.sin_family = AF_INET;
			servaddr.sin_port = htons(atoi(b));
			servaddr.sin_addr.s_addr = inet_addr(a);
			if(bind(fd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0){
				perror("bind failed\n");
			}else
				printf("bind ok\n");

			if(listen(fd,n) != 0){
				perror("listen failed\n");
			}else
				printf("listen....\n");

		}
		NET(char a[], char b[]){
			printf("%s %d\n",a,atoi(b));
			if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
				perror("socket failed\n");
			}else{
				printf("fd;%d\n",fd);
			}

			bzero(&servaddr,0);
			servaddr.sin_family = AF_INET;
			servaddr.sin_port = htons(atoi(b));
			servaddr.sin_addr.s_addr = inet_addr(a);
			printf("bind ok\n");

#if 0
			if(connect(fd,(struct sockaddr*)&servaddr,sizeof(servaddr)) != 0){
				perror("connect failed\n");
			}else
				printf("connect ok\n");
#endif 


		}

		~NET(){
			close(fd);
			printf("~~~~~~~~~~~\n");
		}


		/*socket api function*/
		int accept_init(void);
		int connect_init(void);

		/*epoll api function*/
		int epoll_init(void);
		int sepoll_add(void);
		int cepoll_add(void);
		int epoll_waits(void);
#if 0
		/*staff api function*/
		int add_staff(void);
		int del_staff(void);
		int change_staff(void);

#endif 
		/*客户端api*/
		int main_interface(void);
		int SubMenu(void);
		int anal_staff(void);
		int R_staff(void);
		int L_staff(void);
		int Q_staff(void);
		int C_staff(void);

#if 0
		int H_staff(void);
#endif 
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
		sPrtcls sd;

		/*用于封装sqlite命令*/
		//	char sql[128];
};
#endif
