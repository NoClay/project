#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<windows.h>
char user1[] = "826611389";
char user2[] = "瞬间永恒";
char user3[] = "826611389@qq.com";
char key_do[] = "123456789";
char key_to_do[17];
char user_to_do[30];
int us_num;
int FLAG = 0;
int flag1, flag7 = 1;
int try_do;
void init_system();
void intput(int i);
int check(char number[]);
void output(int i);
void paint_ps(int i);
void try_to_do(int i);
void visit();
void shuru_key();
void login();
void delete_us(int i);
void xulie();
void gotoxy(int x, int y);
void cuowu(int i, char str[]);
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct user
{
	struct user *last;
	char name[20];
	char sex[4];
	char age[6];
	char birthday[15];
	char number[12];
	struct user *next;
};
struct user *phead;
struct user *pend;
void cuowu(int i, char str[])
{
	int c = 13;
	gets_s(str, sizeof(str));
	while (str[0] == 13 || str[0] == 10 || str[0] == 0)
	{
		gotoxy(14, i);
		gets_s(str, sizeof(str));
	}
	fflush(stdin);
}
struct user *creat()//头插法//循环双链表
{
	int j=3;
	struct user *pnew;
	pnew = (struct user*)malloc(sizeof(struct user));
	if(phead->next==NULL)
	{
		phead->next = pnew;
		pnew->last = phead;
		pnew->next = phead;
		phead->last = pnew;
	}
	else
	{
		pnew->next = phead->next;
		pnew->last = phead;
		phead->next->last = pnew;
		phead->next = pnew;
	}
	us_num++;
	gotoxy(8, j - 2);
	printf("欢迎使用通讯录！");
	gotoxy(0, j);
	printf("*************************************");
	j += 2;
	gotoxy(8, j);
	printf("序号：%d", us_num);
	j += 2;
	gotoxy(8, j);
	printf("姓名：");
	cuowu(j, pnew->name);
	j += 2;
	gotoxy(8, j);
	printf("性别：");
	cuowu(j, pnew->sex);
	j += 2;
	gotoxy(8, j);
	printf("年龄：");
	cuowu(j, pnew->age);
	j += 2;
	gotoxy(8, j);
	printf("生日：");
	cuowu(j, pnew->birthday);
	j += 2;
	gotoxy(8, j);
	printf("号码：");
	gets_s(pnew->number,sizeof(pnew->number));
	while (pnew->number[0]=='0'||strlen(pnew->number)!=11)
	{
		gotoxy(14, j);
		printf("请输入正确的手机号：");
		Sleep(1000);
		gotoxy(14, j);
		printf("                       ");
		gotoxy(14, j);
		gets_s(pnew->number,sizeof(pnew->number));
	}
	return phead;
}
void paint_ps(int i)
{
	int j;
	gotoxy(45, i - 4);
	for (j = 0; j < 30; j++)
	{
		printf("*");
	}
	gotoxy(55, i - 2);
	printf("操作菜单：");
	gotoxy(50, i);
	printf("按k键新建一个联系人");
	gotoxy(50, i + 2);
	printf("按n键查询任意联系人");
	gotoxy(50, i + 4);
	printf("按m键修改当前联系人");
	gotoxy(50, i + 6);
	printf("按c键删除当前联系人");
	gotoxy(50, i + 8);
	printf("按esc退出通讯录");
	gotoxy(45, i + 10);
	for (j = 0; j < 30; j++)
	{
		printf("*");
	}
	for (j = i - 2; j < i + 10;)
	{
		gotoxy(45, j);
		printf("◇");
		gotoxy(73, j);
		printf("◇");
		j += 2;
	}
}
void init_system()
{
	phead = (struct user*)malloc(sizeof(struct user));
	phead->next = phead->last = NULL;
}
int main()
{
	init_system();
	paint_ps(7);
	phead=creat();
}