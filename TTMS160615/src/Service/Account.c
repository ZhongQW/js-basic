/*
* account.c
*
*  Created on: 2015年6月12日
*      Author: Administrator
*/
#include "Account.h"
#include "EntityKey.h"
#include "../Common/list.h"
#include "../Persistence/Account_Persist.c"
#include <string.h>
#include <stdlib.h>

extern account_t gl_CurUser;

//创建系统初始化账号admin
void Account_Srv_InitSys() {
	int i, j;
if(Account_Perst_CheckAccFile()) return ;
	{
		account_t data_admin;
		printf("请注册用户类型[1]售票员[2]经理[9]系统管理员\n");
		scanf("%d", &data_admin.type); 
		printf("请注册用户账号\n");
		scanf("%s", data_admin.username); 
		printf("请注册用户密码\n");
		scanf("%s", data_admin.password); 
		data_admin.id = EntKey_Srv_CompNewKey("account");	
		Account_Srv_Add(&data_admin);
	}
}

//验证登录账号是否已存在，存在，保存登录用户信息到全局变量gl_CurUser，return 1；否则return 0
inline int Account_Srv_Verify(char usrName[], char pwd[]) {
	account_t usr;
	if (Account_Perst_SelByName(usrName, &usr) != 0)
	{
		if (strcmp(pwd, usr.password) != 0)
		{
			return 0;
		}
		else
		{
			strcpy(gl_CurUser.username,usr.username);
			strcpy(gl_CurUser.password,usr.password);
			gl_CurUser.id=usr.id;
			gl_CurUser.type=usr.type;
			return 1;
		}
	}
	return 0;
}


//验证用户名是否存在，遍历list，若存在，返回对应结点指针；否则，返回null
account_node_t * Account_Srv_FindByUsrName(account_list_t list, char usrName[]) {
	account_list_t p;
	List_ForEach(list, p)
	{
		if(strcmp(p->data.username,usrName)==0)
		return p;
	}
	return NULL ;	
}

//添加一个用户账号，通过调用Account_Perst_Insert(data)函数实现
inline int Account_Srv_Add(const account_t *data) {
	if (Account_Perst_Insert(data) == 1)
		return 1;
	return 0;
}

//修改一个用户账号，通过调用Account_Perst_Update(data)函数实现
inline int Account_Srv_Modify(const account_t *data) {
	if (Account_Perst_Update(data) == 1)
		return 1;
	return 0;
}

//删除一个用户账号，通过调用Account_Perst_DeleteByID(usrID)函数实现
inline int Account_Srv_DeleteByID(int usrID) {
	if (Account_Perst_DeleteByID(usrID) == 1)
		return 1;
	return 0;
}

//提取usrID对应的用户账号信息，通过调用Account_Perst_SelectByID(usrID, buf)函数实现
inline int Account_Srv_FetchByID(int usrID, account_t *buf) {
	if(Account_Perst_SelectByID(usrID, buf))
	return 1;
	return 0;

}

//提取usrName对应的用户账号信息，通过调用Account_Perst_SelByName(usrName, buf)函数实现
inline int Account_Srv_FetchByName(char usrName[], account_t *buf) {
	if(Account_Perst_SelByName(usrName, buf))
	return 1;
	return 0;
}

//提取所有用户账号信息，保存到list链表中，通过调用Account_Perst_SelectAll(list)函数实现
inline int Account_Srv_FetchAll(account_list_t list) {
	if(Account_Perst_SelectAll(list))
	return Account_Perst_SelectAll(list);
	else
	return 0;
	return 1;
}


