/*
* File name:  Play_UI.c
* File ID:	  TTMS_SSF_Play_UI_Sour
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/


#include "Play_UI.h"

#include "../Common/list.h"
#include "../Service/play.c"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/*
 * Function:    Play_UI_MgtEntry
 * Function ID:	TTMS_SCU_Play_UI_MgtEnt
 * Description: 剧目信息管理界面
 * Input:       flag为0，进入管理页面，flag为1进入查询界面
 * Output:      剧目管理界面
 * Return:      无
*/

void Play_UI_MgtEntry(int flag) {
	system("cls"); 

    //函数实现部分
    play_list_t     list;
    play_node_t     *p;
    int             i,u,pageSize=5;
    Pagination_t    paging;
	char filter[20],name[20];
    char choice;
    play_t *buf;
    
    List_Init(list,play_node_t);
    
    paging.totalRecords = Play_Srv_FetchAll(list);
    paging.pageSize = pageSize;
    Paging_Locate_FirstPage(list,paging);           //定位到第一页
    
    do {
    	system("cls");
		printf("\t=====================================================================================================\t\n");
 		printf("\t|                                      ******剧目信息******                                         |\t\n");
 		printf("\t=====================================================================================================\n");
		printf("\t|%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s|\n", "ID", "Name", "剧目类型",
			"出品区域", "等级","时长","放映日期","结束日期","票价");
 		printf("\t|===================================================================================================|\t\n");
	  	for (i = 0, p = (play_node_t *) (paging.curPos);
			p != list && i < paging.pageSize; i++) {
			printf("\t%d\t%s\t%s\t\t%s\t\t%s\t%d\t%d/%d/%d\t%d/%d/%d\t\t%d\t\n", 
				p->data.id,
				p->data.name,
				(p->data.type == 1)?"Film":(p->data.type == 2?"Opear":"Concert"),
            	p->data.area,
			   (p->data.rating == 1)?"Child":(p->data.rating == 2?"Teenage":"Adult"),
                p->data.duration,
				p->data.start_date.year,p->data.start_date.month,p->data.start_date.day,
				p->data.end_date.year, p->data.end_date.month,p->data.end_date.day,
				p->data.price);
			p = p->next;
		}
	    printf("\n\t------------------Total Records:%2d ------------------------------------- Page %2d/%2d -------------------\n",
               paging.totalRecords, Pageing_CurPage(paging),
               Pageing_TotalPages(paging));
	    printf("\t|========================================================|\t\n");
	
	printf("\t[F]第一页|[P]上一页|[N]下一页|[L]最后一页|[E]退出\n");
 	printf("\n\n");
 	
    printf("Your Choice:");
 	fflush(stdin);
    scanf("%c",&choice);
    
 	switch(choice){
 		case 'f':
 		case 'F':
 			Paging_Locate_FirstPage(list,paging);
 			break;
 		case 'p':
 		case 'P':
 			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(list, paging, -1, play_node_t);
			}
			break;
		case 'n':
		case 'N':
		if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(list, paging, 1, play_node_t);
			}
			break;
	    case 'l':
	    case 'L':
	   		Paging_Locate_LastPage(list,paging,play_node_t);
	   		break;
	   	case 'E':
	   	case 'e':break;
	    default:
	    	printf("输入有误\n");
	    }
	}while(choice!='E'&&choice!='e');
	switch(flag){
		case 0:
			printf("\n\n\n");
			printf("\t=================================\t\n");
			printf("\t|      ***剧目管理界面***       |\t\n");
			printf("\t=================================\t\n");
			printf("\t|     A.添加剧目                |\t\n");
			printf("\t|     U.修改剧目                |\t\n"); 
			printf("\t|     D.删除剧目                |\t\n");
			printf("\t|     M.演出计划管理            |\t\n");
			printf("\t=================================\t\n");
			printf("请输入你的选择(r/R表示结束):");
			fflush(stdin);
			scanf("%c",&choice);
			while(choice != 'r' && choice != 'R'){
				switch(choice) {
					case 'a':
					case 'A':
						if (Play_UI_Add()) //新添加成功，跳到最后一页显示
							{
							paging.totalRecords = Play_Srv_FetchAll(list);
							Paging_Locate_LastPage(list, paging, play_node_t);  //输出 
							}
							break;
					case 'u':
					case 'U':
						printf("请输入要修改的剧目编号:");
						scanf("%d",&u);
						Play_UI_Modify(u);
						if (Play_UI_Modify(u)) {	//从新载入数据
							paging.totalRecords = Play_Srv_FetchAll(list);
							List_Paging(list, paging, play_node_t);
						}
						break;
					case 'm':
					case 'M':
						printf("请输入要管理演出计划的对应剧目ID:"); 
						scanf("%d",&u); 
						Schedule_UI_MgtEntry(u); 
			       		break;
				    case 'd':
				   	case 'D':
				   		printf("请输入要删除的剧目id:");
						scanf("%d",&u);
						if(Play_UI_Delete(u)){
							paging.totalRecords = Play_Srv_FetchAll(list);
							List_Paging(list, paging, play_node_t);
						}
						break;     		
					default:		
						printf("对不起，您输入的信息有误，请重新输入\n");			
					}
					printf("请输入你的选择(r/R表示结束):");
					fflush(stdin);
			    	scanf("%c",&choice);
				}
				break;
		case 1:
				printf("\n\n\n");
				printf("\t=================================\t\n");
				printf("\t|      ***剧目查询界面***       |\t\n");
				printf("\t|             1.ID查询          |\t\n");
				printf("\t|             2.名称查询        |\t\n");
				printf("\t|             3.模糊查询        |\t\n");
				printf("\t=================================\t\n");
				printf("请输入功能序号:");
				fflush(stdin);
				scanf("%c",&choice);
				switch(choice){ 
					case '1':
						printf("请输入要查询的剧目ID:");
						scanf("%d",&u);
						if(Play_UI_Query(u,buf)){
							play_print(*buf); 
						}
						break;
					case '2':
						printf("请输入要查询的名称:");
						scanf("%s",name);
						if(Play_Srv_FetchByName(list,name)){
							paging.totalRecords = Play_Srv_FetchAll(list);
							List_Paging(list, paging, play_node_t);
						} 
						break;
					case '3':
						printf("请输入要查询的关键字:");
						scanf("%s",filter); 
						Play_Srv_FilterByName(list,filter);
					default:
						printf("输入有误\n");
						break;	
				}
		default:
			printf("输入有误\n");
			break;		
	}
}
 /* Function:    Play_UI_Add
 * Function ID:	TTMS_SCU_Play_UI_Add
 * Description: 添加一条剧目信息
 * Input:       无
 * Output:      输入信息时的各种提示
 * Return:      添加的记录数
 */
 
