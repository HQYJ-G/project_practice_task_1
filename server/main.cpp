/*
 * Name : main.cpp
 * Date : 2020年8月7日
 * Description : 员工管理系统主函数文件
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/

#include <QCoreApplication>
#include "../sql/sqlite.h"
#include "handler.h"
#include "../tcp/tcp.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*声明通信缓存*/
//   sBufType temp;
    sPrtcls Msg;


    /*实例化数据库，tcp，处理信息类*/
    cSqlite sql("employeeinfo.db");
    cMyTcp MyTcp(11115);
    cHandler h(&sql,&Msg,&MyTcp);

//    h.CreateTabe();
    /*
    string aa,bb,cc;
    cPack::InquirePack(Msg,"aa","bb","cc");

    cUnPack::InquireUnPack(Msg,aa,bb,cc);
    cout<<aa<<endl;
    cout<<bb<<endl;
    cout<<cc<<endl;*/
    while(1)
    {
        MyTcp.WaitClient();//等待客户端连接
        memset(&Msg,0,sizeof(sPrtcls));
        MyTcp.RecvMsg(&Msg,sizeof(sPrtcls));
       printf("type%d\n",Msg.type);
        cout<<"接收完成"<<endl;
        h.ClientHandler();
        cout<<"处理完成"<<endl;
        MyTcp.SendMsg(&Msg,sizeof(sPrtcls));
        sleep(1);
    }

    return a.exec();
}
