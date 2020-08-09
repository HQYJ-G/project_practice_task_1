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
 //   sql.Updata("info","NAME = \"X\"","AGE = 20");
//    sql.Delect("info","AGE = 20");
}

Widget::~Widget()
{
    delete ui;
}
