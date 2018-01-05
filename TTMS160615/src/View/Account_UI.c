/*
* Account_UI.c
*
*  Created on: 2015年5月8日
*      Author: Administrator
*/

#include "Account_UI.h"
#include "../Common/list.h" 
#include "../Service/Account.c"
#include<windows.h>
#include <stdio.h>
#include<assert.h>
#include<string.h>
#include <unistd.h>
#include <sys/time.h>

void Account_UI_ShowList(account_list_t list, Pagination_t paging);

//登录函数，提示用户输入用户名和密码，登录成功return 1，否则提示重新登录，超过3次，登录失败
int SysLogin() {
	//系统登录
	Account_Srv_InitSys();
	char ch;
	int i = 0, j,m,n=0;
	char usrName[30];
	char pwd[30];
	int londtime = 3;

	do {
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = = =  ╗\n\n\n");
		printf("\t\t\t╬ぷぷぷぷぷぷぷぷぷ  X·剧院票务管理系统  ぷぷぷぷぷぷぷぷぷ ╬\n\n\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = = =  ╝\n\n\n");
		printf("欢迎使用！");
		printf("请输入1.售票员，2.经理，9.管理员\n");
		scanf("%d", &j);
		getchar(); 
		printf("请输入用户名:\n");
		scanf("%s", usrName);
		getchar(); 
		printf("请输入密码:\n");
		scanf("%s",pwd); 
		/*while ((ch = getch()) != '\r')
		{
			if (ch != 8)
			{
				pwd[i] = ch;
				putchar('*');
				i++;
			}
			else
			{
				putchar('\b');//这里是删除一个我们通过输出回撤符 /b回撤一格，
				putchar(' ');//再显示空格符把刚才的*给盖住，
				putchar('\b');//然后再回撤一格等待录入。
				i--;
			}
		}
		pwd[i] = '\0';		*/
		m=(Account_Srv_Verify(usrName, pwd));
		if (m!=1)
		{
			if (n == londtime)
			{
				printf("您已登陆三次，所以无权登陆此系统......\n");
				exit (0);
			}
			else
			{
				n++;
				printf("您输入的密码或者账户错误，您还有%d次登陆机会！\n", londtime - n);
			}
		}
		else
	{	printf("登陆成功");
		getchar(); 
			return  1;} 
	} while (n <= 4);
	return 1;
}
//管理系统用户功能入口函数，显示用户账号管理菜单
void Account_UI_MgtEntry() {
	char usrName[20];
	char i, j;
	int pagesize;
	account_node_t *p = NULL;
	Pagination_t paging;
	account_list_t head;
	p = head;
	account_node_t *pos;
	//CreateList_Head(head);
	List_Init(head, account_node_t);
//	List_Paging(head, paging, account_node_t);
	printf("请输入页数\n");
	scanf("%d", &pagesize);
	if (pagesize <= 0)
		pagesize = 5;
	paging.pageSize = pagesize;
	paging.totalRecords = Account_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	do {
		printf("\n==================================================================\n");
		printf("********************** account  **********************\n");
		printf("%s\t%s\t%s\t%s\n", "ID", "type", "username", "password");
		printf("------------------------------------------------------------------\n");
		//显示数据
		for (i = 0, pos = (account_node_t *)(paging.curPos);
			pos != head && i < paging.pageSize; i++) {
			printf("%d\t%d\t%s\t\t%s\n", pos->data.id,
				pos->data.type, pos->data.username, pos->data.password);
			pos = pos->next;
		}
		printf("------- Total Records:%2d ----------------------- Page %2d/%2d ----\n",
			paging.totalRecords, Pageing_CurPage(paging),
			Pageing_TotalPages(paging));
		printf("用户账号管理菜单\n");
		printf("1:增加用户信息\n");
		printf("2:删除用户信息\n");
		printf("3:修改用户信息\n");
		printf("4:查询用户信息\n");
		printf("\t[R]第一页|[P]上一页|[N]下一页|[L]最后一页\n");
		printf("\n\n");
		fflush(stdin);
		printf("9:终止程序\n");
		scanf("%c", &i);
		system("cls");
		switch (i)
		{
		case '1':
			if (head == NULL)
			{
				printf("无法添加账号");
			}
			else
			{	Account_UI_Add(head);
				paging.totalRecords = Account_Srv_FetchAll(head);
				List_Paging(head, paging, account_node_t);
			break;} 
		case '2':
			if (head == NULL)
			{
				printf("没有可删除的用户");
			}
			else
			{
				printf("请输入要删除用户的用户名");
				scanf("%s", usrName);
				getchar();
				 
				if(Account_UI_Delete(head, usrName)){
				
				paging.totalRecords = Account_Srv_FetchAll(head);
				List_Paging(head, paging, account_node_t);
			}}
			break;
		case '3':if (head == NULL)
		{
			printf("没有可修改的用户");
		}
				 else
				 {
					 printf("请输入要修改用户的用户名");
					 scanf("%s", usrName);
					 getchar();
					 Account_UI_Modify(head, usrName);
					paging.totalRecords = Account_Srv_FetchAll(head);
					List_Paging(head, paging, account_node_t);
				 }
				 break;
		case '4':if (head == NULL)
		{
			printf("没有可查询的用户");
		}
				 else
				 {
					 printf("请输入要查询用户的用户名");
					 scanf("%s", usrName);
					 getchar();
					 Account_UI_Query(head, usrName);
					 paging.totalRecords = Account_Srv_FetchAll(head);
					 List_Paging(head, paging, account_node_t);
				 }
				 break;
		case 'R':
		case 'r':
			Paging_Locate_FirstPage(head, paging);
			break;
		case 'p':
		case 'P':
			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, account_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, account_node_t);
			}
			break;
 		case 'l':
	   	case 'L':
	   		Paging_Locate_LastPage(head,paging,account_node_t);
	   		break;

			 
		case '9':printf("谢谢使用!\n");exit(0);//终止程序
		}
	} while (i != 'r' || i != 'R');
