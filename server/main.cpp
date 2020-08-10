#include <QCoreApplication>
#include "../sql/sqlite.h"
#include "handler.h"
#include "../tcp/tcp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    sBufType temp;
    sPrtcls Msg;

    cSqlite sql("employeeinfo.db");
    cHandler h(&sql,&Msg);

    cMyTcp MyTcp(11111);

    MyTcp.WaitClient();

    strcpy(Msg.buf,"aaa");
    MyTcp.SendMsg(&Msg,sizeof(sPrtcls));
//    h.CreateTabe();
    /*
    sql.CreateTable("Info"," ID INTEGER PRIMARY KEY   AUTOINCREMENT,Name TEXT NOT NULL,Age INT ,Gender TEXT,TEL TEXT, Wage INT, Auth TEXT, Pwd TEXT");
    sql.CreateTable("Attend","ID INTEGER PRIMARY KEY, Name Text, Time Text");
    sql.CreateTable("Log","ID INTEGER PRIMARY KEY, Name Text,Time Text,Spoor Text");

    sql.Insert("Attend","ID,Name,Time","1,\"X\",\"2002-01-02\"");
    sql.Insert("Log","ID,Name,Time","1,\"X\",\"2002-01-02\"");

    sql.Insert("info","NAME,AGE,GENDER","\"X\",18,\"man\"");
    sql.Insert("info","NAME,AGE,GENDER","\"s\",18,\"man\"");
    sql.Select("info","ID = 1");

    while(!sql.Buf.empty())
    {
        temp = sql.Buf.front();
        sql.Buf.pop();
        cout<<temp.key<<"="<<temp.val<<endl;
    }
*/
    return a.exec();
}
