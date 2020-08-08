/*******************************************************************************
 * net.cpp 
 *
 * @fcopyright  Copyright 2020 hua qing yuan jian .
 * @fauthor     [Zhou ZhenQuan] [zhouzhenquan0310@qq.com]
 * @fversion    1.0
 *
 * @fhistory    [2020-08-08] Create file.
 ******************************************************************************/

#include "net.h"

/*
 * function:    创建套接字
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */


int NET::socket_init(){
	if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket failed\n");
		return -1;
	}else{
		printf("fd;%d\n",fd);
	}
	return 0;
};

/*
 * function:   	绑定套接字
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int NET::bind_init(){
	bzero(&servaddr,0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr(IP);
	if(bind(fd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0){
		perror("bind failed\n");
		return -1;
	}else
		printf("bind ok\n");
	return 0;
};

/*
 * function:   	绑定套接字
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int NET::cbind_init(){
	bzero(&servaddr,0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr(IP);

	return 0;
};


/*
 * function:    监听套接字
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int NET::listen_init(){
	if(listen(fd,5) != 0){
		perror("listen failed\n");
		return -1;
	}else
		printf("listen....\n");
	return 0;
};


/*
 * function:    等待客户端连接
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int NET::accept_init(){
	len = sizeof(cliaddr);
	if((cfd = accept(fd,(struct sockaddr*)&cliaddr,&len)) == -1){
		perror("accpet failed\n");
		return -1;
	}

	return 0;
};


/*
 * function:    向服务器连接
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int NET::connect_init(){
	if(connect(fd,(struct sockaddr*)&servaddr,sizeof(servaddr)) != 0){
		perror("connect failed\n");
		return -1;
	}else
		printf("connect ok\n");

	while(1){
#if 0
		bzero(buf,0);
		fgets(buf,128,stdin);
		send(fd,buf,128,0);

		if(strncmp(buf,"quit",4) == 0)
			break;
#endif 
		bzero(&sd, sizeof(sd));
		NET::add_staff();
		send(fd,&sd,sizeof(sd), 0);

	}

	close(fd);

	return 0;
};

/*
 * function:    创建epoll多路复用
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */


int NET::epoll_init(void){
	if((efd = epoll_create(1)) == -1){
		printf("epoll_create failed\n");
		return -1;
	}

	return 0;
}


/*
 * function:    添加服务器文件描述符到epoll
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */
int NET::sepoll_add(void){
	evt.data.fd = fd;
	evt.events = EPOLLIN | EPOLLET;

	if(epoll_ctl(efd, EPOLL_CTL_ADD, fd, &evt) == -1){
		perror("epoll_ctl fd failed\n");
		return -1;
	}

	return 0;
}

/*
 * function:    添加客户端描述符到epoll
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */
int NET::cepoll_add(void){
	evt.data.fd = cfd;
	evt.events = EPOLLIN | EPOLLET;

	if(epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &evt) == -1){
		perror("epoll add cfd failed\n");
		return -1;
	}


	return 0;
}

#if 1
/*
 * function:    处理有信息的文件描述符
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int NET::epoll_waits(void){
	printf("%s\n",__FUNCTION__);
	int i;
	if((nfds = epoll_wait(efd, evts, EPOLL_SIZE, -1)) == -1){
		perror("epoll wait failed\n");
		return -1;
	}

	for(i = 0; i < nfds; i++){
		if(evts[i].data.fd == fd){
			NET::accept_init();
			NET::cepoll_add();
			continue;
		}else{
			int relen;
			relen = recv(evts[i].data.fd , &sd, sizeof(sd), 0);
			if(relen <= 0){
				printf("cfd :%d exit\n",evts[i].data.fd);
				close(evts[i].data.fd);
				epoll_ctl(efd,EPOLL_CTL_DEL, evts[i].data.fd, &evt);
				continue;
			}else{
				printf("%s-%s-%d-%s-%s-%d\n",sd.name, sd.sex, sd.age,\
						sd.phone, sd.addr, sd.menoy);

			}
		}
	}

	return 0;
}




/*******staff api***********/

/*
 * function:    
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int NET::add_staff(void){

	sd.type = R;

	printf("please name:");
	scanf("%s",sd.name);
	getchar();

	printf("please sex:");
	scanf("%s",sd.sex);
	getchar();

	printf("please age:");
	scanf("%d",&sd.age);
	getchar();

	printf("please phone:");
	scanf("%s",sd.phone);
	getchar();

	printf("please addr:");
	scanf("%s",sd.addr);
	getchar();

	printf("please menoy:");
	scanf("%d",&sd.menoy);
	getchar();

	printf("%s-%s-%d-%s-%s-%d\n",sd.name, sd.sex, sd.age,\
			sd.phone, sd.addr, sd.menoy);


	return 0;
}


/*
 * function:    
 * @param [ in] 
 * @param [out] 
 * @return      
 */
#if 0
int ST::del_staff(void){
	sd.type = D;

	printf("delste id:");
	scanf("%d",&sd.id);

	return 0;
}
#endif
/*
 * function:    
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int NET::change_staff(void){
	sd.type = C;
	int n;

	printf("************************************\n");
	printf("***1: name 2: age 3: phone 4:sex****\n");
	printf("************************************\n");
	printf("change num:");
	scanf("%d",&n);

	switch(n){
	case 1:
		printf("please new name:");
		scanf("%s",sd.addr);
		getchar();
		break;
	case 2:
		printf("please new age:");
		scanf("%d",sd.addr);
		getchar();

		break;
	case 3:
		printf("please new phone:");
		scanf("%s",sd.addr);
		getchar();
		break;
	case 4:
		printf("please new sex:");
		scanf("%s",sd.addr);
		getchar();
		break;
	default:
		printf("num failed\n");
		break;
	}


	printf("%s-%s\n",sd.name, sd.addr);

	return 0;
} 
#endif
