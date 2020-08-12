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
#include"../sql/sqlite.h"
#include<string.h>
#include "../tcp/tcp.h"

/*
  *名称：      构造函数
  *功能：      初始化变量
  * 参数：     Sqlite *sql1 数据库对象指针：sPrtcls *Msg1消息对象指针
  * 返回值： 无
*/
cHandler::cHandler(cSqlite *sql1,sPrtcls *Msg1,cMyTcp *Tcp1)
{
    sql= sql1;
    Msg = Msg1;
    Tcp = Tcp1;
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
    AddNewUser("root","0","0","0","0","ROOT","root");
    return 0;
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

/*
  *名称：      SelectID
  *功能：      根据ID进行查找
  * 参数：     string Table表名;string Name名字；
  * 返回值： 无
*/
int cHandler::SelectID(string Table,string ID)
{
    return sql->Select(Table,"ID="+ID);
}

/*
  *名称：      SelectName
  *功能：      根据Name进行查找
  * 参数：     string Table表名;string Name名字；
  * 返回值： 无
*/
int cHandler::SelectName(string Table,string Name)
{
    return sql->Select(Table,"Name=\""+Name+"\"");
}

/*
  *名称：      UpDataID
  *功能：      根据ID修改数据；
  * 参数：
  * 返回值： 无
*/
int cHandler::UpDataID(string table,string ID,string key,string val)
{
    string temp;
    string temp2;

    temp = "ID="+ID;
    temp2 = key + "=" + val;

    return sql->Updata(table,temp,temp2);
}
/*
  *名称：      ClientHandler
  *功能：      处理客户端消息；
  * 参数：
  * 返回值： 无
*/
int cHandler::ClientHandler()
{


    switch (Msg->type)
    {
        case DISCONNECT:
            DisConnect();
            cout<<"DisConnetc"<<endl;
            break;
        case LOGIN:
            Login();
            /*
            cout<<"Name"<<ClientInfo[Tcp->Getcfd()].Name<<endl;
            cout<<"ID"<<ClientInfo[Tcp->Getcfd()].ID<<endl;
            cout<<"Auth"<<ClientInfo[Tcp->Getcfd()].Auth<<endl;
            cout<<"fd"<<ClientInfo[Tcp->Getcfd()].fd<<endl;
            cout<<"ip"<<ClientInfo[Tcp->Getcfd()].ip<<endl;
            cout<<"port"<<ClientInfo[Tcp->Getcfd()].port<<endl;
            */
            break;
        case REGISTER:
            Register();
            cout<<"Register"<<endl;
            break;
        case INQUIRE:
 //       strcpy(Msg->buf,"aaaaaa");
            cout<<"Inquire"<<endl;
           Inquire();
           break;
        case UPDATA:
            UpData();
            cout<<"DisConnetc"<<endl;
            break;
        case CONNECT:
            cout<<"Connetc"<<endl;
            Connect();
            break;
        default:

            break;
    };

    return 0;
};

void cHandler::DisConnect()
{
    ClientInfo[Tcp->Getcfd()].Name.clear();
    ClientInfo[Tcp->Getcfd()].ID.clear();
    ClientInfo[Tcp->Getcfd()].ip.clear();
    ClientInfo[Tcp->Getcfd()].Auth=USER;
    ClientInfo[Tcp->Getcfd()].port = 0;
    ClientInfo[Tcp->Getcfd()].fd = 0;
    Tcp->CloseNow();
}
/*
  *名称：      Login
  *功能：      处理登录信息；
  * 参数：     无
  * 返回值： 无
*/
void cHandler::Login()
{
    sBufType Temp;

    sql->CleanBuf();
    if (SelectInfoName(Msg->name) == -1)
    {
       strcpy(Msg->buf,"Failed");
       return ;
    }
    ClientInfo[Tcp->Getcfd()].Name = Msg->name;

 //   ClientInfo[Tcp->Getcfd()].Name.assign(Msg->name);

    do
    {
        sql->QueueOut(Temp);
        if (Temp.num == 0)
        {
             strcpy(Msg->buf,"Failed");
             return ;
        }
        cout<<Temp.key<<endl;
        if (Temp.key == "ID")
        {
            ClientInfo[Tcp->Getcfd()].ID = Temp.val;
        }

        if (Temp.key == "Auth")
        {

            if (Temp.val == "ROOT")
            {
                ClientInfo[Tcp->Getcfd()].Auth = ROOT;
            }else
            {
                ClientInfo[Tcp->Getcfd()].Auth = USER;
            }
            /*
            if (strncmp("USER",Temp.val.c_str(),4))
            {
                if (Msg->authority == ROOT)
                {
                    strcpy(Msg->buf,"Failed");
                   return ;
                }
            }*/
        }
    }while(Temp.key != "Pwd");

    sql->CleanBuf();

    if (Temp.val == Msg->pwd)
    {
        Msg->authority = ClientInfo[Tcp->Getcfd()].Auth;
        strcpy(Msg->buf,"OK");
    }else
    {
        strcpy(Msg->buf,"Failed");
    }
}

/*
  *名称：      Register
  *功能：      注册信息处理；
  * 参数：     无
  * 返回值： 无
*/

void cHandler::Register()
{
    string Name;
    string Pwd;
    string Gender;
    string Wage;
    string Age;
    string Tel;

    cUnPack::RegisterUnPack(*Msg,Name,Pwd,Gender,Wage,Age,Tel);
    if (AddNewUser(Name,Age,Gender,Tel,Wage,"USER",Pwd) == -1)
    {
        strcpy(Msg->buf,"Failed");
        return ;
    }
    strcpy(Msg->buf,"OK");
    return ;
}

/*
  *名称：      Inquire
  *功能：      查询信息处理；
  * 参数：     无
  * 返回值： 无
*/
void cHandler::Inquire()
{
    string temp;
    string temp2;
    string temp3;
    string table;
    string Name;
    string ID;
    sBufType temp4;
    int i;
    sql->CleanBuf();
    cUnPack::InquireUnPack(*Msg,table,Name,ID);
    if(ClientInfo[Tcp->Getcfd()].Auth == ROOT)
    {
//        CharHandler(Msg->buf,temp,temp2);
       SelectName(table,Name);
        cout<<"ROOT"<<endl;
     }else
    {
        SelectName(table,ClientInfo[Tcp->Getcfd()].Name);
        cout<<"USER"<<endl;
     }

    temp3.clear();
    while(!sql->Buf.empty()) //出队信息打包到BUF
    {

        sql->QueueOut(temp4);
//        temp3 += temp4.val+"|";
        temp3 += (temp4.key+":"+temp4.val+"\n");
    }
    cout<<temp3<<endl;
    memset(Msg->buf,0,sizeof(Msg->buf));
    strncpy(Msg->buf,temp3.c_str(),MIN(temp3.size(),sizeof(Msg->buf)));
    Msg->authority = ClientInfo[Tcp->Getcfd()].Auth;

    return;
}

/*
  *名称：      CharHandler
  *功能：      分割字符串；
  * 参数：     无
  * 返回值： 无
*/
void cHandler::CharHandler(string Msg,string &a,string &b)
{
    int Pos1;

    Pos1 = Msg.find(",");
    a = Msg.substr(0,Pos1);
    b = Msg.substr(Pos1+1,Msg.size()-Pos1);
}

/*
  *名称：      UpData
  *功能：      修改数据；
  * 参数：     无
  * 返回值： 无
*/
void cHandler::UpData()
{
    string ID;
    string key;
    string val;

    cUnPack::UpdataUnPack(*Msg,ID,key,val);

    if (UpDataID("info",ID,key,val) == -1)
    {
        strcpy(Msg->buf,"Failed");
        return;
    }
    strcpy(Msg->buf,"OK");
    Msg->authority = ClientInfo[Tcp->Getcfd()].Auth;
}

void cHandler::Connect()
{

    ClientInfo[Tcp->NewClient.fd].ip = Tcp->NewClient.ip;
    ClientInfo[Tcp->NewClient.fd].fd = Tcp->NewClient.fd;
    ClientInfo[Tcp->NewClient.fd].port = Tcp->NewClient.port;
    cout<<"Connect ok"<<endl;
}
