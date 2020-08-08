/*******************************************************************************
 * staff.h 
 *
 * @fcopyright  Copyright 2020 hua qing yuan jian .
 * @fauthor     [Zhou ZhenQuan] [zhouzhenquan0310@qq.com]
 * @fversion    1.0
 *
 * @fhistory    [2020-08-08] Create file.
 ******************************************************************************/

#ifndef __STAFF_H__
#define __STAFF_H__


#include <stdio.h>
#include <stdlib.h>


#define NAME_SIZE 32
#define PHONE_SIZE 12
#define ADDR_SIZE 128

#define R 0
#define L 1
#define Q 2
#define C 3
#define D 4


/*
 * 1:姓名
 * 2:性别
 * 3:年龄
 * 4:电话
 * 5:地址---也用于修改信息
 * 6:薪资
 * 7:工作号---用于服务器分配该员工的id
 */
struct staff
{
	int type;
	char name[NAME_SIZE];
	char sex[4];
	unsigned int  age;
	char phone[PHONE_SIZE];
	char addr[ADDR_SIZE];
	unsigned int menoy;
	unsigned int id;
};


	


#endif