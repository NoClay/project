#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<windows.h>
#include<io.h>
#include<fcntl.h>
char key_store[60]="f:/��Ŀ����/ͼ�����ϵͳ/��¼��Ϣ.txt";
char keyin[10]="826611389"; 
char flag_name[30];
void lockit(char str[]);
void login();
int allflag=1;
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void cuowu(int i, int j,int type,char str[])
{
	char str1[40];
	int k;
	k=sizeof(str);
	fflush(stdin);
	if(type==0)
	{
		gotoxy(i,j);	
		gets(str1);
		while (str1[0] == 13 || str1[0] == 10 || str1[0] == 0)
		{
			gotoxy(i, j);
			gets(str1);
			fflush(stdin);
		}
		sprintf(str,"%s",str1);
	}
	else
	{
		gotoxy(i,j);
		gets(str1);
		if(str1[0]!=13&&str1[0]!=10&&str1[0]!=0)
		{
			sprintf(str,"%s",str1);
		}
	}
	fflush(stdin);
}
void paintrectangle(int i,int j,int a,int b)
{
	int k;
	for(k=i+2;k<i+2+a;)
	{
		gotoxy(k,j);
		printf("��");
		gotoxy(k,j+b+1);
		printf("��");
		k=k+2;
	}
	for(k=j;k<j+1+b;k++)
	{
		gotoxy(i,k);
		printf("��");
		gotoxy(i+a+2,k);
		printf("��");
	}
	gotoxy(i,j);
	printf("��");
	gotoxy(i+a+2,j);
	printf("��");
	gotoxy(i,j+b+1);
	printf("��");
	gotoxy(i+a+2,j+b+1);
	printf("��");
}
char *shuru_key(int i,int j,char keystr[])
{
	int k=0,flag6=1;
	int count=i;
	char ch;
	char keystore1[20];
	while(k<=16)
	{
		ch=getch();
		if(flag6==1)
		{
			gotoxy(i,j);
			printf("                        ");
			gotoxy(i,j);
			flag6=0;
		}
		if(ch==13&&count>=i+6)
		{
			k=20;
		}
		else if(ch==8&&count>=i)
		{
			if(count>=i+16)
			{
				printf("\b \b");
			}
			count--;
		}
		else if(ch!=8&&ch!=13)
		{
			keystore1[count-i]=ch;
			if(count<=i+16)
			{
				printf("*");
			}
			count++;
		}
	}
	sprintf(keystr,"%s",keystore1);
}
int ask_for(int i,int j,int type)
{
	char ch;
	gotoxy(i,j);
	if(type==1)
	{
		printf("�Ƿ������ѯ��Y/N?");
	}
	else if(type==2)
	{
		printf("�Ƿ�ɾ����Ϣ��Y/N?");
	}
	else if(type==3)
	{
		printf("�Ƿ����ɾ����Y/N?");
	}
	else if(type==4)
	{
		printf("�Ƿ�����޸ģ�Y/N?");
	}
	else if(type==5)
	{
		printf("�Ƿ��޸���Ϣ��Y/N?");
	}
	else if(type==6)
	{
		printf("�Ƿ񱣴���Ϣ��Y/N?");
	}
	else if(type==7)
	{
		printf("�Ƿ�ȫ��ɾ����Y/N?");
	}
	else if(type==8)
	{
		printf("�Ƿ��¼��Y/N��");
	}
	else if(type==9)
	{
		printf("�Ƿ�ע�᣿Y/N��"); 
	} 
	else if(type==10)
	{
		printf("�Ƿ�Ϊ����Ա��Y/N��"); 
	}
	else if(type==11)
	{
		printf("�Ƿ������¼��Y/N��"); 
	}
	ch=getche();
	while(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N')
	{
		ch=getche();
	}
	if(ch=='y'||ch=='Y')
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
void login()
{
	char user_name[20];
	int userclass,success_flag=0,success=0;
	char user_key[20];
	char username[20];
	char userkey[20]; 
	char usernumber[20];
	char user_number[20];
	FILE *fuser;
	while(allflag)
	{
	fuser=fopen(key_store,"rt+");
	gotoxy(4,5);
	printf("�˺�:   �������˺�/�û���/����");
	gotoxy(4,8);
	printf("����:   ����������");
	paintrectangle(9,4,26,1);
	paintrectangle(9,7,26,1);
	paintrectangle(0,0,40,15);
	gotoxy(12,5);
	Sleep(2000);
	printf("                         ");
	cuowu(12,5,0,user_name);
	gotoxy(12,8);
	shuru_key(12,8,user_key);
	fflush(stdin); 
	allflag=ask_for(4,11,8);
	while(success_flag==0)
	{
		rewind(fuser); 
		while(!feof(fuser))
		{
			fscanf(fuser,"%s %s  %s %d ",username,usernumber,userkey,&userclass);
			if((strcmp(username,user_name)==0||strcmp(usernumber,user_number)==0)&&strcmp(user_key,userkey)==0)
			{
				success_flag++;
				break;
			}
		}
		if(success_flag==0)
		{
			gotoxy(12,5);
			printf("��Ϣ�������������룡");
			gotoxy(12,5);
			Sleep(1000);
			printf("                         ");
			cuowu(12,5,0,user_name);
			gotoxy(12,8);
			shuru_key(12,8,user_key);
			fflush(stdin);
			success++; 
		}
		if(success>3)
		{
			gotoxy(4,13);
			printf("��δ��󣬰ݰݣ�");
			allflag=0; 
			break;
		}
	} 
	if(success<=3&&success_flag!=0)
	{
		allflag=ask_for(4,11,8);
		if(userclass==1)
		{
			sprintf(flag_name,"%s����Ա",username);			
		}
		else
		{
			sprintf(flag_name,"%sͬѧ",username);
		} 
		printf("��ӭ"); 
	}
	fclose(fuser);
	} 
	
}
void number(char numberstr[])
{
	FILE *fuser;
	char username[20];
	int userclass,success_flag=1;
	char userkey[20];
	char usernumber[20];
	char user_number[20];
	srand((unsigned)time(NULL));
	fuser=fopen(key_store,"rt");
	while(success_flag)
	{
		sprintf(user_number,"%d%d%d%d%d%d%d%d",rand()%10,rand()%10,rand()%10,rand()%10,rand()%10,rand()%10,rand()%10,rand()%10);
		rewind(fuser);
		success_flag=0;
		while(!feof(fuser))
		{
			fscanf(fuser,"%s %s  %s %d ",username,usernumber,userkey,&userclass);
			if(strcmp(user_number,usernumber)==0)
			{
				success_flag++;
			}
		}
	}
	fclose(fuser);
	sprintf(numberstr,"%s",user_number);
} 
void sign()
{
	char user_name[20];
	int userclass=2,success_flag=0,success=0;
	char user_key[20];
	char userkey[20];
	char usernumber[20];
	FILE *fuser;
	fuser=fopen(key_store,"at+");
	gotoxy(4,5);
	printf("�ǳ�:   ���������Ļ�Ӣ��");
	gotoxy(4,8);
	printf("����:   ����������");
	gotoxy(4,11);
	printf("ȷ��:   ���ٴ���������"); 
	paintrectangle(9,4,26,1);
	paintrectangle(9,7,26,1);
	paintrectangle(9,10,26,1); 
	paintrectangle(0,0,40,20);
	gotoxy(12,5);
	Sleep(1000);
	printf("                         ");
	cuowu(12,5,0,user_name);
	gotoxy(12,8);
	shuru_key(12,8,user_key);
	fflush(stdin); 
	shuru_key(12,11,userkey);
	fflush(stdin);
	while(strcmp(user_key,userkey)!=0)
	{
		gotoxy(12,11);
		printf("���벻һ�£�");
		Sleep(1000);
		gotoxy(12,11);
		printf("               ");
		shuru_key(12,8,user_key);
		fflush(stdin); 
		shuru_key(12,11,userkey);
		fflush(stdin);
	}
	if(ask_for(4,14,10))
	{
		while(1)
		{
			gotoxy(4,16);
			printf("���룺  ���������Ա���룡");
			shuru_key(12,14,userkey);
			if(strcmp(userkey,keyin)==0)
			{
				userclass=1;
				break;
			}
		}
	}
	if(ask_for(4,18,9))
	{
		number(usernumber);
		gotoxy(12,18);
		printf("�˺�Ϊ��%s",usernumber);
		getch();
		fprintf(fuser,"%s\t%s\t%s\t%d\n",user_name,usernumber,user_key,userclass);
	}
	else
	{
		allflag=0;
	}
	fclose(fuser); 
}
int main()
{
	char str[20];
	cuowu(1,1,1,str); 
}
