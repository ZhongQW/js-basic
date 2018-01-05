int play_print(play_t p) {
	printf("\t==========================================================\t\n");
 	printf("\t|                 ******剧目信息******                   |\t\n");
 	printf("\t==========================================================\n");
	printf("\t|   1.剧目ID:        %20d                |\t\n",p.id);
	printf("\t|   2.剧目名称:      %20s                |\t\n",p.name); 
	printf("\t|   3.剧目类型:      %20d                |\t\n",p.type);
	printf("\t|   4.剧目出品区域:  %20s                |\t\n",p.area);
	printf("\t|   5.剧目等级:      %20d                |\t\n",p.rating);
	printf("\t|   6.剧目时长(分钟):%20d                |\t\n",p.duration);
	printf("\t|   7.放映日期:      %10d%4d%4d                |\t\n",p.start_date.year,p.start_date.month,p.start_date.day);
	printf("\t|   8.结束日期:      %10d%4d%4d                |\t\n",p.end_date.year,p.end_date.month,p.end_date.day);
	printf("\t|   9.票价:          %20d                |\t\n",p.price);
	    	     	
 	printf("\t|========================================================|\t\n");
 }
