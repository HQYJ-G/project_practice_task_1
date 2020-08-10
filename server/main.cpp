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
    cMyTcp MyTcp(11115);
    cHandler h(&sql,&Msg,&MyTcp);
    h.CreateTabe();


    MyTcp.WaitClient();
    while(1)
    {
        MyTcp.RecvMsg(&Msg,sizeof(sPrtcls));
        h.ClientHandler();
        cout<<"bb"<<endl;
        MyTcp.SendMsg(&Msg,sizeof(sPrtcls));
    }

    return a.exec();
}
