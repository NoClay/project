#include<stdio.h>
#include<time.h>
#include<windows.h>
char fun(char str[])
{
	time_t timep; 
	struct tm *p; 
	time(&timep); 
	p=localtime(&timep); 
	sprintf(str,"%d��%d��%d��%dʱ%d��%d��",(1900+p->tm_year), (1+p->tm_mon),p->tm_mday,p->tm_hour, p->tm_min, p->tm_sec);
	return str;
}
int main()
{ 
	char str[60];
	str=fun(str);
	printf("%s",str);
}
	printf("��k������ͼ��");
	gotoxy(i,k+2);
	printf("��n����ѯͼ��");
	gotoxy(i,k+4);
	printf("��m���޸�ͼ��");
	gotoxy(i,k+6);
	printf("��c��ɾ��ͼ��");
	gotoxy(i,k+8);
	printf("��l�����ͼ��");
	gotoxy(i,k+10);
	printf("��b���黹ͼ��");
	gotoxy(i,k+12);
	printf("��s��������Ϣ");
	gotoxy(i,k+14);
	printf("��esc�˳�����");  
}

