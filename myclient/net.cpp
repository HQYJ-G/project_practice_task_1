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

using namespace std;

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
				close(evts[i].data.fd);
				epoll_ctl(efd,EPOLL_CTL_DEL, evts[i].data.fd, &evt);
				printf("cfd :%d exit\n",evts[i].data.fd);
				continue;
			}else{
				NET::anal_staff();
			}
		}
	}

	return 0;
}

/*******staff api***********/

/*
 * function:    客户端主界面
 * @param [ in] NULL
 * @param [out] NULL
 * @return      0
 */


int NET::main_interface(void){
	int n;

	cout << "**********************" << endl;
	cout << "1:注册  2:登陆  3:退出" << endl; 
	cout << "**********************" << endl;
	cout << "请输入你的选项：";
	cin >> n;

	switch(n){
	case 1:
		NET::R_staff();
		break;
	case 2:
		if(L_staff() == 1){
			NET::SubMenu();
		}else{
			cout << "用户名或者密码错误！" << endl;
			break;
		}
	case 3:
		close(fd);
		exit(0);
	default:
		cout << "输入错误！清重新输入！！！！！" << endl;
	}

	return 0;
}

/*
 * function:   登陆成功后的菜单 
 * @param [ in] 无
 * @param [out] 无
 * @return      0
 */
int NET::SubMenu(void){
//	printf("%s\n",__FUNCTION__);
	cout << "**********************" << endl;
	cout << "1:查询  2:修改  3:退出" << endl;
	cout << "**********************" << endl;

	int n;
	cout << "请输入你的选项:";
	cin >> n;

	switch(n){
	case 1:
		NET::Q_staff();
		break;
	case 2:
		NET::C_staff();
		break;
	case 3:
		close(fd);
		exit(0);
	default:
		cout << "输入错误！清重新输入！！！！！" << endl;
	}

	return 0;

}


/*
 * function:    注册员工信息
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int NET::R_staff(void){

	bzero(&sd, sizeof(sd));
	sd.type = REGISTER;
	sd.authority = USER;


	printf("please name:");
	scanf("%s",sd.name);
	getchar();

	printf("please passwd:");
	scanf("%s",sd.pwd);
	getchar();
#if 0
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

	printf("%s-%s-%s-%d-%s-%s-%d\n",sd.name, sd.passwd, sd.sex, sd.age,\
			sd.phone, sd.addr, sd.menoy);

#endif
	cout << "name " << sd.name << "  " << "pwd " << sd.pwd << endl;

	if(send(fd,&sd,sizeof(sd), 0) == -1){
		cout << "send err!" << endl;
	}else{
		cout << "send ok!" << endl;
	}

	return 0;
}

/*
 * function:    实现登陆功能
 * @param [ in] 无
 * @param [out] 无
 * @return  	成功返回1   
 */
int NET::L_staff(void){
	sd.type = LOGIN;
	
	cout << "*****************" << endl;
	cout << "1:普通用户 2:root" << endl;
	cout << "*****************" << endl;

	int n;
	cout << "输入选项:";
	cin >> n;

	if(n < 1 || n > 2){
		cout << "输入错误！" << endl;
		exit(-1);
	}

	if(n == 1){
		sd.authority = USER;
	}else{
		sd.authority = ROOT;
	}

	cout << "名字:";
	cin >> sd.name ;
	cout << "密码:";
	cin >> sd.pwd;

	if(send(fd,&sd,sizeof(sd), 0) == -1){
		cout << "send err!" << endl;
		exit(-1);
	}else{
		cout << "send ok!" << endl;
	}

	if(recv(fd,&sd,sizeof(sd), 0) == -1){
		cout << "recv err!" << endl;
		exit(-1);
	}

	if(strncmp(sd.buf,"OK",2) == 0){
		return 1;
	}

	return 0;
}

/*
 * function:   登陆成功后的菜单 
 * @param [ in] 无
 * @param [out] 无
 * @return      0
 */
int NET::Q_staff(void){
//	printf("%s\n",__FUNCTION__);
	sd.type = INQUIRE;

	cout << "要查询的名字:";
	cin >> sd.name;

	if(send(fd,&sd,sizeof(sd), 0) == -1){
		cout << "send err!" << endl;
		exit(-1);
	}else{
		cout << "send ok!" << endl;
	}

	if(recv(fd,&sd,sizeof(sd), 0) == -1){
		cout << "recv err!" << endl;
		exit(-1);
	}

	cout << sd.buf << endl;

	return 0;

}


/*
 * function:    修改员工信息  
 * @param [ in] 无
 * @param [out] 无
 * @return      0
 */
int NET::C_staff(void){
//	printf("%s\n",__FUNCTION__);

	cout << "要修改的信息,以id为准" << endl;
	cout << "请先查询此员工的id号" << endl;





	return 0;

}


/*
 * function:    解析员工操作
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int NET::anal_staff(void){

	return 0;

}


#if 0

/**************************/
/*
 * function:    
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int ST::del_staff(void){
	sd.type = D;

	printf("delste id:");
	scanf("%d",&sd.id);

	return 0;
}
/*
 * function:    修改员工信息
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









/*
 * function:    
 * @param [ in] 
 * @param [out] 
 * @return      
 */
int NET::H_staff(void){
	printf("%s\n",__FUNCTION__);


	return 0;

}
#endif 
#endif
