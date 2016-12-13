#include<stdio.h>
#include<time.h>
#include<windows.h>
char fun(char str[])
{
	time_t timep; 
	struct tm *p; 
	time(&timep); 
	p=localtime(&timep); 
	sprintf(str,"%d年%d月%d日%d时%d分%d秒",(1900+p->tm_year), (1+p->tm_mon),p->tm_mday,p->tm_hour, p->tm_min, p->tm_sec);
	return str;
}
int main()
{ 
	char str[60];
	str=fun(str);
	printf("%s",str);
}
	printf("按k键新增图书");
	gotoxy(i,k+2);
	printf("按n键查询图书");
	gotoxy(i,k+4);
	printf("按m键修改图书");
	gotoxy(i,k+6);
	printf("按c键删除图书");
	gotoxy(i,k+8);
	printf("按l键借出图书");
	gotoxy(i,k+10);
	printf("按b键归还图书");
	gotoxy(i,k+12);
	printf("按s键保存信息");
	gotoxy(i,k+14);
	printf("按esc退出管理");  
}

