/*
* File name:  Schedule_UI.c
* File ID:	  TTMS_SSF_Schedule_UI_Sour
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/


#include "Schedule_UI.h"
#include "Play_UI.h"

#include "../Service/Play.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"

#include <stdio.h>
#include <stdlib.h>

	/*
	 * Function:    Schedule_UI_ListAll
	 * Function ID:	TTMS_SCU_Schedule_UI_List
	 * Description: 显示所有的演出计划信息,进行查询。
	 * Input:       无
	 * Output:      所有剧目的信息
	 * Return:      无
	 */
void Schedule_UI_ListAll(void) {
	
}

/*
 * Function:    Schedule_UI_Add
 * Function ID:	TTMS_SCU_Schedule_UI_Add
 * Description: 添加一条演出计划信息
 * Input:       相关剧目的ID号
 * Output:      输入信息时的各种提示
 * Return:      添加的记录数
 */
int Schedule_UI_Add(int play_id) {
	schedule_t rec;
	int newRecCount = 0;//记录新增剧目数 
	char choice;

	printf("\n=================================================\n");
	printf("*****************  添加演出计划   *****************\n");
	printf("---------------------------------------------------\n");

	rec.play_id=play_id ;
	printf("添加演出厅ID"); 
	scanf("%d",&rec.studio_id);
	printf("添加放映日期 ");
	scanf("%d%d%d",&rec.date.year,&rec.date.month,&rec.date.day);
	printf("添加放映时间"); 
	scanf("%d%d%d",&rec.time.hour,&rec.time.minute,&rec.time.second);
	printf("添加座位数");
	scanf("%d",&rec.seat_count);
	
	rec.id = EntKey_Srv_CompNewKey("Schedule");
	
	if(Schedule_Srv_Add(&rec))
	{
		newRecCount += 1;
			printf("添加演出计划成功\n");
	}
	else
		printf("添加演出计划失败\n");
		printf("------------------------------------------------\n");
	
	return newRecCount;
}
/*
 * Function:    Schedule_UI_Modify
 * Function ID:	TTMS_SCU_Schedule_UI_Mod
 * Description: 按照ID号更新演出计划信息
 * Input:       待更新的剧目ID号
 * Output:      输入信息时的各种提示
 * Return:      更新的剧目信息数，0表示未找到，1表示找到并更新
 */
int Schedule_UI_Modify(int id){

	int rtn=0;
	schedule_t rec;
	int choice;
	
	if(Schedule_Srv_FetchByID(id,&rec)==1){ 
		printf("未找到该剧目的演出计划");
		return 0; 
	}
	 
	printf("\n=================================\n");
	printf("***********  修改演出计划  ********\n");
	printf("------------------------------------");
	printf("\n=================================\n");
	printf("\n|*******  1.演出厅ID    ******* |\n");
	printf("\n|*******  2.放映日期    ******* |\n");
	printf("\n|*******  3.放映时间    ******* |\n");
	printf("\n|*******  4.座位数      ******* |\n");
	printf("\n=================================\n");
	printf("\n\n");
	do{
		printf("请输入所修改内容的选项(0退出演出计划修改):");
		scanf("%d",&choice);
		switch(choice){
		
			case 1:
				printf("演出厅ID:");
				scanf("%d",&rec.studio_id);
				break;
			case 2:
				printf("放映日期");
				scanf("%d%d%d",&rec.date.year,&rec.date.month,&rec.date.day);
				break;
			case 3:
				printf("添加放映时间"); 
				scanf("%d%d%d",&rec.time.hour,&rec.time.minute,&rec.time.second);
				break;
			case 4:
				printf("添加座位数");
				scanf("%d",&rec.seat_count);
				break; 
			case 0:break;
			
			default:
				printf("对不起，输入的信息有误\n");
				break;
		}
	}while(choice!=0);
	
	rtn=Schedule_Srv_Modify(&rec);
	if(rtn==1)
		printf("修改演出计划成功\n");
	else
		printf("修改演出计划失败\n");
		
}

/*
 * Function:    Schedule_UI_Delete
 * Function ID:	TTMS_SCU_Schedule_UI_Del
 * Description: 按照ID号删除演出计划信息
 * Input:       待删除的剧目ID号
 * Output:      提示删除是否成功
 * Return:      0表示删除失败，1表示删除成功
 */
