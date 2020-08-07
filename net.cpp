#include "net.h"

/*
 * function:    创建套接子
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int NET::socket_init(void){
	if((serfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		printf("socket failed\n");
		return -1;
	}

	return serfd;
}

/*
 * function:    套接子地址绑定
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */

int NET::bind_init(void){
	bzero(&servaddr,0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr(IP);

	if(bind(serfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) != 0){
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
int NET::linsten_init(void){
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

int NET::accept_init(void){
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

int NET::connect_init(void){
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

int NET::epoll_init(void){
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
int NET::epoll_add(void){
	
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

int NET::epoll_del(void){
	if(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &ev) == -1){
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

int NET::epoll_waits(void){
	if((nfds = epoll_wait(epoll_fd, evs, EPOLL_SIZE, -1)) == -1){
		printf("epoll_wait failed\n");
		return -1;
	}

	return 0;
}

