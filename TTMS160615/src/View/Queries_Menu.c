#include <stdio.h>
#include <stdlib.h>

#include "Queries_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"

void Queries_Menu(void){
	char choice;
	do {
		printf("\n==================================================================\n");
		printf("************************Information Queries*************************\n");
		printf("[S]演出厅查询\n");
		printf("[P]剧目查询\n");
		printf("[T]票务查询(未完成)\n");
		printf("[C]演出计划查询\n");
		printf("[R]退出.\n");
		printf("\n==================================================================\n");
		printf("Please input your choice:");
		fflush(stdin);
		choice = getchar();
		switch (choice) {
		case 'S':
		case 's':
	//		Studio_UI_query();
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry(1);
			break;
		case 'T':
		case 't': 
		//Ticket_UI_query;
			break;
		case 'C':
		case 'c':
		//	Schedule_UI_ListAll();
			break;
		}
	} while ('R' != choice && 'r' != choice);
	}
