#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<windows.h>
#include<io.h>
#include<fcntl.h>
void gotoxy(int x, int y);//移动光标的位置 
void booksave();//保存图书到固定的文件 
void cuowu(int i, int j,char str[]); //输入合法的字符串 
void allsort();//对所有数据 以书名为根据进行排序 
void visitall();//查找书目 
int compare(char str[],struct book *key);//模糊对比数据 
int ask_for(int i,int j,int type);//询问是否继续进行下一步操作 Y返回1  n返回0 
void deletebook(int type);//删除图书 
int output(int i,int j,int k);//把所需的图书输出出来 
void shuru_key(int i,int j,char keystr[]);//输入密码的函数 
void try_to_do();//操作判断函数 
void change(int type_key);//1表示修改，2 表示借出 3表示归还 
void paintrectangle(int i,int j,int a,int b);//用字符对出一个矩形框 
void paint_ps();//显示菜单  用户和管理员菜单的输出 
void sign();//注册账户 
int login();//登陆函数 
void number(char numberstr[]);//产生随机8位账号 
int book_num=0;//全局变量表示数据库书目数 
int allflag=1;//全局执行变量1为正常的执行，0为退出 
char key_store[60]="f:/登录信息.txt";//登录信息储存的位置 
int user_type;//登陆用户的等级 
char keyin[20]="826611389";//管理员的核心内码，注册时使用 
char flag_name[30];//全局用户昵称 
char strok[4]="是";
char strno[4]="否";
struct book//定义书籍结构体 
{
	struct book *last;
	char number[20];//书号 
	char name[50];//书名 
	char author[20];//作者 
	char kind[20];//类别 
	char adress[30];//出版社 
	char price[10];//价格 
	char type[4];//是否在库 
	char lendtime[20];//借出时间 
	char backtime[20];//归还时间 
	struct book *next;
};
struct book *phead;
struct book *read()//读取数据库信息，上载书目 
{
	FILE *fbook;
	struct book *pend;
	long count=0;
	long size;
	long last=75;
	fbook=fopen("f:/图书管理.txt","rt");
	if(fbook==NULL)//如果没有该文件，则建立该文件 ，否则进行读取 
	{
		fclose(fbook);
		fbook=fopen("f:/图书管理.txt","wt");
		fprintf(fbook,"书号\t书名\t作者\t类别\t出版社\t价格\t是否在库 借出时间\t归还时间\t当前库包含数据：%d\n",0);
		fclose(fbook);
		fbook=fopen("f:/图书管理.txt","rt");	
	}
	fseek(fbook,last,0);
	fscanf(fbook,"%d",&size);
	while(count!=size)
	{
		struct book *pnew;
		pnew=(struct book*)malloc(sizeof(struct book));
		book_num++;
		count++;
		if(book_num==1)
		{
			phead=pnew;
			phead->next=NULL;
			phead->last=NULL;
		} 
		else if(book_num==2)
		{
			phead->next=pnew;
			pnew->last=phead;
			pnew->next=NULL;
			pend=pnew;
		}
		else
		{
			pend->next=pnew;
			pnew->last=pend;
			pend=pend->next;
			pend->next=NULL;
		}
		fscanf(fbook,"%s %s %s %s %s %s %s %s %s ",pnew->number,pnew->name,pnew->author,pnew->kind,pnew->adress,pnew->price,pnew->type,pnew->lendtime,pnew->backtime);
	}
	fclose(fbook);
	return phead;
}
void booksave()//把程序内数据保存到文件中 
{
	FILE *fbook;
	struct book *temp=phead;
	fbook=fopen("f:/图书管理.txt","wt");
	fprintf(fbook,"书号\t书名\t作者\t类别\t出版社\t价格\t是否在库 借出时间\t归还时间\t当前库包含数据：%d\n",book_num);
	while(temp!=NULL)
	{
		fprintf(fbook,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",temp->number,temp->name,temp->author,temp->kind,temp->adress,temp->price,temp->type,temp->lendtime,temp->backtime);
		temp=temp->next; 
	}
	gotoxy(0,3);
	printf("保存成功!");
	fclose(fbook);
}
void cuowu(int i, int j,int type,char str[])//在合适合法输入字符串//i,j表示光标的定位//type表示输入的类型 
{
	char str1[40];
	fflush(stdin);
	if(type==0)//类型0表示字符串内没有值，输入回车光标返回继续执行输入 
	{
		gotoxy(i,j);	
		gets(str1);
		while (str1[0] == 13 || str1[0] == 10 || str1[0] == 0)
		{
			gotoxy(i, j);
			gets(str1);
			fflush(stdin);
		}
		sprintf(str,"%s",str1);//将合法字符串打印到目标字符串 
	}
	else//类型为1表示目标字符串有值，回车后跳过输入，进入下一个 
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
struct book *creat(int j,int k,int type,struct book *goost)//头插法//i,j定位光标//type为类型//1为输入//2为修改//3为借出 
{
	struct book *pnew;
	time_t timep; 
	struct tm *p; 
	int howtype=0;//区别的输入类型变量 
	if(type==1||type==2)
	{
		if(type==1)
		{
			pnew=(struct book*)malloc(sizeof(struct book));
			book_num++;
			if(book_num==1)
			{
				phead=pnew;
				phead->next=NULL;
				phead->last=NULL;
			} 
			else if(book_num==2)
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
			gotoxy(k,j++);
			printf("书号：");
			gotoxy(k,j++);
			printf("书名：");
			gotoxy(k,j++);
			printf("作者："); 
			gotoxy(k,j++);
			printf("类别：");
			gotoxy(k,j++);
			printf("出版社：");
			gotoxy(k,j++);
			printf("价格：");
			gotoxy(k,j++);
			printf("是否借出？（在库为是；借出为否）：");
		}
		else
		{
			howtype=1;
		}
		cuowu(k+6,j-7,howtype,pnew->number);
		cuowu(k+6,j-6,howtype,pnew->name);
		cuowu(k+6,j-5,howtype,pnew->author);
		cuowu(k+6,j-4,howtype, pnew->kind);
		cuowu(k+8,j-3,howtype, pnew->adress);
		cuowu(k+6,j-2,howtype, pnew->price);
		cuowu(k+34,j-1,howtype, pnew->type);
		while(strcmp(pnew->type,strno)!=0&&strcmp(pnew->type,strok)!=0)
		{
			cuowu(k+34,j-1,howtype, pnew->type);
		}
	}
	if(strcmp(pnew->type,strno)==0)
	{
		if(type==3)
		{
			time(&timep); 
			p=localtime(&timep); 
			sprintf(pnew->lendtime,"%4d.%2d.%2d",(1900+p->tm_year), (1+p->tm_mon),p->tm_mday);//获取当天日期，作为借书日期 
			gotoxy(k, j-2);
			printf("借出时间(例：2015.06.02):%s",pnew->lendtime);
			gotoxy(k, j-1);
			printf("归还时间(例：2015.06.02):");
			cuowu(k+25,j-1,1, pnew->backtime);
		}
		else
		{
			gotoxy(k, j++);
			printf("借出时间(例：2015.06.02):");
			gotoxy(k, j++);
			printf("归还时间(例：2015.06.02):");
			cuowu(k+25,j-2,howtype, pnew->lendtime);
			cuowu(k+25,j-1,howtype, pnew->backtime);
		}
	}
	else
	{
		sprintf(pnew->lendtime,"0000.00.00");
		sprintf(pnew->backtime,"0000.00.00");
	}
	allsort();//进行排序 
	return phead;
}
void gotoxy(int x, int y)//光标定位函数 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void paintrectangle(int i,int j,int a,int b)//画出一个矩形框 
{
	int k;
	for(k=i+2;k<i+2+a;)
	{
		gotoxy(k,j);
		printf("━");
		gotoxy(k,j+b+1);
		printf("━");
		k=k+2;
	}
	for(k=j;k<j+1+b;k++)
	{
		gotoxy(i,k);
		printf("┃");
		gotoxy(i+a+2,k);
		printf("┃");
	}
	gotoxy(i,j);
	printf("┏");
	gotoxy(i+a+2,j);
	printf("┓");
	gotoxy(i,j+b+1);
	printf("┗");
	gotoxy(i+a+2,j+b+1);
	printf("┛");
}
void paint_ps()
{
	int j;
	int i=70;
	int k=5;
	int weitiao[4]={0,0,0,0}; 
	gotoxy(15,1);
	printf("欢迎%s使用图书管理系统！",flag_name);
	gotoxy(0,2);
	printf("***************************************************************"); 
	if(user_type==1)
	{
		paintrectangle(i-4,k-2,16,19); 
	}
	else 
	{
		paintrectangle(i-4,k-2,16,10);//用户界面菜单框 
		weitiao[0]=-2;//坐标修正 
		weitiao[1]=-6;
		weitiao[2]=-10;
	}
	gotoxy(i,k);
	printf("按k键新增图书");
	gotoxy(i,k+2+weitiao[0]);
	printf("按n键查询图书");
	gotoxy(i,k+4);
	printf("按m键修改图书");
	gotoxy(i,k+6);
	printf("按c键删除图书");
	gotoxy(i,k+8+weitiao[1]);
	printf("按l键借出图书");
	gotoxy(i,k+10+weitiao[1]);
	printf("按b键归还图书");
	if(user_type==1)
	{
		gotoxy(i,k+12);
		printf("按s键保存图书");
		gotoxy(i,k+14);
		printf("按a键全部删除");
	}
	gotoxy(i,k+16+weitiao[2]);
	printf("按esc退出使用");  
}
int output(int i,int j,int k)
{
	struct book *temp=phead;
	int cj=0;
	int bk_num=1;
	while(bk_num!=k)//遍历到固定的书籍 执行输出 
	{
		bk_num++;
		temp=temp->next;
	}
	gotoxy(i,j);
	printf("书号：%s",temp->number);
	j++;
	gotoxy(i,j);
	printf("书名：%s",temp->name);
	j++;
	gotoxy(i,j);
	printf("作者：%s",temp->author);
	j++;
	gotoxy(i,j);
	printf("类别：%s",temp->kind);
	j++;
	gotoxy(i,j);
	printf("出版社：%s",temp->adress);
	j++;
	gotoxy(i,j);
	printf("价格：%s",temp->price);
	j++;;
	gotoxy(i,j);
	printf("是否借出？（在库为是；借出为否）：%s",temp->type);
	j++;
	if(strcmp(temp->type,strno)==0)
	{
		gotoxy(i,j);
		printf("借出时间(例：2015.06.02):%s",temp->lendtime);
		j++;
		gotoxy(i,j);
		printf("归还时间(例：2015.06.02):%s",temp->backtime);
		j++;
	}
	return j;//返回光标行的位置		
}
void allsort()
{
	int k=1;
	struct book *pnow=phead;
	struct book *pnext=pnow->next;
	struct book *temp;
	while(k)
	{
		k=0;
		pnow=phead;
		pnext=pnow->next;
		while(pnext!=NULL)
		{
			if(strcmp(pnow->name,pnext->name)>0)
			{
				if(book_num==2)
				{
					pnext->next=pnow;
					pnext->last=NULL;
					pnow->last=pnext;
					pnow->next=NULL;
					phead=pnext;
					pnow=pnext;
					pnext=pnow->next;
				}
				else
				{
					if(pnow==phead)
					{
						pnext->next->last=phead;
						phead->next=pnext->next;
						pnext->next=phead;
						phead->last=pnext;
						pnext->last=NULL;
						phead=pnext;
						pnow=phead;
						pnext=phead->next;				
					}
					else if(pnext->next==NULL)
					{
						pnow->last->next=pnext;
						pnext->last=pnow->last;
						pnow->last=pnext;
						pnext->next=pnow;
						pnow->next=NULL;
						pnow=pnext;
						pnext=pnow->next;
					}
					else
					{
						pnext->next->last=pnow;
						pnow->last->next=pnext;
						pnow->next=pnext->next;
						pnext->next=pnow;
						pnext->last=pnow->last;
						pnow->last=pnext;					
						pnow=pnext;
						pnext=pnow->next;			
					}
				}
				k=1;
			}
			pnow=pnow->next;
			pnext=pnow->next;
		}
	}	
}
int ask_for(int i,int j,int type)//寻求执行操作 //i,j定位光标//type表示执行寻求时操作提示信息的类型 
{
	char ch;
	gotoxy(i,j);
	char todo[40];
	char sort[20][30]={"继续查询","删除信息","继续删除","继续修改","修改信息","保存信息","全部删除","登录","注册","为管理员","继续借书","继续还书"};
	sprintf(todo,"是否%s？Y/N?",sort[type-1]);
	printf("%s",todo);
	ch=getche();
	while(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N')
	{
		gotoxy(i+strlen(todo),j);
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
void visitall()
{
	int flag=1;
	int bk_num=0,i=0,j=5,pass;
	char str[40];
	int success_flag=0;
	struct book *temp=phead;
	while(flag)
	{	
		gotoxy(0,3);
		printf("请输入信息：");
		cuowu(12,3,0,str);
		while(temp!=NULL)
		{
			bk_num++;
			if(compare(str,temp)==1)//模糊判定数据 
			{
				success_flag++;//搜索结果标志 
				pass=output(i,j,bk_num);
				j=pass;
			}
			temp=temp->next;		
		}
		gotoxy(0,4);
		printf("共%d个搜索结果！",success_flag);
		if(success_flag==0) 
		{
			gotoxy(0,5);
			printf("输入错误,查无此书！");
			flag=ask_for(0,6,1);
		}
		else
		{
			flag=ask_for(0,j,1);	
		}
		if(flag==1)//继续查询恢复 
		{
			system("cls");
			paint_ps();
			success_flag=0;
			bk_num=0,i=0,j=5;
			temp=phead;
		}
	}
}
int compare(char str[],struct book *key)
{
	int size,sizenumber,sizename,sizekind,sizeadress,sizeauthor,i,j,success[5]={0,0,0,0,0};
	size=strlen(str);
	sizenumber=strlen(key->number);
	sizename=strlen(key->name);
	sizekind=strlen(key->kind);
	sizeadress=strlen(key->adress);
	sizeauthor=strlen(key->author);
	for(i=0;i<sizenumber-size+1;i++)//对书号进行模糊判定 
	{
		success[0]=1;
		for(j=0;j<size;j++)
		{
			if(str[j]!=key->number[j+i])
			{
				success[0]=0;
			}
		}
		if(success[0]==1)
		{
			break;
		}
	}
	for(i=0;i<sizename-size+1;i++)//对书名进行模糊判定 
	{
		success[1]=1;
		for(j=0;j<size;j++)
		{
			if(str[j]!=key->name[j+i])
			{
				success[1]=0;
			}
		}
		if(success[1]==1)
		{
			break;
		}
	}
	for(i=0;i<sizekind-size+1;i++)//对书类进行模糊判定 
	{
		success[2]=1;
		for(j=0;j<size;j++)
		{
			if(str[j]!=key->kind[j+i])
			{
				success[2]=0;
			}
		}
		if(success[2]==1)
		{
			break;
		}
	}
	for(i=0;i<sizeadress-size+1;i++)//对出版社进行模糊判定 
	{
		success[3]=1;
		for(j=0;j<size;j++)
		{
			if(str[j]!=key->adress[j+i])
			{
				success[3]=0;
			}
		}
		if(success[3]==1)
		{
			break;
		}
	}
	for(i=0;i<sizeauthor-size+1;i++)//对作者进行模糊判定 
	{
		success[4]=1;
		for(j=0;j<size;j++)
		{
			if(str[j]!=key->author[j+i])
			{
				success[4]=0;
			}
		}
		if(success[4]==1)
		{
			break;
		}
	}
	if((success[0]+success[1]+success[2]+success[3]+success[4])!=0)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
void deletebook(int type)//删除图书//type表示删除类型//1为单个删除//2为全部删除 
{
	int flag=1;
	char ch;
	char str[40];
	int bk_num=0,i=0,j=4;
	int success_flag=0;
	struct book *temp=phead;
	struct book *tempnext; 
	if(type==1)
	{
		while(flag)
		{	
			gotoxy(0,3);
			printf("请输入具体书号或书名：");
			cuowu(22,3,0,str);
			while(temp!=NULL)
			{
				bk_num++;
				if(strcmp(str,temp->number)==0||strcmp(str,temp->name)==0)
				{
					j=output(i,j,bk_num);
					success_flag++;
					break;
				}
				temp=temp->next;		
			}
			if(success_flag==0) 
			{
				gotoxy(0,4);
				printf("输入错误,查无此书！");
				flag=ask_for(0,5,3);
			}
			else
			{
				flag=ask_for(0,j,2);
				if(flag==1)
				{
					if(book_num==1)
					{
						free(phead);
						phead=NULL;
					}
					else
					{
						if(bk_num==1)
						{
							phead=phead->next;
							free(phead->last);
						}
						else if(bk_num==book_num)
						{
							temp->last->next=NULL;
							free(temp);
						}
						else
						{
							tempnext=temp->next;
							temp->last->next=temp->next;
							tempnext->last=temp->last;
							free(temp);				
						}
					}
					book_num--;
				}
				j++;
				flag=ask_for(i,j,3);		
			}
			if(flag==1)
			{
				success_flag=0;
				bk_num=0,i=0,j=4;
				temp=phead;
				system("cls");
				paint_ps();
			}
		}
	}
	else if(type==2)
	{
		j--;
		flag=ask_for(i,j++,7);//进行三次执行判断，防止误删文件 
		if(flag==1)
		{
			flag=ask_for(i,j++,7);
			if(flag==1)
			{
				flag=ask_for(i,j++,7);
				if(flag==1)
				{
					while(temp!=NULL)
					{
						tempnext=temp->next;
						free(temp);
						temp=tempnext;
					}
					phead=NULL;
					book_num=0;
					gotoxy(0,j);
					printf("删除成功！当前数据库无数据！");
				}
				else
				{
					gotoxy(0,j);
					printf("未删除全部数据！");
				}
				flag=0;
			}
			else
			{
				gotoxy(0,j);
				printf("未删除全部数据！");
			}
		}
		else
		{
			gotoxy(0,j);
			printf("未删除全部数据！");
		}	
	}
}
void shuru_key(int i,int j,char keystr[])
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
		if(ch==13&&count>=i+6)//密码 6位以上且输入回车则退出输入密码//否则不执行 
		{
			k=20;
		}
		else if(ch==8&&count>i)//按删除键删除错误的一位密码 
		{
			if(count<=i+16)
			{
				printf("\b \b");
			}
			count--;
		}
		else if(ch!=8&&ch!=13&&count<=i+16)//遇到极限位数停止输入 
		{
			keystore1[count-i]=ch;
			printf("*");
			count++;
		}
	}
	sprintf(keystr,"%s",keystore1);
}
void change(int type_key)//1表示修改，2 表示借出 3表示归还 
{
	int flag=1;
	char ch;
	char str[40];
	int bk_num=0,i=0,j=3;
	int success_flag=0;
	struct book *temp=phead; 
	while(flag)
	{	
		gotoxy(i,j);
		printf("请输入具体书号或书名：");
		cuowu(22,j,0,str);
		while(temp!=NULL)
		{
			bk_num++;
			if(strcmp(str,temp->number)==0||strcmp(str,temp->name)==0)
			{
				j++;
				success_flag++;
				break;
			}
			temp=temp->next;
		}
		if(success_flag==0)
		{
			j++;
			gotoxy(i,j);
			printf("输入错误，查无此书!");
			j++;
			if(type_key==1)
			{
				flag=ask_for(i,j,4);
			}
			else if(type_key==2)
			{
				flag=ask_for(i,j,11);
			}
			else
			{
				flag=ask_for(i,j,12);
			}
		}
		else
		{
			if(type_key==1)
			{
				j=output(i,j,bk_num);
				phead=creat(j,i,2,temp);//调用前边复合功能函数修改 
				if(strcmp(temp->type,strno)==0)
				{
					j=j+2;
				}
				flag=ask_for(i,j,4);
			}
			else if(type_key==2)
			{
				if(strcmp(temp->type,strok)==0)
				{
					sprintf(temp->type,"%s",strno);
					j=output(i,j,bk_num);
					phead=creat(j,i,3,temp);	
				}
				else
				{
					printf("对不起，该书已被借出，归还时间:%s",temp->backtime);
					j++;
				}
				flag=ask_for(i,j,11);
			}
			else if(type_key==3)
			{
				sprintf(temp->type,"%s",strok);
				sprintf(temp->lendtime,"0000.00.00");
				sprintf(temp->backtime,"0000.00.00");
				j=output(i,j,bk_num);
				flag=ask_for(i,j,12);		
			}
		}
		if(flag==1)
		{
			system("cls");
			paint_ps();
			bk_num=0,i=0,j=3;
			success_flag=0;
			temp=phead;
		}
	}
}
void try_to_do()//菜单的判断执行 
{
	char c;
	c=getch();
	if(user_type==1)//管理员时合法输入字符 
	{
		while(c!=27&&c!='m'&&c!='n'&&c!='c'&&c!='k'&&c!='s'&&c!='l'&&c!='b'&&c!='a') 
		{
			c=getch();
		}
	}
	else if(user_type==2)//用户时合法输入字符 
	{
		while(c!=27&&c!='n'&&c!='l'&&c!='b') 
		{
			c=getch();
		}
	}
	switch(c)
	{
	case 27:
	{
		if(user_type==1)
		{
			booksave();
		} 
		allflag=0;
	};break;
	case 'm':change(1);break;
	case 'n':visitall();break;
	case 'k':phead=creat(3,0,1,phead);break;
	case 'c':deletebook(1);break;
	case 's':booksave();break;
	case 'l':change(2);break;
	case 'b':change(3);break;
	case 'a':deletebook(2);break;
	}
}
int login()//登陆函数 
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
		printf("账号:   请输入账号/昵称");
		gotoxy(4,8);
		printf("密码:   请输入密码");
		paintrectangle(9,4,26,1);
		paintrectangle(9,7,26,1);
		paintrectangle(0,0,40,15);
		gotoxy(12,5);
		Sleep(1000);
		printf("                         ");
		cuowu(12,5,0,user_name);
		gotoxy(12,8);
		shuru_key(12,8,user_key);
		fflush(stdin); 
		while(success_flag==0)
		{
			allflag=ask_for(4,11,8);
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
				printf("信息错误，请重新输入！");
				gotoxy(12,5);
				Sleep(1000);
				printf("                         ");
				cuowu(12,5,0,user_name);
				gotoxy(12,8);
				shuru_key(12,8,user_key);
				fflush(stdin);
				success++; 
			}
			if(success>=3)//多次错误系统自动退出 
			{
				gotoxy(4,13);
				printf("多次错误，拜拜！");
				allflag=0; 
				break;
			}
		} 
		if(success<3&&success_flag!=0)//通过后执行下一步操作，打印昵称到全局昵称 
		{
			if(userclass==1)
			{
				sprintf(flag_name,"%s管理员",username);	
				return 1;		
			}
			else
			{
				sprintf(flag_name,"%s同学",username);
				return 2;
			} 
		}
		else
		{
			return 0;
		}
		fclose(fuser);
	} 
	
}
void number(char numberstr[])//产生随机账号 
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
void sign()//注册 
{
	char user_name[20];
	int userclass=2,success_flag=0,success=0;
	char user_key[20];
	char userkey[20];
	char usernumber[20];
	FILE *fuser;
	fuser=fopen(key_store,"at+");
	gotoxy(4,5);
	printf("昵称:   请输入中文或英文");
	gotoxy(4,8);
	printf("密码:   请输入密码");
	gotoxy(4,11);
	printf("确认:   请再次输入密码"); 
	paintrectangle(9,4,26,1);
	paintrectangle(9,7,26,1);
	paintrectangle(9,10,26,1); 
	paintrectangle(0,0,40,21);
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
		printf("密码不一致！");//密码不一致重新返回密码设定环节 
		Sleep(1000);
		gotoxy(12,11);
		printf("               ");
		shuru_key(12,8,user_key);
		fflush(stdin); 
		shuru_key(12,11,userkey);
		fflush(stdin);
	}
	if(ask_for(4,14,10))//管理员注册要求管理员内码 
	{
		while(1)
		{
			gotoxy(4,16);
			printf("内码：  请输入管理员内码！");
			shuru_key(12,16,userkey);
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
		gotoxy(4,20);
		printf("账号为：%s,请记好！",usernumber);
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
	char ch;
	int i=83,j=21;
	int flagtype;
	FILE *fuser;
	fuser=fopen(key_store,"rt");
	if(fuser==NULL)
	{
		fclose(fuser);
		fuser=fopen(key_store,"wt");
		fclose(fuser);
	}
	while(allflag)//外部登陆验证部分 
	{
		system("cls");
		gotoxy(24,7);
		printf("*******<1>登录*******");
		gotoxy(24,9);
		printf("*******<2>注册*******");
		gotoxy(24,11);
		printf("*******<3>退出*******");
		paintrectangle(22,5,20,9);
		gotoxy(33,13);
		ch=getchar();
		while(ch!='1'&&ch!='2'&&ch!='3')
		{
			gotoxy(33,13);
			ch=getchar();
		}
		switch(ch)
		{
		case '1':
			{
				system("cls");
				user_type=login();
				if(user_type!=0)
				{
					system("cls");
					allflag=1;
					phead=read();
					while(allflag)//执行主程序 
					{
						paint_ps();
						try_to_do();
						if(user_type==2)
						{
							i=83;
							j=11;
						}
						gotoxy(i,j);
						getch();
						system("cls");
					}
				}
			}break;
		case '2':system("cls");sign();break;
		case '3':allflag=0;break;
		}
	}
} 