int Play_UI_Add(void)
{
	play_t rec;
	int newRecCount = 0;//记录新增剧目数 
	char choice;

	do {
		/*system("cls");*/
		printf("\n=======================================================\n");
		printf("****************  Add New Play  ****************\n");
		printf("-------------------------------------------------------\n");
		printf("Play Name:");
		fflush(stdin);
		gets(rec.name);
		printf("剧目类型:(1表示电影，2表示歌剧，3表示音乐会)");
		scanf("%d", &(rec.type));
		printf("出品地区:");
		fflush(stdin);
		scanf("%s", &(rec.area));
		printf("剧目级别(1表示儿童可观看，2表示青少年可观看，3表示成人可观看):");
		scanf("%d",&(rec.rating));
		printf("演出时长:");
		scanf("%d",&(rec.duration));
		printf("上映日期(年月日,空格隔开):");
		scanf("%d%d%d",&(rec.start_date.year),&(rec.start_date.month),&(rec.start_date.day));
		printf("结束日期(年月日,空格隔开):");
		scanf("%d%d%d",&(rec.end_date.year),&(rec.end_date.month),&(rec.end_date.day));
		printf("票的价格:");
		scanf("%d",&(rec.price));
		printf("=======================================================\n");

		//获取主键
		rec.id = EntKey_Srv_CompNewKey("Play");

		if (Play_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("The new room added successfully!\n");
	 	}
		else
			printf("The new room added failed!\n");
			printf("-------------------------------------------------------\n");
			printf("[A]dd more, [R]eturn:");
			fflush(stdin);
			scanf("%c", &choice);
	} while ('a' == choice && 'A' == choice);
	return newRecCount;
}
/*
 * Function:    Play_UI_Modify
 * Function ID:	TTMS_SCU_Play_UI_Mod
 * Description: 更新剧目信息
 * Input:       待更新的剧目ID号
 * Output:      输入信息时的各种提示
 * Return:      更新的剧目信息数，0表示未找到，1表示找到并更新
 */