//	Account_UI_ShowList(head, paging);




}


//添加一个用户账号信息，如果账号名存在，提示出错信息
int Account_UI_Add(account_list_t list)
{ 
	int i=0;
	account_node_t *m,p, *q = list;
	char num;
	system("cls");
	do
	{
		printf("请输入要添加用户的账号:");
		scanf("%s", p.data.username);
		getchar();
		if (Account_Srv_FindByUsrName(list, p.data.username) != NULL)
		{
			printf("账号已经存在");
			return 0;
		}
		else {
			printf("请输入要添加用户的密码");
			scanf("%s", p.data.password);
			getchar();
			printf("请输入要添加用户的身份id(1:售票员||2:经理||9:系统管理员)");
			while (scanf("%d", &p.data.type) != 1)
			{
				printf("输入的不是数字,请重新输入!");
				continue;
			}
			p.data.id = EntKey_Srv_CompNewKey("account");
			if (Account_Srv_Add(&(p.data)) == 1)
			{
				m=&p;
				m = (account_node_t*)malloc(sizeof(account_node_t));
				List_AddHead(list,m);
				printf("添加成功"); 
				return 1;} 
		/*		while (q->next)
					q = q->next;
				q->next = p;
				p->prev = q;
				p->next = NULL;
				printf("添加成功");
			}
			printf("是否继续输入?1:继续其他:退出");
			while (scanf("%d", &i) != 1)
			{
				printf("输入的不是数字,请重新输入!");
				continue;
			}*/
		}
	} while (i == 1);
	return 1;
}
/*data
Account_Srv_Add()*/


//根据用户账号名修改用户账号密码，不存在这个用户账号名，提示出错信息
int Account_UI_Modify(account_list_t list, char usrName[]) {
	account_node_t *x, *p = list;
	char q[30], q1[30], q2[30];
	int i=0;
	x = Account_Srv_FindByUsrName(p, usrName); 
	system("cls");
	do
	{
		if (x == NULL) {
			printf("没有找到该用户");
			return 0; 
		}
		else
		{
			printf("用户名为%s\n", x->data.username);
			printf("原密码为%s\n", x->data.password);
			printf("请输入新密码");
			scanf("%s", q1);
			getchar();
			printf("请再次输入新密码");
			scanf("%s", q2);
			getchar();
			if ((strcmp(q1, q2)) == 0)
			{
				strcpy(x->data.password, q1);
				if (Account_Srv_Modify(&(x->data)) == 1)
				{
					x->prev = p->prev;
					x->next = p->next;
					printf("修改成功");
					return 1;
				}
			}
			else {
				printf("两次输入不一致!修改失败,输入1重新修改,输入其他退出");
				scanf("%d", &i);
			}
		}
	} while (i == 1);
	return 1;
}

//根据用户账号名删除一个已经存在的用户账号信息，如果不存在这个用户账号名，提示出错信息
int Account_UI_Delete(account_list_t list, char usrName[]) {
	account_node_t *q, *p = list;
	int usrID;
	char q2[30], q1[30];
	int i;
	char a;
	q = Account_Srv_FindByUsrName(p, usrName); 
	system("cls");
	if (q  == NULL)
	{
		printf("账号不存在");
		return 0;
	}

	printf("要删除的用户名为%s\n确定删除吗?(y/n)", q->data.username);
	scanf("%c", &a);
	getchar();
	usrID=(Account_Srv_FindByUsrName(list,usrName)->data.id);
	if (a == 'y' || a== 'Y') {
		Account_Srv_DeleteByID(q->data.id);
		printf("删除成功!");
		return 1;
	}
	else
		printf("删除失败");
	return 0;
}

//根据用户账号名查找该用户账号是否存在，存在返回1，否则返回0，并提示错误信息
int Account_UI_Query(account_list_t  list, char usrName[]) {
	account_node_t *q, *p = list;
	char q2[30], q1[30];
	int i;
	char a;
	q = Account_Srv_FindByUsrName(p, usrName); 
	system("cls");
	if (q== NULL)
	{
		printf("账号不存在");
		return 0;
	}
	else {
		printf("该用户ID为%ld\n用户类型为%d\n账号名为%s\n密码为%s\n", q->data.id, q->data.type, q->data.username, q->data.password);
		getchar(); 
	}
	return 1;
}

//以头插法创建链表list.返回值为数据节点个数
int CreateList_Head(account_list_t list) {
	int i;
	account_list_t p;

	for (i = 0; i < 100; i++) {
		p = (account_node_t*)malloc(sizeof(account_node_t));
		if (!p)
			break;
		List_AddHead(list, p);
	}
	return i;
}
//销毁链表	
/*void Account_UI_ShowList(account_list_t list, Pagination_t paging) {

	int size = 0;
	ShowListByPage(list, size);
	List_Destroy(list, account_node_t);//销毁链表	
}*/
