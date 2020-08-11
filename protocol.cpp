/*
 * Name : protocol.cpp
 * Date : 2020年8月7日
 * Description : 用于客户端服务器通信的结构体和解析
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/

#include "protocol.h"
#include<string.h>

/*
  *名称：      LoginPack
  *功能：      登录信息打包
  * 参数：     输出：sPrtcls &Msg
  *                  输入：tring Name,string Pwd
  * 返回值： 无
*/
void cPack::LoginPack(sPrtcls &Msg, string Name,string Pwd)
{
   memset(&Msg,0,sizeof(sPrtcls));

    Msg.type = LOGIN;

   Name.copy(Msg.name,MIN(sizeof(Msg.name),Name.size()));
   Pwd.copy(Msg.pwd,MIN(sizeof(Msg.pwd),Name.size()));
}

/*
  *名称：      RegisterPack
  *功能：      注册信息打包
  * 参数：     输出:sPrtcls &Msg
  *                  输入: string Name,string Pwd,string Gender,unsigned int Wage, unsigned int Age,string Tel
  * 返回值： 无
*/
void cPack::RegisterPack(sPrtcls &Msg, string Name,string Pwd,string Gender,string Wage, string Age,string Tel)
{
    sPersonel temp;

    memset(&Msg,0,sizeof(sPrtcls));
    memset(&temp,0,sizeof(sPersonel));

    Msg.type = REGISTER;

    Name.copy(Msg.name,MIN(sizeof(Msg.name),Name.size()));
    Pwd.copy(Msg.pwd,MIN(sizeof(Msg.pwd),Name.size()));
    Gender.copy(temp.gender,MIN(sizeof(temp.gender),Gender.size()));
    Wage.copy(temp.wage,MIN(sizeof(temp.wage),Wage.size()));
    Age.copy(temp.age,MIN(sizeof(temp.age),Age.size()));
    Tel.copy(temp.Tel,MIN(sizeof(temp.Tel),Tel.size()));

    memcpy(Msg.buf,&temp,sizeof(sPersonel));

}

void InquirePack(sPrtcls &Msg,string table,string Name,string ID)
{
    sInquir temp;

    memset(&Msg,0,sizeof(sPrtcls));
    memset(&temp,0,sizeof(sInquir));

    Msg.type = INQUIRE;

    table.copy(temp.table,MIN(table.size(),sizeof(temp.table)));
    Name.copy(temp.name,MIN(Name.size(),sizeof(temp.name)));
    ID.copy(temp.id,MIN(ID.size(),sizeof(temp.id)));

    memcpy(Msg.buf,&temp,sizeof(sInquir));
};

void UpdataPack(sPrtcls &Msg,string ID,string key,string val)
{
    sUpdata temp;

    memset(&Msg,0,sizeof(sPrtcls));
    memset(&temp,0,sizeof(sUpdata));

    Msg.type = UPDATA;

    ID.copy(temp.id,MIN(ID.size(),sizeof(temp.id)));
    key.copy(temp.key,MIN(sizeof(sUpdata),key.size()));
    val.copy(temp.val,MIN(sizeof(sUpdata),val.size()));

    memcpy(Msg.buf,&temp,sizeof(sUpdata ));
};

/*
  *名称：      LoginPack
  *功能：      登录信息解包
  * 参数：     输出：tring Name,string Pwd
  *                  输入：sPrtcls &Msg
  * 返回值： 无
*/
void cUnPack::LoginUnPack(sPrtcls &Msg, string &Name,string &Pwd)
{
    Name = Msg.name;
    Pwd = Msg.pwd;
}

/*
  *名称：      RegisterPack
  *功能：      注册信息解包
  * 参数：     输出:string &Name,string &Pwd,string &Gender,unsigned int &Wage, unsigned int &Age,string &Tel
  *                  输入: sPrtcls &Msg,
  * 返回值： 无
*/
void cUnPack::RegisterUnPack(sPrtcls &Msg, string &Name,string &Pwd,string &Gender,string &Wage, string &Age,string &Tel)
{
    sPersonel temp;

    memcpy(&temp,Msg.buf,sizeof(sPersonel));

    Name = Msg.name;
    Pwd = Msg.pwd;
    Gender = temp.gender;
    Wage = temp.wage;
    Age = temp.age;
    Tel = temp.Tel;
}

void cUnPack::InquireUnPack(sPrtcls &Msg,string &table,string &Name,string &ID)
{
    sInquir temp;

    memcpy(&temp,Msg.buf,sizeof(sInquir));

    table = temp.table;
    Name = temp.name;
    ID = temp.id;

}

void cUnPack::UpdataUnPack(sPrtcls &Msg,string &ID,string &key,string &val)
{
    sUpdata temp;

    memcpy(&temp,Msg.buf,sizeof(sUpdata));

    ID = temp.id;
    key = temp.key;
    val = temp.val;
}
