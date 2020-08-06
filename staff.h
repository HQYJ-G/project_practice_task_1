#ifndef __STAFF_H__
#define __STAFF_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sqlite3.h>
class SS{

public:

	int sock_init(void);
	int sock_bind(void);
	int sock_listen(void);
	int sock_accept(void);
	int sock_connect(void);

	int sq_create(void);
	int sq_close(void);
	int sq_exec(void);


	int insert_data(void);
	int delete_data(void);
	int change_data(void);
	void show_data(void);


private:
/* 			 员工基本信息     	      */
/* 1:名字 2:性别 3:年龄 4:电话 5:住址 */
	char name[32];
	char sex[8];
	char age[2];
	char phone[12];
	char address[128];
/* 		要操作的成员 	*/
/* 1:数据库句柄指针  
 * 2:服务器和客户端的文件描述符 */
	sqlite3 *db;
	int serfd,clifd;

};



#endif
