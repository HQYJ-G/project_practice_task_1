/*
 * Name : protocol.h
 * Data : 2020年8月7日
 * Description : 用于客户端服务器通信的结构体和解析
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/


#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__
struct ClientToServer 
{
	char cmd[32];//客户端发送的命令
	char para[128];//命令的参数
}

struct ServerToClient
{
	char[512] msg;//服务端返回的消息
	unsigned int pic;//未发送消息数量
}

#endif
