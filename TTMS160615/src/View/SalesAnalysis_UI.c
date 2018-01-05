/*
 * SalesAnalysis_UI.c
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */
#include "SalesAnalysis_UI.h"
#include "../Common/list.h"
#include "../Common/common.h"
#include "../Service/SalesAnalysis.c"
//#include "../Service/Account.c"


#include <conio.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

//外部变量gl_CurUser 用于存储登录用户信息
extern account_t gl_CurUser;

//定义分页机制中页面大小为5
static const int SALESANALYSIS_PAGE_SIZE = 5;



//创建链表 
//GreateList_Head(list) {
//	int i;//控制创建链表的节点个数 
//	salesanalysis_node_t *new;
//	
//	for(i = 0; i < 100; i++) {
//		new = (salesanalysis_node_t *)malloc(sizeof(salesanalysis_node_t));  //创建新的节点
//		if(!new)
//			break; 
//		List_AddHead(list,new);
//	} 
//	return i;
//}




//分页器
static void ShowSalesanalysisListByPage(salesanalysis_list_t head,int listsize) {
	 
 	Pagination_t paging; // 定义分页器；
	paging.pageSize =  SALESANALYSIS_PAGE_SIZE; //设置分页显示页面大小 
	Salesanalysis_Srv_StaticSale(head);//获取剧目票房信息服务 
	
	paging.totalRecords = Salesanalysis_Srv_StaticSale(head);//设置分页的总记录数
	
   	SalesAnalysis_Srv_SortBySale(head);//调用剧目票房排行服务函数
    salesanalysis_node_t *pos; //头指针
    int i;
   //定位到分页器的第一页
   Paging_Locate_FirstPage(head,paging); 
	char choice;
	printf("\n\n\n");
	printf("\t==================================================\t\n");
	printf("\t|              ***剧目票房排行榜***              |\t\n");
	printf("\t==================================================\t\n");
	
	for (i = 0, pos = (salesanalysis_node_t *) (paging.curPos);
		pos != head && i < paging.pageSize; i++) {
				printf("\tID%5d Name%5s price%5d totaltickets%5ld sales%5ld",
				pos->data.play_id,
				pos->data.name,
				pos->data.price,
				pos->data.totaltickets,
				pos->data.sales);
				pos = pos->next;
			}
	printf("\t------- Total Records:%2d ----------------------- Page %2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
	printf("\t|============================================|\t\n");
		printf("\t|       P.上一页  N.下一页  R.退出       |\t\n");
	printf("\t|============================================|\t\n");
	do{
	printf("你的选择是");
	scanf("%c",&choice);
	fflush(stdin);
	switch(choice) {
		case 'p':
		case 'P':
			if(1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head,paging,-1,salesanalysis_node_t);
			}
			break;
		case 'n':
		case 'N':
			if(Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head,paging,1,salesanalysis_node_t);
			}
			break;
		default:
			break;			
		}
	}while(choice != 'r'&& choice != 'R');
	
 } 

//剧院销售排行榜函数,降序显示截止目前剧院电影票房排行榜
void SalesAnalysis_UI_BoxOffice() {
	
	setvbuf(stdout,NULL,_IONBF,0);
	salesanalysis_list_t head; //定义链表头指针 
	int size = 0;
	
	List_Init(head,salesanalysis_node_t); //初始化链表 
	//size = GreateList_Head(list); //创建链表 
	
	//Salesanalysis_Srv_StaticSale(head);//获取剧目票房信息服务 
	
	//SalesAnalysis_Srv_SortBySale(head);//调用剧目票房排行服务函数
	
	ShowSalesanalysisListByPage(head,size); //通过分页显示链表内容
	
	List_Destroy(head,salesanalysis_node_t);//销毁链表 
}

//显示售票员在给定日期区间的售票情况
void SalesAnalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate){
	int sale;
	account_t usr;
	usr.id = usrID;
	sale = Salesanalysis_Srv_CompSaleVal(usr.id,stDate,endDate);
	Account_Srv_FetchByID(usr.id,&usr);
	printf("从%d.%d.%d到%d.%d.%d期间销售额为:%d",stDate.year,stDate.month,stDate.day,endDate.year,endDate.month,endDate.day,sale);

}

//销售分析入口函数，显示菜单，菜单包含"降序显示截止目前剧院电影票房排行榜"，“显示或查询当日售票员售票情况”，
//“查询给定日期区间某售票员售票情况”
void SalesAanalysis_UI_MgtEntry() {
	char choice;
	account_t user;//结构体 
	user_date_t stDate;
	user_date_t endDate;
	char UsrName[20];//售票员的名字
	account_t gl_CurUser_type;
	
	Pagination_t paging; 
	
	//界面 
	printf("\n\n\n");
	printf("\t\n|===================================================================|\t\n");
	printf("\t\n|               *************销售数据分析**************             |\t\n");
	printf("\t\n|===================================================================|\t\n");
	printf("\t\n| B.剧目票房排行榜  D.售票员销售额界面  S.经理销售额界面  R.退出程序|\t\n");
	printf("\t\n|===================================================================|\t\n"); 
	
	do{
	
		printf("请输入你的选择:");
		fflush(stdin);
		scanf("%c",&choice);
		switch(choice)
		{
			case 'b':
				case 'B':
					
					SalesAnalysis_UI_BoxOffice();
					
					break;
			case 'd':
				case 'D':
					if(gl_CurUser.type == USR_CLERK){
						SalesAnalysis_UI_StatSale(user.id,stDate,endDate);
					}
					else
					{
						printf("输入售票员的名字:");
						fflush(stdin);
						scanf("%s",&UsrName);
						if(!Account_Srv_FetchByName(UsrName,&user)) {
							printf("抱歉，尚未找到该信息");
						}
						else
							SalesAnalysis_UI_StatSale(user.id,stDate,endDate);
					}
					
					break;
			case 's':
				case 'S':
					if(gl_CurUser.type != USR_MANG)
					{
						printf("输入售票员的名字:");
						fflush(stdin);
						scanf("%s",&UsrName);
						if(!Account_Srv_FetchByName(UsrName,&user))
						{
							printf("抱歉，尚未找到该信息");
						}
						else
						{
							printf("请输入剧目上映时间与下映时间:(以空格隔开，如2017 6 14)");
							scanf("%d%d%d",&stDate.year,&stDate.month,&stDate.day);
							scanf("%d%d%d",&endDate.year,&endDate.month,&endDate.day);
							SalesAnalysis_UI_StatSale(user.id,stDate,endDate);
					    }
						}
					else
						printf("对不起，输入信息错误");
					break;
			case 'r':
				case 'R':
					break;
			default:
				break; 
		}
	}while(choice != 'R' && choice != 'r');

}



