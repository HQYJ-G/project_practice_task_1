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

typedef struct
{
    string ID;
    string Name;
    string Auth;
    int fd;
    string ip;
}sOnlineInfo;

class cHandler
{
    private:
        cSqlite *sql;
        sPrtcls *Msg;
        cMyTcp *Tcp;
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
        int ClientHandler();
        void CharHandler(string Msg,string &a,string &b);
        void Inquire();
        void Login();
        void Register();
        void test();

};

#endif // HANDLER_H