int Play_UI_Modify(int id){
	play_t rec; 
	int rtn = 0;
	int choice;
	if(!Play_Srv_FetchByID(id,&rec)) {
		printf("不存在该剧目ID\n请按回车键[enter]继续\n");
		getchar();
		return 0;
	}
	printf("\t==============================================\t\n");
    printf("\t|**************  修改剧目信息  **************|\t\n");
	printf("\t----------------------------------------------\t\n");
	printf("\t|   1.剧目名称                               |\t\n"); 
	printf("\t|   2.剧目类型                               |\t\n");
	printf("\t|   3.剧目出品区域                           |\t\n");
	printf("\t|   4.剧目等级                               |\t\n");
	printf("\t|   5.剧目时长(分钟)                         |\t\n");
	printf("\t|   6.放映日期                               |\t\n");
	printf("\t|   7.结束日期                               |\t\n");
	printf("\t|   8.票价                                   |\t\n");
	printf("\t----------------------------------------------\t\n");
	printf("\n\n");
	
	printf("请输入所修改内容的选项(0表示结束):");
	scanf("%d",&choice);	
	while(choice != 0) {
	   switch(choice)
	  {
		case 1:
			printf("请输入新的剧目名称:");
			scanf("%s",rec.name);
			break;
		case 2:
			printf("请输入新的剧目类型(1表示儿童可观看，2表示青少年可观看，3表示成人可观看):");
			scanf("%d",&rec.type);
			break;
		case 3:
			printf("请输入新的剧目区域:");
			scanf("%s",rec.area);
			break;
		case 4:
			printf("请输入剧目等级(1表示电影，2表示歌剧，3表示音乐会):");
			scanf("%d",&rec.rating);
		case 5:
			printf("请输入新剧目时长(分钟):");
			scanf("%d",&rec.duration);
			break;
		case 6:
			printf("请输入新剧目放映日期(空格隔开，如2017 6 13):");
			scanf("%d%d%d",&rec.start_date.year,&rec.start_date.month,&rec.start_date.day);
			break;
		case 7:
			 printf("请输入新剧目结束日期(空格隔开，如2017 6 13):");
			 scanf("%d%d%d",&rec.end_date.year,&rec.end_date.month,&rec.end_date.day);
			 break;
		case 8:
			printf("请输入新剧目票价:");
			scanf("%d",&rec.price);
			break;
		default:
			printf("对不起，您输入的信息有误");
			break;
	    	}
	    	printf("请输入所修改内容的选项(0表示结束):");
			scanf("%d",&choice);
	}
	
	if(Play_Srv_Modify) {
		printf("修改成功");
		rtn = 1;
	}
	else
		printf("对不起，修改信息失败");
		
	return rtn;
}

/*
 * Function:    Play_UI_Delete
 * Function ID:	TTMS_SCU_Play_UI_Del
 * Description: 按照ID号删除剧目信息
 * Input:       待删除的剧目ID号
 * Output:      提示删除是否成功
 * Return:      0表示删除失败，1表示删除成功
 */
int Play_UI_Delete(int id){
	
	int rtn = 0;
	
	//若存在该ID，则删除该部分内容 
	if(Play_Srv_DeleteByID(id))
	{
		printf("删除成功\n输入回车键[enter]继续\n");
		rtn = 1;
	}
	else
	    printf("删除失败\n输入回车键[enter]继续\n");
	getchar();
	return rtn;
}
/*
 * Function:    Play_UI_Query
 * Function ID:	TTMS_SCU_Play_UI_Qry
 * Description: 按照ID号查询剧目信息
 * Input:       待查找的剧目ID号
 * Output:      查找到的剧目信息
 * Return:      0表示未找到，1表示找到了
 */
int Play_UI_Query(int id , play_t *rec){
	return Play_Perst_SelectByID(id,rec);
}
