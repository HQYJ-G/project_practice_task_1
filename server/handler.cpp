/*
 * Name : handler.cpp
 * Date : 2020年8月10日
 * Description : 消息处理函数
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/


#include"handler.h"
#include"../protocol.h"
#include"../sql/sqlite.h"
#include<string.h>
/*
  *名称：      构造函数
  *功能：      初始化变量
  * 参数：     Sqlite *sql1 数据库对象指针：sPrtcls *Msg1消息对象指针
  * 返回值： 无
*/
cHandler::cHandler(cSqlite *sql1,sPrtcls *Msg1)
{
    sql= sql1;
    Msg = Msg1;
}

/*
  *名称：      析构函数
  *功能：      无
  * 参数：     无
  * 返回值： 无
*/
cHandler::~cHandler()
{

}

/*
  *名称：      CreateTabe
  *功能：      创建Info Attend Log表函数
  * 参数：     无
  * 返回值： 无
*/
int cHandler::CreateTabe(void)
{
    sql->CreateTable("Info"," ID INTEGER PRIMARY KEY   AUTOINCREMENT,Name TEXT NOT NULL,Age INT ,Gender TEXT,TEL TEXT, Wage INT, Auth TEXT, Pwd TEXT");
    sql->CreateTable("Attend","ID INTEGER, Name Text, Time Text");
    sql->CreateTable("Log","ID INTEGER, Name Text,Time Text,Spoor Text");
}

/*
  *名称：      AddNewUser
  *功能：      在Info表中添加新的员工信息
  * 参数：     string Name 姓名；string Age 年龄；string Gender 性别；string Tel 电话；string Wage 工资；string Auth 权限；string Pwd 密码；
  * 返回值： 无
*/
int cHandler::AddNewUser(string Name,string Age,string Gender,string Tel,string Wage,string Auth,string Pwd)
{
    return sql->Insert("Info","Name,Age,Gender,Tel,Wage,Auth,Pwd","\""+Name+"\""+","+Age+","+"\""+Gender+"\""+","+"\""+Tel+"\""+","+Wage+","+"\""+Auth+"\""+","+"\""+Pwd+"\"");
}

/*
  *名称：      AddAttend
  *功能：      在Attend表中添加员工考勤信息
  * 参数：     string ID 工号；string Name姓名；string Data日期时间；
  * 返回值： 无
*/
int cHandler::AddAttend(string ID,string Name,string Data)
{
    return sql->Insert("Attend","ID,Name,Time",ID+","+"\""+Name+"\""+","+"\""+Data+"\"");
}

/*
  *名称：      AddLog
  *功能：      在Log表中添加操作记录
  * 参数：     string ID 工号；string Name姓名；string Data日期时间；string Spoor 操作记录；
  * 返回值： 无
*/
int cHandler::AddLog(string ID,string Name,string Data,string Spoor)
{
    return sql->Insert("Log","ID,Name,Time",ID+","+"\""+Name+"\""+","+"\""+Data+"\""+"\""+Spoor+"\"");
}

/*
  *名称：      SelectInfoID
  *功能：      在Info表中根据工号查找员工信息
  * 参数：     string ID 工号；
  * 返回值： 无
*/
int cHandler::SelectInfoID(string ID)
{
    return sql->Select("Info","ID="+ID);
}

/*
  *名称：      SelectInfoName
  *功能：      在Info表中根据名字查找员工信息
  * 参数：     string Name名字；
  * 返回值： 无
*/
int cHandler::SelectInfoName(string Name)
{
    return sql->Select("Info","Name=\""+Name+"\"");
}

/*
  *名称：      SelectAttendID
  *功能：      在Info表中根据工号查找员工信息
  * 参数：     string ID 工号；
  * 返回值： 无
*/
int cHandler::SelectAttendID(string ID)
{
    return sql->Select("Attend","ID="+ID);
}

/*
  *名称：      SelectAttendName
  *功能：      在Info表中根据名字查找员工信息
  * 参数：     string Name名字；
  * 返回值： 无
*/
int cHandler::SelectAttendName(string Name)
{
    return sql->Select("Attend","Name=\""+Name+"\"");
}

/*
  *名称：      SelectLogID
  *功能：      在Info表中根据工号查找员工信息
  * 参数：     string ID 工号；
  * 返回值： 无
*/
int cHandler::SelectLogID(string ID)
{
    return sql->Select("Log","ID="+ID);
}

/*
  *名称：      SelectLogName
  *功能：      在Info表中根据名字查找员工信息
  * 参数：     string Name名字；
  * 返回值： 无
*/
int cHandler::SelectLogName(string Name)
{
    return sql->Select("Log","Name=\""+Name+"\"");
}


int cHandler::ClientHandler()
{
    sBufType Temp;

    switch (Msg->type)
    {
        case LOGIN:
            SelectInfoName(Msg->name);

            do
            {
                sql->QueueOut(Temp);
                if (Temp.key == "Auth")
                {
                    Msg->authority = Temp.val=="root"?ROOT:USER;
                }
            }while(Temp.key != "Pwd");

            if (Temp.val == Msg->pwd)
            {
                strcpy(Msg->buf,"OK");
                return 0;
            }

            strcpy(Msg->buf,"Failed");
            return -1;

        case REGISTER:

            break;
        case INQUIRE:

            break;
        default:

            break;
    };

    return 0;
};

