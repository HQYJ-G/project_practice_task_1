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

class cHandler
{
    private:
        cSqlite *sql;
        sPrtcls *Msg;
 //       const string quoting = "\"";
    public:

        cHandler(cSqlite *sql1,sPrtcls *Msg1);
        ~cHandler();

        int CreateTabe(void);
        int AddNewUser(string Name,string Age,string Gender,string Tel,string Wage,string Auth,string Pwd);
        int AddAttend(string ID,string Name,string Data);
        int AddLog(string ID,string Name,string Data,string Spoor);
        int SelectInfoID(string ID);
        int SelectInfoName(string Name);
        int SelectAttendID(string ID);
        int SelectAttendName(string Name);
        int SelectLogID(string ID);
        int SelectLogName(string Name);
        int ClientHandler();

};

#endif // HANDLER_H
