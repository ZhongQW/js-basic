/*
 * Studio_UI.c
 *
 *  Created on: 2015年4月24日
 *      Author: Administrator
 */
#include "Studio_UI.h"

#include "../Common/list.h"
#include "../Service/studio.c"
#include "../Service/seat.h"
#include "../Service/EntityKey.h"
#include "Seat_UI.c"

static const int STUDIO_PAGE_SIZE = 5;

#include <stdio.h>

void Studio_UI_MgtEntry(void) {
	int i, id;
	char choice;

	studio_list_t head;
	studio_node_t *pos;
	Pagination_t paging;

	List_Init(head, studio_node_t);
	paging.offset = 0;
	paging.pageSize = STUDIO_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Studio_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

	do {
		system("cls");
		printf("\n==================================================================\n");
		printf("********************** Projection Room List **********************\n");
		printf("%5s  %18s  %10s  %10s  %10s\n", "ID", "Name", "Rows Count",
				"Columns Count", "Seats Count");
		printf("------------------------------------------------------------------\n");
		//显示数据
		for (i = 0, pos = (studio_node_t *) (paging.curPos);
				pos != head && i < paging.pageSize; i++) {
			printf("%5d  %18s  %10d  %10d  %10d\n", pos->data.id,
					pos->data.name, pos->data.rowsCount, pos->data.colsCount,
					pos->data.seatsCount);
			pos = pos->next;
		}
		printf("------- Total Records:%2d ----------------------- Page %2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf(
				"******************************************************************\n");
		printf(
				"[P]revPage|[N]extPage | [A]dd|[D]elete|[U]pdate | [S]eat | [R]eturn");
		printf(
				"\n==================================================================\n");
		printf("Your Choice:");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);

		switch (choice) {
		case 'a':
		case 'A':
			if (Studio_UI_Add()) //新添加成功，跳到最后一页显示
			{
				paging.totalRecords = Studio_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, studio_node_t);  //输出 
			}
			break;
		case 'd':
		case 'D':
			printf("Input the ID:");
			scanf("%d", &id);
			if (Studio_UI_Delete(id)) {	//从新载入数据
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			break;
		case 'u':
		case 'U':
			printf("Input the ID:");
			scanf("%d", &id);
			if (Studio_UI_Modify(id)) {	//从新载入数据
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			break;
		case 's':
		case 'S':
			printf("Input the ID:");
			scanf("%d", &id);
			Seat_UI_MgtEntry(id);
			paging.totalRecords = Studio_Srv_FetchAll(head);
			List_Paging(head, paging, studio_node_t);
			break;
		case 'p':
		case 'P':
			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, studio_node_t);
}

int Studio_UI_Add(void) {
	studio_t rec;
	int newRecCount = 0;
	char choice;

	do {
		/*system("cls");*/
		printf("\n=======================================================\n");
		printf("****************  Add New Projection Room  ****************\n");
		printf("-------------------------------------------------------\n");
		printf("Room Name:");
		fflush(stdin);
		gets(rec.name);
		printf("Row Count of Seats:");
		scanf("%d", &(rec.rowsCount));
		printf("Column Count of Seats:");
		scanf("%d", &(rec.colsCount));
		rec.seatsCount = 0;
		printf("=======================================================\n");

		//获取主键
		rec.id = EntKey_Srv_CompNewKey("Studio");

		if (Studio_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("The new room added successfully!\n");
		} else
			printf("The new room added failed!\n");
		printf("-------------------------------------------------------\n");
		printf("[A]dd more, [R]eturn:");
		fflush(stdin);
		scanf("%c", &choice);
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

int Studio_UI_Modify(int id) {
	studio_t rec;
	int rtn = 0;
	int newrow, newcolumn;
	seat_list_t list;
	int seatcount;

	/*Load record*/
	if (!Studio_Srv_FetchByID(id, &rec)) {
		printf("The room does not exist!\nPress [Enter] key to return!\n");
		getchar();
		return 0;
	}

	printf("\n=======================================================\n");
	printf("****************  Update Projection Room  ****************\n");
	printf("-------------------------------------------------------\n");
	printf("Room ID:%d\n", rec.id);
	printf("Room Name[%s]:", rec.name);
	fflush(stdin);
	gets(rec.name);

	List_Init(list, seat_node_t);
	seatcount = Seat_Srv_FetchByRoomID(list, rec.id);
	if(seatcount){
		do{			//如果座位文件中已有座位信息，则更新的行列必须比以前大，否则不允许更改
			printf("Row Count of Seats should >= [%d]:", rec.rowsCount);
			scanf("%d", &(newrow));
			printf("Column Count of Seats should >= [%d]:", rec.colsCount);
			scanf("%d", &(newcolumn));
		}while(	newrow<rec.rowsCount||newcolumn<rec.colsCount);
		rec.rowsCount=newrow;
		rec.colsCount=newcolumn;
		rec.seatsCount=seatcount;
	}
	else{
		printf("Row Count of Seats:");
		scanf("%d", &rec.rowsCount);
		printf("Column Count of Seats:");
		scanf("%d", &rec.colsCount);
		rec.seatsCount=0;
	}

	printf("-------------------------------------------------------\n");

	if (Studio_Srv_Modify(&rec)) {
		rtn = 1;
		printf(
				"The room data updated successfully!\nPress [Enter] key to return!\n");
	} else
		printf("The room data updated failed!\nPress [Enter] key to return!\n");

	getchar();
	return rtn;
}

int Studio_UI_Delete(int id) {

	int rtn = 0;

	if (Studio_Srv_DeleteByID(id)) {
		//在删除放映厅时，同时根据放映厅id删除座位文件中的座位
		if(Seat_Srv_DeleteAllByRoomID(id))
			printf("The seats of the room deleted successfully!\n");
		printf(
				"The room deleted successfully!\nPress [Enter] key to return!\n");
		rtn = 1;
	} else {
		printf("The room does not exist!\nPress [Enter] key to return!\n");
	}

	getchar();
	return rtn;
}
void Studio_UI_query(void){
	char choice; 
	int u;
	studio_t *buf; 
	char filter[20],name[20];
	
	
    schedule_list_t     list;
	Pagination_t paging;
    List_Init(list,schedule_node_t);
    
    paging.totalRecords = Schedule_Srv_FetchAll(list);
    paging.pageSize = 5;
    Paging_Locate_FirstPage(list,paging);  
    
	printf("\n\n\n");
	printf("\t=================================\t\n");
	printf("\t|        ***演出厅查询界面***     |\t\n");
	printf("\t|             1.ID查询            |\t\n");
	printf("\t|     	   2.名称查询           |\t\n");
	printf("\t|        	   3.模糊查询           |\t\n");
	printf("\t=================================\t\n");
	printf("请输入功能序号:");
	fflush(stdin);
	scanf("%c",&choice);
	
	switch(choice){ 
		case '1':
			printf("请输入要查询的演出厅ID:");
			scanf("%d",&u);
			if(Studio_Perst_SelectByID(u,buf==1)){
				printf("ID: %d\t名称: %s\t座位行数: %d\t座位列数: %d\t总数: %d",
				buf->id,
				buf->name,
				buf->rowsCount,
				buf->colsCount,
				buf->seatsCount);
			}
			else printf("未找到该演出厅"); 
			break;
		case '2':
			printf("请输入要查询的名称:");
			scanf("%s",name);
			if(Studio_Srv_FetchByName(list,name)){
				paging.totalRecords = Studio_Srv_FetchAll(list);
				List_Paging(list, paging, studio_node_t);
				} 
			break;
		case '3':
			printf("请输入要查询的关键字:");
			scanf("%s",filter); 
			Studio_Srv_FilterByName(list,filter);
		default:
			printf("输入有误\n");
			break;	
	}
}
