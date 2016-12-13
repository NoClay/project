#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<windows.h>
#include<io.h>
#include<fcntl.h>
void gotoxy(int x, int y);
void cuowu(int i,int j, char str[]);
void paint_ps(int i);
void try_to_do();
void output(int i,int j,int k);
int ask_for(int i,int j);
void shuru_key();
void login();
void allsort();
void visit();
void delete_user();
void initsystem();
void user_save();
void number_loading();
int user_num=0;
int allflag=1;
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
struct user *user_read()
{
	FILE *fuser;
	struct user *pend;
	int i;
	fuser=fopen("f:/源代码/通讯录/通讯录.txt","rt");
	while(!feof(fuser))
	{
		struct user *pnew;
		pnew=(struct user*)malloc(sizeof(struct user));
		user_num++;
		if(user_num==1)
		{
			phead=pnew;
			phead->next=NULL;
			phead->last=NULL;
		} 
		else if(user_num==2)
		{
			pend=pnew;
			phead->next=pnew;
			pnew->last=phead;
			pnew->next=NULL;
		}
		else
		{
			pend->next=pnew;
			pnew->last=pend;
			pend=pend->next;
			pend->next=NULL;
		}
		fscanf(fuser,"%d %s %s %s %s %s ",&i,pnew->name,pnew->sex,pnew->age,pnew->birthday,pnew->number);
	}
	fclose(fuser);
	return phead;
}
void user_save()
{
	FILE *fuser;
	struct user *temp=phead;
	int i=1;
	fuser=fopen("f:/源代码/通讯录/通讯录.txt","wt");
	while(temp!=NULL)
	{
		fprintf(fuser,"%d\t%s\t%s\t%s\t%s\t%s\n",i,temp->name,temp->sex,temp->age,temp->birthday,temp->number);
		i++;
		temp=temp->next; 
	}
	fclose(fuser);
}
struct user *creat(int type,struct user *goost)//头插法
{
	int j=3;
	struct user *pnew;
	if(type==1)
	{
		pnew=(struct user*)malloc(sizeof(struct user));
		user_num++;
		if(user_num==1)
		{
			phead=pnew;
			phead->next=NULL;
			phead->last=NULL;
		} 
		else if(user_num==2)
		{
			phead->next=pnew;
			pnew->last=phead;
			pnew->next=NULL;
		}
		else
		{
			pnew->next=phead->next;
			phead->next->last=pnew;
			pnew->last=phead;
			phead->next=pnew;
		}
	}
	else if(type==2)
	{
		pnew=goost;
	} 
	gotoxy(0, j);
	printf("********************************************");
	j += 2;
	gotoxy(8,j);
	printf("序号：%d", user_num);
	j += 2;
	gotoxy(8,j);
	printf("姓名：");
	cuowu(14,j, pnew->name);
	j += 2;
	gotoxy(8, j);
	printf("性别：");
	cuowu(14,j, pnew->sex);
	j += 2;
	gotoxy(8, j);
	printf("年龄：");
	cuowu(14,j, pnew->age);
	j += 2;
	gotoxy(8, j);
	printf("生日：");
	cuowu(14,j, pnew->birthday);
	j += 2;
	gotoxy(8, j);
	printf("号码：");
	gets(pnew->number);
	while (pnew->number[0]=='0'||strlen(pnew->number)!=11)
	{
		gotoxy(14, j);
		printf("请输入正确的号码：");
		Sleep(1000);
		gotoxy(14, j);
		printf("                       ");
		gotoxy(14, j);
		gets(pnew->number);
	}
	allsort();
	return phead;
}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void cuowu(int i, int j,char str[])
{
	int c = 13;
	gets(str);
	while (str[0] == 13 || str[0] == 10 || str[0] == 0)
	{
		gotoxy(i, j);
		gets(str);
	}
	fflush(stdin);
}
void paint_ps()
{
	int j;
	int i=55;
	int k=5;
	for(j=i-2;j<i+20;)
	{
		gotoxy(j,k-2); 
		printf("━");
		gotoxy(j,k+12);
		printf("━");
		j=j+2;
	}
	for(j=k-1;j<k+12;j++)
	{
		gotoxy(i-4,j); 
		printf("┃");
		gotoxy(i+20,j);
		printf("┃");
	}
	gotoxy(i-4,k-2);
	printf("┏");
	gotoxy(i+20,k-2);
	printf("┓");
	gotoxy(i-4,k+12);
	printf("┗");
	gotoxy(i+20,k+12);
	printf("┛");
	gotoxy(i,k);
	printf("按k键新建一个联系人");
	gotoxy(i,k+2);
	printf("按n键查询任意联系人");
	gotoxy(i,k+4);
	printf("按m键修改当前联系人");
	gotoxy(i,k+6);
	printf("按c键删除当前联系人");
	gotoxy(i,k+8);
	printf("按s键保存所有联系人");
	gotoxy(i,k+10);
	printf("按esc退出通讯录");  
}
int ask_for(int i,int j,int type)
{
	char ch;
	gotoxy(i,j);
	if(type==1)
	{
		printf("是否继续查询？Y/N?");
	}
	else if(type==2)
	{
		printf("是否删除信息？Y/N?");
	}
	else if(type==3)
	{
		printf("是否继续删除？Y/N?");
	}
	else if(type==4)
	{
		printf("是否继续修改？Y/N?");
	}
	else if(type==5)
	{
		printf("是否修改信息？Y/N?");
	}
	else if(type==6)
	{
		printf("是否保存信息？Y/N?");
	}
	gotoxy(i,j+2);
	ch=getchar();
	while(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N')
	{
		gotoxy(i,j+2); 
		ch=getchar();
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
void visit_user()
{
	int flag=1;
	char ch;
	char str[20];
	int us_num=0;
	int success_flag=0;
	struct user *temp=phead;
	while(flag)
	{	
		system("cls");
		paint_ps();
		gotoxy(12,3);
		printf("请输入想要查询姓名或电话:");
		gotoxy(12,5);
		printf("                                  ");
		gotoxy(12,5);
		cuowu(12,5,str);
		while(temp!=NULL)
		{
			us_num++;
			if(strcmp(str,temp->name)==0||strcmp(str,temp->number)==0)
			{
				output(12,9,us_num);
				success_flag++;
				flag=0; 
			}
			temp=temp->next; 
		}
		gotoxy(12,7);
		printf("共%d个搜索结果！",success_flag);
		if(success_flag==0) 
		{
			gotoxy(12,9);
			printf("输入错误,查无此人！");
			flag=ask_for(12,11,1);
		}
	}
}
void output(int i,int j,int k)
{
	struct user *temp=phead;
	int us_num=0;
	while(temp!=NULL)
	{
		us_num++;
		if(us_num==k)
		{
			gotoxy(i,j);
			printf("序号：%d",k);
			j=j+2;
			gotoxy(i,j);
			printf("姓名：%s",temp->name);
			j=j+2;
			gotoxy(i,j);
			printf("性别：%s",temp->sex);
			j=j+2;
			gotoxy(i,j);
			printf("年龄：%s",temp->age);
			j=j+2;
			gotoxy(i,j);
			printf("生日：%s",temp->birthday);
			j=j+2;
			gotoxy(i,j);
			printf("电话：%s",temp->number);
			return;
		}
	} 
}
void delete_user()
{
	int flag=1;
	char ch;
	char str[20];
	int us_num=1;
	int us_num_flag;
	int success_flag=0;
	struct user *temp=phead; 
	while(flag)
	{	
		system("cls");
		paint_ps();
		gotoxy(12,3);
		printf("请输入想要删除的联系人的序号：");
		gotoxy(12,5);
		printf("                                  ");
		gotoxy(12,5);
		scanf("%d",&us_num_flag);
		while(us_num!=us_num_flag)
		{
			us_num++;
			temp=temp->next; 
		}
		if(us_num==us_num_flag)
		{
			success_flag=1;
			output(12,11,us_num_flag);
		}		
		if(success_flag==0) 
		{
			gotoxy(12,7);
			printf("输入错误,查无此人！");
			flag=ask_for(12,11,3);
		}
		else 
		{
			flag=ask_for(12,7,2);
			if(us_num_flag==1)
			{
				phead=phead->next;
				free(phead->last);
				phead->last=NULL;
			} 
			else if(us_num_flag==user_num&&user_num>1)
			{
				temp->last->next=NULL;
				free(temp);
			}
			else
			{
				temp->last->next=temp->next;
				temp->next->last=temp->last;
				free(temp);
			}
			flag=ask_for(12,7,3);	
		}
	}
} 
void allsort_user()
{
	int k=1;
	struct user *pnow=phead;
	struct user *pnext=pnow->next;
	struct user *temp;
	while(k)
	{
		k=0;
		pnow=phead;
		pnext=pnow->next;
		while(pnext!=NULL)
		{
			if(strcmp(pnow->name,pnext->name)>0)
			{
				if(pnow==phead)
				{
					phead->last=pnext;
					phead->next=pnext->next;
					pnext->next->last=phead;
					pnext->next=phead;
					pnext->last=NULL;
					phead=pnext;
					pnow=phead;
					pnext=pnow->next;					
				}
				else
				{
					pnow->last->next=pnext;
					pnext->next->last=pnow;
					pnow->next=pnext->next;	
					pnext->next=pnow;
					pnext->last=pnow->last;
					pnow->last=pnext;
					temp=pnow;
					pnow=pnext;
					pnext=temp;			
				}
				k=1;
			}
			pnow=pnow->next;
			pnext=pnow->next;
		}
	}	
}
void change_user()
{
	int flag=1;
	char ch;
	char str[20];
	int us_num=1;
	int us_num_flag;
	int success_flag=0;
	struct user *temp=phead; 
	while(flag)
	{	
		system("cls");
		paint_ps();
		gotoxy(12,3);
		printf("请输入想要修改的联系人的序号：");
		gotoxy(12,5);
		printf("                                  ");
		gotoxy(12,5);
		scanf("%d",&us_num_flag);
		while(us_num!=us_num_flag)
		{
			us_num++;
			temp=temp->next; 
		}
		if(us_num==us_num_flag)
		{
			success_flag=1;
			output(12,11,us_num_flag);
		}		
		if(success_flag==0) 
		{
			gotoxy(12,7);
			printf("输入错误,查无此人！");
			flag=ask_for(12,11,5);
		}
		else 
		{
			flag=ask_for(12,7,6);
			phead=creat(2,temp);
			flag=ask_for(12,7,5);	
		}
	}
}
void shuru_key()
{
	int i,c,flag6=1;
	for(i=0;i<16;)
	{
		c=getch();
		if(flag6==1)
		{
			gotoxy(12,7);
			printf("                        ");
			gotoxy(12,7);
			flag6=0;
		}
		if(c==13&&key_to_do[0]!=13&&key_to_do[i]!=10)
		{
			i=21;
		}
		else if(c==8&&i>0)
		{
			printf("\b \b");
			i--;
		}
		else
		{
			key_to_do[i]=c;
			printf("*");
			i++;
		}
	}
}
void login()
{
	char str[20],choose_do;
	gotoxy(4,5);
	printf("账号:  请输入账号/用户名/邮箱");
	gotoxy(4,7);
	printf("密码： 请输入密码");
	gotoxy(12,5);
	Sleep(2000);
	printf("                              ");
	gotoxy(12,5);
	scanf("%s",user_to_do); 	
	while(user_to_do[0]==13||user_to_do==0)
	{
	printf("                              ");
	gotoxy(12,5);
	gets(user_to_do);
	}
	gotoxy(12,7);
	shuru_key();
	while(strcmp(key_to_do,key_do)!=0||(strcmp(user_to_do,user1)!=0&&strcmp(user_to_do,user2)!=0&&strcmp(user_to_do,user3)!=0))
	{
		while(strcmp(user_to_do,user1)!=0&&strcmp(user_to_do,user2)!=0&&strcmp(user_to_do,user3)!=0)
		{
			gotoxy(12,5);
			printf("账号错误！请重新输入！");
			gotoxy(12,7);
			printf("                        ");
			gotoxy(12,5);
			Sleep(2000);
			printf("                              ");
			gotoxy(12,5);
			scanf("%s",user_to_do); 
		} 
		gotoxy(12,7);
		printf("密码错误！请重新输入！");
		gotoxy(12,7);
		shuru_key(); 
	}
	fflush(stdin); 
	gotoxy(4,9);
	printf("登录Y/N？:");
	gotoxy(14,9);
	scanf("%c",&choose_do);
	while(choose_do!='y'&&choose_do!='Y'&&choose_do!='n'&&choose_do!='N')
	{
		scanf("%c",&choose_do);
	}
	if(choose_do=='N'||choose_do=='n')
	{
		flag7=0;
	} 	
}
void try_to_do()
{
	char c;
	c=getch();
	while(c!=27&&c!='m'&&c!='n'&&c!='c'&&c!='k'&&c!='s')  c=getch();
	switch(c)
	{
	case 27:allflag=0;break;
	case 'm':change_user();try_to_do();break;
	case 'n':visit_user();try_to_do();break;
	case 'k':
		{
			system("cls");
			paint_ps();
			phead=creat(1,phead);
			try_to_do();
		};break;
	case 'c':delete_user();try_to_do();
	case 's':user_save();try_to_do();break;
	}
}
int main()
{
	char c;
	all_flag=1;
	login();
	if(flag7==1)
	{
		us_num=0;
		system("cls");
		gotoxy(0, 3);
		printf("********************************************");
		gotoxy(8,1);
		printf("欢迎“%s”用户使用通讯录！\n",);
		phead = (struct user*)malloc(sizeof(struct user));
		paint_ps(55,5);
		try_to_do(0);
	}	
}
