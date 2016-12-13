#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<windows.h>
#include<io.h>
#include<fcntl.h>
void gotoxy(int x, int y);
void booksave();
void cuowu(int i, int j,char str[]); 
void allsort();
void visitall(int type);
int compare(char str[],struct book *key);
int ask_for(int i,int j,int type);
void deletebook(int type);
int output(int i,int j,int k);
void try_to_do(int type);
void changebook();
void paintrectangle(int i,int j,int a,int b);
int book_num=0;
int allflag=1;
char key_store[60]="f:/��Ŀ����/ͼ�����ϵͳ/��¼��Ϣ.txt";
char flag_name[30]="�庮";
char strok[4]="��";
char strno[4]="��";
struct book
{
	struct book *last;
	char number[20];
	char name[50];
	char author[20];
	char kind[20];
	char adress[20];
	char price[10];
	char type[4];
	char lendtime[12];
	char backtime[12];
	struct book *next;
};
struct book *phead;
struct book *read()
{
	FILE *fbook;
	struct book *pend;
	long count=0;
	long size;
	long last=75;
	fbook=fopen("f:/��Ŀ����/ͼ�����ϵͳ/ͼ�����.txt","rt");
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
void booksave()
{
	FILE *fbook;
	struct book *temp=phead;
	fbook=fopen("f:/��Ŀ����/ͼ�����ϵͳ/ͼ�����.txt","wt");
	fprintf(fbook,"���\t����\t����\t���\t������\t�۸�\t�Ƿ��ڿ� ���ʱ��\t�黹ʱ��\t��ǰ��������ݣ�%d\n",book_num);
	while(temp!=NULL)
	{
		fprintf(fbook,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",temp->number,temp->name,temp->author,temp->kind,temp->adress,temp->price,temp->type,temp->lendtime,temp->backtime);
		temp=temp->next; 
	}
	fclose(fbook);
}
void cuowu(int i, int j,int type,char str[])
{
	char str1[40];
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
struct book *creat(int j,int k,int type,struct book *goost)//ͷ�巨
{
	struct book *pnew;
	time_t timep; 
	struct tm *p; 
	int howtype=0;
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
		printf("��ţ�");
		gotoxy(k,j++);
		printf("������");
		gotoxy(k,j++);
		printf("���ߣ�"); 
		gotoxy(k,j++);
		printf("���");
		gotoxy(k,j++);
		printf("�����磺");
		gotoxy(k,j++);
		printf("�۸�");
		gotoxy(k,j++);
		printf("�Ƿ��������ڿ�Ϊ�ǣ����Ϊ�񣩣�");
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
	}
	if(strcmp(pnew->type,strno)==0)
	{
		if(type==3)
		{
			time(&timep); 
			p=localtime(&timep); 
			sprintf(pnew->lendtime,"%4d.%2d.%2d",(1900+p->tm_year), (1+p->tm_mon),p->tm_mday);
			gotoxy(k, j-2);
			printf("���ʱ��(����2015.06.02):%s",pnew->lendtime);
			gotoxy(k, j-1);
			printf("�黹ʱ��(����2015.06.02):");
			cuowu(k+25,j-1,1, pnew->backtime);
		}
		else
		{
					gotoxy(k, j++);
		printf("���ʱ��(����2015.06.02):");
		gotoxy(k, j++);
		printf("�黹ʱ��(����2015.06.02):");
		cuowu(k+28,j-2,howtype, pnew->lendtime);
		cuowu(k+28,j-1,howtype, pnew->backtime);
		}
	}
	else
	{
		sprintf(pnew->lendtime,"0000.00.00");
		sprintf(pnew->backtime,"0000.00.00");
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
void paint_ps(int type)
{
	int j;
	int i=70;
	int k=5;
	int weitiao[4]={0,0,0,0}; 
	gotoxy(15,1);
	printf("��ӭ%sʹ��ͼ�����ϵͳ��",flag_name);
	gotoxy(0,2);
	printf("***************************************************************"); 
	if(type==1)
	{
		paintrectangle(i-4,k-2,16,19); 
	}
	else 
	{
		paintrectangle(i-4,k-2,16,10);
		weitiao[0]=-2;
		weitiao[1]=-6;
		weitiao[2]=-10;
	}
	gotoxy(i,k);
	printf("��k������ͼ��");
	gotoxy(i,k+2+weitiao[0]);
	printf("��n����ѯͼ��");
	gotoxy(i,k+4);
	printf("��m���޸�ͼ��");
	gotoxy(i,k+6);
	printf("��c��ɾ��ͼ��");
	gotoxy(i,k+8+weitiao[1]);
	printf("��l�����ͼ��");
	gotoxy(i,k+10+weitiao[1]);
	printf("��b���黹ͼ��");
	gotoxy(i,k+12);
	printf("��s������ͼ��");
	gotoxy(i,k+14);
	printf("��a��ȫ��ɾ��");
	gotoxy(i,k+16+weitiao[2]);
	printf("��esc�˳�ʹ��");  
}
int output(int i,int j,int k)
{
	struct book *temp=phead;
	int cj=0;
	int bk_num=1;
	while(bk_num!=k)
	{
		bk_num++;
		temp=temp->next;
	}
	gotoxy(i,j);
	printf("��ţ�%s",temp->number);
	j++;
	gotoxy(i,j);
	printf("������%s",temp->name);
	j++;
	gotoxy(i,j);
	printf("���ߣ�%s",temp->author);
	j++;
	gotoxy(i,j);
	printf("���%s",temp->kind);
	j++;
	gotoxy(i,j);
	printf("�����磺%s",temp->adress);
	j++;
	gotoxy(i,j);
	printf("�۸�%s",temp->price);
	j++;;
	gotoxy(i,j);
	printf("�Ƿ��������ڿ�Ϊ�ǣ����Ϊ�񣩣�%s",temp->type);
	j++;
	if(strcmp(temp->type,strno)==0)
	{
		gotoxy(i,j);
		printf("���ʱ��(����2015.06.02):%s",temp->lendtime);
		j++;
		gotoxy(i,j);
		printf("�黹ʱ��(����2015.06.02):%s",temp->backtime);
		j++;
	}
	return j;		
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
void visitall(int type)
{
	int flag=1;
	int bk_num=0,i=0,j=5,pass;
	char str[40];
	int success_flag=0;
	struct book *temp=phead;
	while(flag)
	{	
		gotoxy(0,3);
		printf("��������Ϣ��");
		cuowu(12,3,0,str);
		while(temp!=NULL)
		{
			bk_num++;
			if(compare(str,temp)==1)
			{
				success_flag++;
				pass=output(i,j,bk_num);
				j=pass;
			}
			temp=temp->next;		
		}
		gotoxy(0,4);
		printf("��%d�����������",success_flag);
		if(success_flag==0) 
		{
			gotoxy(0,5);
			printf("�������,���޴��ˣ�");
			flag=ask_for(0,6,1);
		}
		else
		{
			flag=ask_for(0,j,1);	
		}
		if(flag==1)
		{
			success_flag=0;
			system("cls");
			paint_ps(type);
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
	for(i=0;i<sizenumber-size+1;i++)
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
	for(i=0;i<sizename-size+1;i++)
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
	for(i=0;i<sizekind-size+1;i++)
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
	for(i=0;i<sizeadress-size+1;i++)
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
	for(i=0;i<sizeauthor-size+1;i++)
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
void deletebook(int type)
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
			printf("�����������Ż�������");
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
				gotoxy(0,5);
				printf("�������,���޴��飡");
				flag=ask_for(0,6,3);
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
				system("cls");
				paint_ps(1);
			}
		}
	}
	else if(type==2)
	{
		flag=ask_for(i,j++,7);
		if(flag==1)
		{
			flag=ask_for(i,j++,7);
			if(flag==1)
			{
				flag=ask_for(i,j,7);
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
				}
				flag=0;
			}
		}	
	}
}
void change(int type_key)//1��ʾ�޸ģ�2 ��ʾ��� 3��ʾ�黹 
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
		printf("�����������Ż�������");
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
			gotoxy(i,j);
			j++;
			printf("������󣬲��޴���!");
		}
		else
		{
			if(type_key==1)
			{
				j=output(i,j,bk_num);
				phead=creat(j,i,2,temp);
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
					printf("�Բ��𣬸����ѱ�������黹ʱ��:%s",temp->backtime);
				}	
			}
			else if(type_key==3)
			{
				sprintf(temp->type,"%s",strok);
				sprintf(temp->lendtime,"0000.00.00");
				sprintf(temp->backtime,"0000.00.00");
				j=output(i,j,bk_num);				
			}
		}
		flag=ask_for(i,j,4);
	}
}
void try_to_do(int type)
{
	char c;
	c=getch();
	if(type==1)
	{
		while(c!=27&&c!='m'&&c!='n'&&c!='c'&&c!='k'&&c!='s'&&c!='l'&&c!='b'&&c!='a') 
		{
			c=getch();
		}
	}
	else if(type==2)
	{
		while(c!=27&&c!='n'&&c!='l'&&c!='b') 
		{
			c=getch();
		}
	}
	switch(c)
	{
	case 27:booksave();allflag=0;break;
	case 'm':change(1);break;
	case 'n':visitall(type);break;
	case 'k':phead=creat(3,0,1,phead);break;
	case 'c':deletebook(1);break;
	case 's':booksave();break;
	case 'l':change(2);break;
	case 'b':change(3);break;
	case 'a':deletebook(2);break;
	}
}
int main()
{
	allflag=1;
	phead=read();
	while(allflag)
	{
		paint_ps(1);
		try_to_do(1);
		gotoxy(83,21);
		getch();
		system("cls");
	}
} 
