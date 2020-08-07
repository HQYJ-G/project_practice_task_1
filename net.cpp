#include "net.h"



int NET::socket_init(){
	if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		return -1;
	}else{
		printf("fd;%d\n",fd);
	}
	return 0;
};
int NET::bind_init(){
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
int NET::listen_init(){
	if(listen(fd,5) != 0)
		return -1;
	else
		printf("listen....\n");
	return 0;
};

int NET::accept_init(){
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

int NET::connect_init(){
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

