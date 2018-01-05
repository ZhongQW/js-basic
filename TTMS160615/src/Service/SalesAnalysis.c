/*
 * salesanalysis.c
 *
 *  Created on: 2015年6月12日
 *      Author: Administrator
 */
#include <string.h>
#include <stdio.h>
#include "SalesAnalysis.h"
#include "../Persistence/Sale_Persist.h" 
#include "../Persistence/SalesAnalysis_Persist.c"
#include "Ticket.h"
#include "Play.h"
#include "Sale.h" 
#include "Schedule.h"
#include "../Common/list.h"

//计算员工usrID在给定时间区间的销售额，返回销售额
inline int Salesanalysis_Srv_CompSaleVal(int usrID, user_date_t stDate, user_date_t endDate){

	int amount = 0;
	sale_list_t saleList; //链表 
	sale_node_t *pSale; //定义指针变量
	List_Init(saleList,sale_node_t);//初始化 
	Sale_Perst_SelectByUsrID(saleList,usrID,stDate,endDate);//载入匹配usrID的销售信息，构建链表 
	List_ForEach(saleList,pSale);//遍历 
	amount += pSale->data.value;
	return amount;//返回某售票员的销售额 
}

//结合剧目Play.dat,统计销售数据，构建销售分析salesanalysis_list_t list链表，返回list链表长度
int Salesanalysis_Srv_StaticSale(salesanalysis_list_t list) {
	play_list_t playList; //定义头指针
	play_node_t *pos; //指针变量
	salesanalysis_node_t *newNode;
	int sold,total; //存储已售票数和总票数
	int count = 0; //记录节点个数 
	
	List_Free(list,salesanalysis_node_t);//释放list中所有数据节点 
	List_Init(playList,play_node_t);//初始化playList链表
	 
	total = Play_Srv_FetchAll(playList);//函数从文件play.dat载入剧目信息构建playlist链表
	
	List_ForEach(playList,pos);//遍历playList链表
	{
		newNode = (salesanalysis_node_t*)malloc(sizeof(salesanalysis_node_t));
		if(!newNode)
		{
			printf("内存分配失败!!\n");
			
		}
		newNode->data.play_id = pos->data.id;
		strcpy(newNode->data.name,pos->data.name);
		strcpy(newNode->data.area,pos->data.area);
		newNode->data.duration = pos->data.duration;
		newNode->data.start_date = pos->data.start_date;
		newNode->data.end_date	= pos->data.end_date;
		newNode->data.price = pos->data.price;
		newNode->data.sales = Schedule_Srv_StatRevByPlay(pos->data.id,&sold,&total);
		newNode->data.totaltickets = sold;
		List_AddTail(list,newNode);
		count++;
	}
		
	List_Destroy(playList,play_node_t);//销毁链表 
	 
	return count;
}

//对剧院电影票房排序
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list){
	salesanalysis_node_t *p;
	salesanalysis_node_t *listLeft;
	if(list = NULL) {
		printf("对不起，无法执行");
	}
	else {
		list->prev->next = NULL;
		listLeft = NULL;
		list->next = list->prev = list;
		{
			if(listLeft == NULL) {
				printf("对不起，无法执行");
			}
			else {
				while(!listLeft) {
					listLeft = (salesanalysis_node_t *)malloc(sizeof(salesanalysis_node_t));
					p = listLeft;
					listLeft = listLeft->next;
					}
				}
		}
	}
}


