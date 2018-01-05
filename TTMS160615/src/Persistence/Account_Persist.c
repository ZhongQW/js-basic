/*
* Account_Persist.c
*
*  Created on: 2015年5月8日
*      Author: Administrator
*/

#include "Account_Persist.h"
#include "../Service/account.h"
#include "../common/list.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>
#include <string.h>

static const char ACCOUNT_DATA_FILE[] = "Account.dat";
static const char ACCOUNT_DATA_TEMP_FILE[] = "AccountTmp.dat ";

//判断账号文件是否存在，返回1存在，返回0不存在
int Account_Perst_CheckAccFile() {
	if (access("Account.dat", 0) == 0)
		return 1;
	return (0);
}

//根据用户名载入账号,载入成功 return 1；否则 return 0
int Account_Perst_SelByName(char usrName[], account_t *buf) {
	assert(NULL!=buf);
	FILE *fp;
	account_t data;	
	fp=fopen("Account.dat","r");
	if(fp==NULL)
	{
		fclose(fp);
		return 0;
	}
	while (!feof(fp)) 
	{
		if (fread(&data, sizeof(account_t), 1, fp)) 
		{
			if (strcmp(usrName,data.username)==0)
			{
				*buf = data;
				break;
			}
		}
	}
	fclose(fp);
	return 1;
}

//新账号写入账号文件中，返回实际写入的数据块数目
int Account_Perst_Insert(const account_t *data) {
	FILE *fp;
	account_t x; 
	fp = fopen("account.dat", "ab");
/*	while (!feof(fp)) 
	{
		if (fread(&x, sizeof(account_t), 1, fp)) 
		{
			if(x.username==data->username)
			{
				printf("存在同名用户");
				return 0; 
			}
		}
	}*/
	if (NULL == fp)
	{
		printf("打开文件%s失败!\n", "Account.dat");
		return 0;
	}
	if(fwrite(data, sizeof(account_t), 1, fp))
	{
		printf("写入完成!\n"); 
	fclose(fp);
	return 1;
	}
	return 0; 
}

//在账号文件中查找与参数账号匹配的账号，找到 return 1；否则 return 0；并进行覆盖重写
int Account_Perst_Update(const account_t * data) {
	assert(NULL!=data);
	FILE *fp = fopen("account.dat", "rb+");
	account_t x;
	int found = 0;
	if (NULL == fp) 
	{
		printf("打开文件%s失败!\n","account.dat");
		return 0;
	}
	while (!feof(fp)) 
	{
		if (fread(&x, sizeof(account_t), 1, fp)) 
		{
			if (strcmp(x.username,data->username)==0)
			{
				fseek(fp, -sizeof(account_t), SEEK_CUR);
				fwrite(data, sizeof(account_t), 1, fp);
				found = 1;
				break;
			}
			else
			{
				
			} 
		}
	}
	fclose(fp);
	return found;
}

//在账号文件中删除与参数id匹配的账号，删除成功 return 1；否则 return 0；
 int Account_Perst_DeleteByID(int id) {

	FILE *fpSour, *fpTarg;
	account_t buf;
	
	if (rename(ACCOUNT_DATA_FILE, ACCOUNT_DATA_TEMP_FILE) < 0) 
	{
		printf("打开文件..失败 %s!\n", ACCOUNT_DATA_FILE);
		return 0;
	}

	fpSour = fopen(ACCOUNT_DATA_TEMP_FILE, "rb");
	fpTarg = fopen(ACCOUNT_DATA_FILE, "wb");

	if (NULL == fpTarg) {
		printf("打开文件失败 %s!\n", ACCOUNT_DATA_FILE);
		return 0;
	}
	if (NULL == fpSour) {
		printf("打开文件失败 %s!\n", ACCOUNT_DATA_TEMP_FILE);
		return 0;
	}
	while (!feof(fpSour))
	 {
		if (fread(&buf, sizeof(account_t), 1, fpSour)) 
		{
			if (id == buf.id) 
			{	
			continue;
			}
			fwrite(&buf, sizeof(account_t), 1, fpTarg);
		}
	}
	fclose(fpTarg);
	fclose(fpSour);

	remove(ACCOUNT_DATA_TEMP_FILE);
	return 1;

}


//在账号文件中查找与参数id匹配的账号，并通过指针buf传出；匹配成功 return 1；否则 return 0；
int Account_Perst_SelectByID(int id, account_t *buf) {
	assert(NULL != buf);

	FILE *fp = fopen("account.dat", "rb");
	if (NULL == fp) {
		return 0;
	}
	account_t data;
	int found = 0;
	while (!feof(fp)) {
		if (fread(&data, sizeof(account_t), 1, fp)) {
			if (id == data.id) {
				*buf = data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);
	return found;

	return 1;
}

//遍历读ACCOUNT_DATA_FILE文件，动态构建用户账号list链表,list 为链表头指针，返回list长度
int Account_Perst_SelectAll(account_list_t list) {
	account_node_t *newNode;
	account_t data;
	int recCount = 0;
	assert(NULL!=list);
	
	if (access("account.dat", 0))
	return 0;

	List_Free(list, account_node_t);

	FILE *fp = fopen("account.dat", "rb");
	if (NULL == fp) 
	{
		return 0;
	}
	while (!feof(fp)) 
	{
		if (fread(&data, sizeof(account_t), 1, fp)) 
		{
			newNode = (account_node_t*) malloc(sizeof(account_node_t));
			if (!newNode) 
			{
				printf("Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			newNode->data = data;
			List_AddTail(list, newNode);
			recCount++;
		}
	}
	fclose(fp);
	return recCount;
}

