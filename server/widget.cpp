#include "widget.h"
#include "ui_widget.h"
#include "../sql/sqlite.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    sBufType temp;

    ui->setupUi(this);
    Sqlite sql("employeeinfo.db");
    sql.CreateTable("info"," ID INTEGER PRIMARY KEY   AUTOINCREMENT,NAME TEXT NOT NULL,AGE INT ,GENDER TEXT,TEL TEXT, WAGE INT, AUTH TEXT, PWD TEXT");
    sql.Insert("info","NAME,AGE,GENDER","\"X\",18,\"man\"");
    sql.Insert("info","NAME,AGE,GENDER","\"s\",18,\"man\"");
    sql.Select("info","ID = 1");
    while(!sql.Buf.empty())
    {
        temp = sql.Buf.front();
        sql.Buf.pop();
        cout<<temp.key<<"="<<temp.val<<endl;
    }
 //   sql.Updata("info","NAME = \"X\"","AGE = 20");
//    sql.Delect("info","AGE = 20");
}

Widget::~Widget()
{
    delete ui;
}
