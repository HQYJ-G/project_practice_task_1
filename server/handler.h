/*
 * Name : handler.h
 * Date : 2020年8月10日
 * Description : 消息处理函数
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/


#ifndef HANDLER_H
#define HANDLER_H

#include"../protocol.h"
#include"../sql/sqlite.h"
#include"../tcp/tcp.h"
#include<list>
typedef struct
{
    string ID;
    string Name;
    eAuthorityType Auth;
    int fd;
    string ip;
    short port;
}sOnlineInfo;

class cHandler
{
    private:
        cSqlite *sql;
        sPrtcls *Msg;
        cMyTcp *Tcp;
        sOnlineInfo ClientInfo[100];

 //       const string quoting = "\"";
    public:

        cHandler(cSqlite *sql1,sPrtcls *Msg1,cMyTcp *Tcp1);
        ~cHandler();

        int CreateTabe(void);
        int AddNewUser(string Name,string Age,string Gender,string Tel,string Wage,string Auth,string Pwd);
        int AddAttend(string ID,string Name,string Data);
        int AddLog(string ID,string Name,string Data,string Spoor);
        int SelectID(string Table,string ID);
        int SelectName(string Table,string Name);
        int SelectInfoID(string ID);
        int SelectInfoName(string Name);
        int SelectAttendID(string ID);
        int SelectAttendName(string Name);
        int SelectLogID(string ID);
        int SelectLogName(string Name);
        int UpDataID(string table,string ID,string key,string val);
        int ClientHandler();
        void CharHandler(string Msg,string &a,string &b);
        void DisConnect();
        void Inquire();
        void Login();
        void Register();
        void UpData();
        void Connect();

};

#endif // HANDLER_H
