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

/*
const int NAME_MAX  =  32;
const int BUF_MAX = 256;
*/

typedef enum
{
    DISCONNECT = 0,//断开标志
    LOGIN = 1,//登录
    REGISTER = 2,//注册
    INQUIRE = 3,//查询
    UPDATA = 4,//修改权限
    CONNECT= 5,//连接标志
}eCmdType;

typedef enum
{
    USER = 0,//用户
    ROOT,//管理员

}eAuthorityType;

typedef struct
{
    eCmdType type;//客户端发送的命令
    char name[32];//用户名
    char pwd[32];//密码
    eAuthorityType authority;//用户权限
        char sex[1];//性别
        unsigned int age;//年龄
        char phone[12];//手机
        char addr[56];//地址
        unsigned int menoy;//工资
    char buf[256];//消息缓存
}sPrtcls;


typedef struct
{
    char gender[6];//性别
    char age[4];//年龄
    char Tel[12];//电话
    char wage[8];//工资
}sPersonel;

typedef struct
{
    char table[16];
    char name[16];
    char id[16];
}sInquir;

typedef struct
{
    char key[16];
    char val[32];
    char id[16];
}sUpdata;

inline size_t MIN(size_t a,size_t b)
{
    return  a<b?a:b;
};

class cPack
{
    private:

    public:
        static void LoginPack(sPrtcls &Msg, string Name,string Pwd);
        static void RegisterPack(sPrtcls &Msg, string Name,string Pwd,string Gender,string Wage, string Age,string Tel);
        static void InquirePack(sPrtcls &Msg,string table,string Name,string ID);
        static void UpdataPack(sPrtcls &Msg,string ID,string key,string val);
};

class cUnPack
{

    public:
        static void LoginUnPack(sPrtcls &Msg, string &Name,string &Pwd);
        static void RegisterUnPack(sPrtcls &Msg, string &Name,string &Pwd,string &Gender,string &Wage, string &Age,string &Tel);
        static void InquireUnPack(sPrtcls &Msg,string &table,string &Name,string &ID);
        static void UpdataUnPack(sPrtcls &Msg,string &ID,string &key,string &val);
};


#endif
