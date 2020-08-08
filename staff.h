/*******************************************************************************
 * staff.h 
 *
 * @fcopyright  Copyright 2020 hua qing yuan jian .
 * @fauthor     [Zhou ZhenQuan] [zhouzhenquan0310@qq.com]
 * @fversion    1.0
 *
 * @fhistory    [2020-08-08] Create file.
 ******************************************************************************/

#define NAME_SIZE 32
#define PHONE_SIZE 12
#define ADDR_SIZE 128


#ifndef __STAFF_H__
#define __STAFF_H__

/*
 * 1:姓名
 * 2:性别
 * 3:年龄
 * 4:电话
 * 5:地址
 * 6:薪资
 * 7:工作号---用于服务器分配该员工的id
 */
struct staff
{
	char name[NAME_SIZE];
	char sex[4];
	unsigned int  age;
	char phone[PHONE_SIZE];
	char addr[ADDR_SIZE];
	unsigned int menoy;
	unsigned int id;

};

#endif
