/*
* File name:  Schedule_Persist.c
* File ID:	  TTMS_SSF_Schedule_Perst_Sour
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/


#include "Schedule_Persist.h"
#include "../Service/schedule.h"
#include "../Common/list.h"
#include "../Service/ticket.h"
#include "../View/Ticket_UI.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>


/*
 * Function:    Schedule_Perst_Insert
 * Function ID:	TTMS_SCU_Schedule_Perst_Insert
 * Description: 在演出计划信息文件末尾写入一条演出计划信息
 * Input:       待加入文件的演出计划信息数据
 * Output:      打开文件失败的信息
 * Return:      写入文件的记录数
 */
int Schedule_Perst_Insert(const schedule_t *data)
{
	FILE *fp;
	int rtn=0;
	fp=fopen("Schedule.dat","ab");
	if(fp==NULL)
	{
		printf("\n打开文件失败\n");
		return 0;
	}
	rtn=fwrite(data,sizeof(schedule_t),1,fp);
	fclose(fp);
	return rtn;
}

/*
 * Function:    Schedule_Perst_Update
 * Function ID:	TTMS_SCU_Schedule_Perst_Mod
 * Description: 按照演出计划ID号更新文件中的演出计划信息
 * Input:       待在文件中更新的演出计划信息数据
 * Output:      打开文件失败的信息
 * Return:      更新的演出计划信息数，0表示未找到，1表示找到并更新
 */

int Schedule_Perst_Update(const schedule_t *data) {
	
	assert(data != NULL);
	int found = 0;
	schedule_t buf;
	
	FILE *fp = fopen("Schedule.dat","rb+");
	if(fp == NULL) {
		printf("对不起，打开文件失败\n");
		return 0;
	}
	else {
		while(!(fp))                //判断是否读到文件末尾 
		{
			if(fread(&data,sizeof(schedule_t),1,fp)) {
				if(buf.id == data->id) {
					fseek(fp, -sizeof(schedule_t), SEEK_CUR);
				    fwrite(data, sizeof(schedule_t), 1, fp);
				    found = 1;
				    break;
				}
			}
		}
	}	
   return found;
}
/*
 * Function:    Schedule_Perst_DeleteByID
 * Function ID:	TTMS_SCU_Schedule_Perst_DelByID
 * Description: 按照演出计划ID号删除演出计划的信息
 * Input:       待删除的演出计划ID号
 * Output:      打开文件失败的信息
 * Return:      0表示删除失败，1表示删除成功
 */

int Schedule_Perst_DeleteByID(int ID) {
	int found = 0;
	//将原始文件重命名，然后读取数据重新写入到数据文件中，并将要删除的实体过滤掉。
	schedule_t buf;
	FILE *fpSour, *fpTarg;//原文件，临时文件 
	//对原始数据文件重命名
	if(rename("Schedule.dat", "ScheduleTmp.dat")<0){
		printf("对不起，不能打开 %s!\n", "Schedule.dat");
		return 0;
	}
	
	else
	{
		fpSour = fopen("ScheduleTmp.dat", "rb");
		if (NULL == fpSour ){
			printf("对不起，不能打开 %s!\n", "Schedule.dat");
			return 0;
		}
		fpTarg = fopen("Schedule.dat", "wb");
		if ( NULL == fpTarg ) {
			printf("对不起，不能打开 %s!\n", "ScheduleTmp.dat");
			return 0;
		}
		while (!feof(fpSour)) {
			if (fread(&buf, sizeof(schedule_t), 1, fpSour)) {
				if (ID == buf.id) {
					found = 1;
					continue;
				}
				fwrite(&buf, sizeof(schedule_t), 1, fpTarg);
			}
		}
		fclose(fpTarg);
		fclose(fpSour);
	}
   	//删除临时文件
	remove("ScheduleTmp.dat");
	return found;
}
/*
 * Function:    Schedule_Perst_SelectByID
 * Function ID:	TTMS_SCU_Schedule_Perst_SelByID
 * Description: 按照演出计划ID号删除演出计划的信息
 * Input:       待查找的演出计划ID号，保存查找结果的内存的地址
 * Output:      无
 * Return:      0表示未找到，1表示找到了
 */
int Schedule_Perst_SelectByID(int ID, schedule_t *buf){
	assert(NULL!=buf);

	FILE *fp = fopen("Schedule.dat", "rb");
	if (NULL == fp) {
		return 0;
	}
	schedule_t data;
	int found = 0;
	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			if (ID == data.id) {
				*buf = data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);
	return found;
}

/*
 * Function:    Schedule_Perst_SelectAll
 * Function ID:	TTMS_SCU_Schedule_Perst_SelAll
 * Description: 将所有演出计划信息建立成一条链表
 * Input:       list为演出计划信息链表的头指针
 * Output:      提示建立链表时，申请空间失败
 * Return:      返回查找到的记录数目
 */
int Schedule_Perst_SelectAll(schedule_list_t list){
	schedule_node_t *newNode;
	schedule_t data;
	int recCount = 0;

	List_Free(list, schedule_node_t);

	FILE *fp = fopen("Schedule.dat", "rb");
	if (NULL == fp) { //文件不存在
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			newNode = (schedule_node_t*) malloc(sizeof(schedule_node_t));
			if (!newNode) {
				printf(
						"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
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

/*
 * Function:    Schedule_Perst_SelectByPlay
 * Function ID:	TTMS_SCU_Schedule_Perst_SelByPlay
 * Description: 将同意剧目的演出计划信息搜索出来，建立一条链表
 * Input:       list为满足条件的演出计划信息链表的头指针，剧目的ID号
 * Output:      提示建立链表时，申请空间失败
 * Return:      返回查找到的记录数目
 */
int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id){
	FILE *fp;
	schedule_t data;
	schedule_list_t newNode;
	int recCount=0;
	fp=fopen("Schedule.dat","rb");
	
	List_Free(list,schedule_node_t);
	
	while(!feof(fp)){
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			newNode = (schedule_node_t*) malloc(sizeof(schedule_node_t));
			if (!newNode) {
				printf(
						"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
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
