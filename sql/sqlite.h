/*
 * Name : sqlite.h
 * Date : 2020年8月7日
 * Description : 数据库增删改查
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/


#ifndef __SQLITE_H__
#define __SQLITE_H__

#include<sqlite3.h>
#include<iostream>

using namespace std;

class Sqlite
{
	private:
		sqlite3 *db;

	public:
		Sqlite(const string s);
		~Sqlite();
		CreateTable(const string s);
		Select(const string s);
		Insert(const string s);
		Updata(const string s);
		Delect(const string s);
}

#endif
