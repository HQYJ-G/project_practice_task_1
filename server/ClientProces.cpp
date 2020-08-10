/*
 * Name : ClientProces.cpp
 * Date : 2020年8月10日
 * Description : 消息处理函数
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/

#include"../protocol.h"
#include"../sql/sqlite.h"

int handler(sPrtcls &Msg,Sqlite &data)
{

    switch (Msg.type)
    {
        case LOGIN:

            break;
        case REGISTER:

            break;
        case INQUIRE:

            break;
        default:

            break;
    };

    return 0;
};
