#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 30
#define INFINITY 9999 
#define MAX 15 // 车次号 
//城市信息
typedef struct {
	int NO;//城市序号 
	char name[20];//城市名字 
}CityNode;
//路线信息 
typedef struct {
	int money;//单位是元
	char number[MAX];//车次号 
	CityNode startCity;//起始城市
	CityNode endCity;//到达城市
	int StartTime;//起始时间单位是秒
	int EndTime;//到达时间单位是秒
	int CostTime;//消耗时间单位是秒 
}ArcsNode,*ArcsPtr;
//图的信息 
typedef struct {
	ArcsNode Edg[MAXSIZE];
    int arcs[MAXSIZE][MAXSIZE];//边的集合，1表示有路径，0表示没有路径 
	int vexnum;//顶点的个数 
	int arcsnum; //边的个数 
}AdjMatrix; 

void First(AdjMatrix *G);
void Creat(AdjMatrix *G);
void Query(AdjMatrix G);
void First(AdjMatrix *G){
	int logo;
	printf("请选择你要执行的操作：\n对路线进行->1：删除和修改，2：查询\n");
	scanf("%d",&logo);
	switch(logo){
		case 1:Creat(G);break;
		case 2:Query(*G);break;
	    default:printf("请输入正确的提示信息！"); 
	} 
}
void Creat(AdjMatrix *G){
	int i,j;
	CityNode city;
	FILE *fp;//指向城市信息的文件指针 
	FILE *fs;//指向时刻表的文件指针 
	printf("请输入城市个数和路线的个数：\n");
	scanf("%d%d",&G->vexnum,&G->arcsnum);
    fp = fopen("城市信息.txt","w");
    printf("输入城市序号为0000表示结束！\n");
	for(i=0;i<G->vexnum;i++){ 
	   printf("NO.",i+1);
	   scanf("%d",&city.NO);
	   if (city.NO!=0000){
		  scanf("%s",city.name); 
		  fwrite(&city,sizeof(CityNode),1,fp);
       }
       else
        printf("信息更新成功！");
    fclose(fp); 
    }
}
//void Query(AdjMatrix G){
//	int logo,start,end;
//	printf("请输入你要查询的路线起始城市和要到达的城市的序号！\n");
//	//读文件内城市的序号
//	scanf("%d%d",&start,&end);
//	printf("选择一条你的决策,1:最快到达，2：费用最少，3：中转站最少！\n");      	
//	scanf("%d",&logo);
//}
int main() {
	AdjMatrix G;
	First(&G); 
	return 0;
}
