#include <stdio.h>

#include "Main_Menu.h"
#include "../Service/ticket.c"
#include "../Service/EntityKey.c"

#include "..\Common\common.c"
#include "../Common/play_print.c" 

#include "Studio_UI.c" 

#include "Play_UI.c"
#include "../Persistence/Play_Persist.c"
#include "Schedule_UI.c"
#include "../Service/Schedule.c"


#include "Queries_Menu.c"
#include "Account_UI.c"

#include "Sale_UI.c"
#include "SalesAnalysis_UI.c"

void Main_Menu(void) {
	char choice;
	do {
		system("cls");
		printf("\n==================================================================\n");
		printf("******************** 剧院票务管理系统 ********************\n");
		printf("[S]演出厅管理\n");
		printf("[P]剧目管理\n");
		printf("[T]售票管理\n");
		printf("[R]退票\n");
		printf("[Q]查询\n");
		printf("[n]数据分析\n");
		printf("[A]管理系统用户\n");
		printf("[E]退出系统.\n");
		printf("\n==================================================================\n");
		printf("Please input your choice:");
		fflush(stdin);
		choice = getchar();
		switch (choice) {
		case 'S':
		case 's':
			Studio_UI_MgtEntry();
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry(0);
			break;
		case 'Q':
		case 'q':
			Queries_Menu();
			break;
		case 'T':
		case 't':
			Sale_UI_MgtEntry();
			break;
		case 'R':
		case 'r':
	//		Sale_UI_ReturnTicket();
			break;
		case 'N':
		case 'n':
			SalesAanalysis_UI_MgtEntry();
			break;
		case 'A':
		case 'a':
			Account_UI_MgtEntry();
			break;
		case 'E':
		case 'e':
			printf("谢谢使用!"); 
		}
	} while ('E' != choice && 'e' != choice);
}