int Schedule_UI_Delete(int id){

	int rtn = 0;
	
	//若存在该ID，则删除该部分内容 
	if(Schedule_Srv_DeleteByID(id))
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
 * Function:    Schedule_UI_Query
 * Function ID:	TTMS_SCU_Schedule_UI_Qry
 * Description: 按照ID号查询演出计划信息
 * Input:       待查找的剧目ID号
 * Output:      查找到的剧目信息
 * Return:      0表示未找到，1表示找到了
 */
int Schedule_UI_Query(int id){

	char chioce;
	schedule_t buf;
	int rtn;
	 if (Schedule_Srv_FetchByID( id, &buf)) {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t***********  ID为%2d的演出计划  **********\n",buf.id);
		printf("\t\t\t = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\n\n");
        rtn = 1;
        printf("计划ID: %d\n",&buf.id);
        printf("剧目ID: %d\n",&buf.play_id);
        printf("放映厅ID: %d\n",&buf.studio_id);
        printf("演出日期:%d年%d月%d日\n", &buf.date.year, &buf.date.month, &buf.date.day);
        printf("演出时间:%d时%d分%d秒\n",&buf.time.hour, &buf.time.minute, &buf.time.second);
        printf("座位数量:%d\n",buf.seat_count);
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
        printf("输入回车键结束");
        while(getchar() != '\n');
    }
	else    
    {
        printf("\n\t\t\t查找不到该演出计划！");
		rtn = 0; 
    }
    return rtn;
	
}

/*
 * Function:    Schedule_UI_ListByPlay
 * Function ID:	TTMS_SCU_Schedule_UI_ListByPlay
 * Description: 以列表模式显示给定剧目的演出计划信息
 * Input:       list为查找到的演出计划信息链表的头指针，play为剧目信息，paging为显示分页设置参数
 * Output:      无
 * Return:      返回查找到的记录数目
 */
void Schedule_UI_ListByPlay(const play_t *play, schedule_list_t list, Pagination_t paging){
}

/*
 * Function:    Schedule_UI_MgtEntry
 * Function ID:	TTMS_SCU_Schedule_UI_MgtEnt
 * Description: 演出计划管理界面，演出计划按照剧目进行管理，以剧目ID号为输入
 * Input:       相关剧目ID号
 * Output:      演出计划信息
 * Return:      无
 */
void Schedule_UI_MgtEntry(int play_id){

	int id;//演出计划ID 
	int i;
	char choice;
	char ch;
	schedule_list_t list;          
	schedule_node_t *p;  
	int flag;       
	Pagination_t paging; 
	        
	List_Init(list, schedule_node_t);        
//	paging.offset = 0;       
	paging.pageSize = 5;
	//载入数据
	paging.totalRecords = Schedule_Srv_FetchAll(list);
	Paging_Locate_FirstPage(list, paging);
	do{
    	system("cls");
		printf("\t|====================================================================================================|\n");
 		printf("\t|                                    ******演出计划信息******                                        |\t\n");
 		printf("\t|====================================================================================================|\n");
		printf("\t  %s\t%s\t%s\t%s\t%s\t%s\t\n","演出计划ID","上映剧目ID","演出厅ID","放映日期","放映时间","座位数");
 		printf("\t|====================================================================================================|\t\n");
 		
	  	for (i = 0, p = (schedule_node_t *) (paging.curPos);
			p != list && i < paging.pageSize; i++) {
			printf("\t|%d\t%d\t%d\t%4d/%2d/%2d\t%4d/%2d/%2d\t%4d/%2d/%2d\t%d\t|\n",
			(p->data.id),
			(p->data.play_id),
			(p->data.studio_id),
			(p->data.date.year),(p->data.date.month),(p->data.date.day),
			(p->data.time.hour),(p->data.time.minute),(p->data.time.second));
			p = p->next;
		}
	    printf("\n\t------------------Total Records:%2d ------------------------------------- Page %2d/%2d -------------------\n",
               paging.totalRecords, Pageing_CurPage(paging),
               Pageing_TotalPages(paging));
	    printf("\t|========================================================|\t\n");
	    
		printf("\t[F]第一页|[P]上一页|[N]下一页|[L]最后一页|[E]退出\n");
	 
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
	
	printf("\t===========================================================\n");
	printf("\t******************     演出计划管理    ********************\n");
//	printf("\t ID     Name     room     time    excess  ticket   quantity\n");
	printf("\t-----------------------------------------------------------\n");
	printf("\t***********************************************************\n");
	printf("\t[A]dd | [D]elete | [U]pdate | [Q]uery | [R]eturn\n");
	printf("\t===========================================================\n");
	do{
		printf("请输入你的选择(r/R退出演出计划管理):");
		fflush(stdin);
		scanf("%c",&ch);
		switch(ch)
		{
			case'a':
			case'A':
					Schedule_UI_Add(play_id);break;
			case'd':
			case'D':
				printf("请输入需要删除的演出计划id");
				scanf("%d",&id);
				Schedule_UI_Delete(id);break;
			case'u':
			case'U':
				printf("请输入需要修改的演出计划id");
				scanf("%d",&id);
				Schedule_UI_Modify(id);break;
			case 'q':
			case 'Q':
				printf("请输入要查询的演出计划ID");
				scanf("%d",&id); 
				Schedule_UI_Query(id);break;
			case 'r':
			case 'R':
				break; 
			default:
				printf("对不起，你输入的信息有误\n");
		}
	}while(ch!='r'&&ch!='R');
}

