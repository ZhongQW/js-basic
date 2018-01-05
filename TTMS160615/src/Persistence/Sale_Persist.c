#include "Sale_Persist.h"
#include "../Common/list.h"
#include "../Service/Sale.h"
#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>


static const char SALE_DATA_FILE[] = "Sale.dat";
static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat";

int Sale_Perst_Insert(const sale_t *data) {
	FILE *fp = fopen(SALE_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) 
	{
		printf("Cannot open file %s!\n", SALE_DATA_FILE);
		return 0;
	}
	else 
	   	  if (!feof(fp))
	      {
		     rtn=fwrite(data,sizeof(data),1,fp);
	         fclose(fp);
	      }
       return rtn;
}

int Sale_Perst_DeleteByID(int saleID) {
	if(rename(SALE_DATA_FILE,SALE_DATA_TEMP_FILE)<0){
    	printf("Cannot open file %s!\n",SALE_DATA_FILE);
	} 
	FILE  *fpSour;
	FILE  *fpTarg; 
	int   found=0;
	fpSour=fopen(SALE_DATA_FILE,"rb");
    if (NULL==fpSour){
        printf("Cannot open file %s!\n",SALE_DATA_TEMP_FILE);
        return 0;
    }
    
	fpTarg=fopen(SALE_DATA_FILE,"wb");
	if (NULL==fpTarg){
		printf("Cannot open file %s\n",SALE_DATA_FILE);
		return 0; 
	} 
    ticket_t buf;
	while(!feof(fpSour)){
		if(fread(&buf,sizeof(ticket_t),1,fpSour)){
			if(saleID==buf.id){
				found=1;
				continue;
			}
			fwrite(&buf,sizeof(ticket_t),1,fpTarg);
		}
	}    
	fclose (fpTarg);
	fclose (fpSour);
	remove(SALE_DATA_TEMP_FILE); 
	return found;
}

//根据用户ID载入给定时间区间内的销售记录
int Sale_Perst_SelectByUsrID(sale_list_t list, int usrID, user_date_t stDate,
		user_date_t endDate) {

	sale_node_t *newNode; 
	
	FILE   *fp=fopen(SALE_DATA_FILE,"rb");
	if (NULL==fp)
	{
    printf("Cannot open file %s!\n",SALE_DATA_FILE);
	return 0;	
    }
	int recCount;
	sale_t saleRac;	
    while(!feof(fp)){
    	fread(&saleRac,sizeof(sale_t),1,fp);{
    	 if  ((saleRac.id==usrID)&&(saleRac.date.year==endDate.year&&saleRac.date.month==endDate.month&&saleRac.date.day==endDate.day))
		 {
		   newNode=(sale_t *)malloc(sizeof(sale_t));
		   newNode=&saleRac;
		   List_AddTail(list,newNode);
		   recCount++; 
		}
		}
	}
	fclose (fp);
	return recCount;
}
//根据给定时间区间内的销售记录
int Sale_Perst_SelectByDate(sale_list_t list, user_date_t stDate,
		user_date_t endDate) {
	sale_node_t *newNode; 
	FILE  *fp=fopen(SALE_DATA_FILE,"rb");
	if (NULL==fp)
	{
	   printf("Cannot open file %s！",SALE_DATA_FILE);
	   return 0; 
	}
	int recCount;
	sale_t saleRac;	
    while(!feof(fp)){
    	fread(&saleRac,sizeof(sale_t),1,fp);
		{
    	 if  (saleRac.date.year==endDate.year&&saleRac.date.month==endDate.month&&saleRac.date.day==endDate.day)
		 {
		   newNode=(sale_t *)malloc(sizeof(sale_t));
		   newNode=&saleRac;
		   List_AddTail(list,newNode);
		   recCount++; 
		}
		}
	}
	fclose (fp);
	return recCount;
}
    
/*

//queryUid = null,query all the uid Sale information return the all uid Sale information number
//queryUid =  uid, query the uid Sale information return the uid Sale  number
 *
int  Sale_Infor_By_Uid(char * queryUid, Sale_list_t head)
{

	return 0;
}

int Sale_Infor_By_Time(char  queryTime[][30], Sale_list_t head)
{

	
	return 0;
}

//根据票的id获得票的基本信息 
int Select_Price_By_Playid(int id, ticket_t *buf)
{
	
		return 0;
}
*/

