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

const unsigned int CMD_MAX  =  32;
const unsigned int PARA_MAX  =  128;
const unsigned int MSG_MAX  =  512;

struct ClientToServer 
{
    char cmd[CMD_MAX];//客户端发送的命令
    char para[PARA_MAX ];//命令的参数
};

struct ServerToClient
{
    char msg[MSG_MAX] ;//服务端返回的消息
	unsigned int pic;//未发送消息数量
};


class MsgHandler
{
	private:
		queue<struct ServerToClient> data;
	public:
		

};

#endif
