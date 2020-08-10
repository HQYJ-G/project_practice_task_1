/*
 * Name : protocol.h
 * Date : 2020年8月7日
 * Description : 用于客户端服务器通信的结构体和解析
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/


#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include<iostream>
#include<queue>

using namespace std;

const unsigned int NAME_MAX  =  32;
const unsigned int BUF_MAX = 256;

typedef enum
{
    LOGIN = 0,//登录
    REGISTER,//注册
    INQUIRE,//查询
	CHANGE,//修改

}eCmdType;

typedef enum
{
    USER = 0,//用户
    ROOT,//管理员

}eAuthorityType;

typedef struct
{
    eCmdType type;//客户端发送的命令
    char name[NAME_MAX];//用户名
    char pwd[NAME_MAX];//密码
    eAuthorityType authority;//用户权限
	char sex[1];//性别
	unsigned int age;//年龄
	char phone[12];//手机
	char addr[56];//地址
	unsigned int menoy;//工资
    char buf[256];//消息缓存
}sPrtcls;


class MsgHandler
{
	private:
		queue<struct ServerToClient> data;
	public:
		

};

#endif
