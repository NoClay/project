#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<windows.h>
#include<io.h>
#include<fcntl.h>
void gotoxy(int x, int y);//�ƶ�����λ�� 
void booksave();//����ͼ�鵽�̶����ļ� 
void cuowu(int i, int j,char str[]); //����Ϸ����ַ��� 
void allsort();//���������� ������Ϊ���ݽ������� 
void visitall();//������Ŀ 
int compare(char str[],struct book *key);//ģ���Ա����� 
int ask_for(int i,int j,int type);//ѯ���Ƿ����������һ������ Y����1  n����0 
void deletebook(int type);//ɾ��ͼ�� 
int output(int i,int j,int k);//�������ͼ��������� 
void shuru_key(int i,int j,char keystr[]);//��������ĺ��� 
void try_to_do();//�����жϺ��� 
void change(int type_key);//1��ʾ�޸ģ�2 ��ʾ��� 3��ʾ�黹 
void paintrectangle(int i,int j,int a,int b);//���ַ��Գ�һ�����ο� 
void paint_ps();//��ʾ�˵�  �û��͹���Ա�˵������ 
void sign();//ע���˻� 
int login();//��½���� 
void number(char numberstr[]);//�������8λ�˺� 
int book_num=0;//ȫ�ֱ�����ʾ���ݿ���Ŀ�� 
int allflag=1;//ȫ��ִ�б���1Ϊ������ִ�У�0Ϊ�˳� 
char key_store[60]="f:/��¼��Ϣ.txt";//��¼��Ϣ�����λ�� 
int user_type;//��½�û��ĵȼ� 
char keyin[20]="826611389";//����Ա�ĺ������룬ע��ʱʹ�� 
char flag_name[30];//ȫ���û��ǳ� 
char strok[4]="��";
char strno[4]="��";
struct book//�����鼮�ṹ�� 
{
	struct book *last;
	char number[20];//��� 
	char name[50];//���� 
	char author[20];//���� 
	char kind[20];//��� 
	char adress[30];//������ 
	char price[10];//�۸� 
	char type[4];//�Ƿ��ڿ� 
	char lendtime[20];//���ʱ�� 
	char backtime[20];//�黹ʱ�� 
	struct book *next;
};
struct book *phead;
struct book *read()//��ȡ���ݿ���Ϣ��������Ŀ 
{
	FILE *fbook;
	struct book *pend;
	long count=0;
	long size;
	long last=75;
	fbook=fopen("f:/ͼ�����.txt","rt");
	if(fbook==NULL)//���û�и��ļ����������ļ� ��������ж�ȡ 
	{
		fclose(fbook);
		fbook=fopen("f:/ͼ�����.txt","wt");
		fprintf(fbook,"���\t����\t����\t���\t������\t�۸�\t�Ƿ��ڿ� ���ʱ��\t�黹ʱ��\t��ǰ��������ݣ�%d\n",0);
		fclose(fbook);
		fbook=fopen("f:/ͼ�����.txt","rt");	
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
void booksave()//�ѳ��������ݱ��浽�ļ��� 
{
	FILE *fbook;
	struct book *temp=phead;
	fbook=fopen("f:/ͼ�����.txt","wt");
	fprintf(fbook,"���\t����\t����\t���\t������\t�۸�\t�Ƿ��ڿ� ���ʱ��\t�黹ʱ��\t��ǰ��������ݣ�%d\n",book_num);
	while(temp!=NULL)
	{
		fprintf(fbook,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",temp->number,temp->name,temp->author,temp->kind,temp->adress,temp->price,temp->type,temp->lendtime,temp->backtime);
		temp=temp->next; 
	}
	gotoxy(0,3);
	printf("����ɹ�!");
	fclose(fbook);
}
void cuowu(int i, int j,int type,char str[])//�ں��ʺϷ������ַ���//i,j��ʾ���Ķ�λ//type��ʾ��������� 
{
	char str1[40];
	fflush(stdin);
	if(type==0)//����0��ʾ�ַ�����û��ֵ������س���귵�ؼ���ִ������ 
	{
		gotoxy(i,j);	
		gets(str1);
		while (str1[0] == 13 || str1[0] == 10 || str1[0] == 0)
		{
			gotoxy(i, j);
			gets(str1);
			fflush(stdin);
		}
		sprintf(str,"%s",str1);//���Ϸ��ַ�����ӡ��Ŀ���ַ��� 
	}
	else//����Ϊ1��ʾĿ���ַ�����ֵ���س����������룬������һ�� 
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
struct book *creat(int j,int k,int type,struct book *goost)//ͷ�巨//i,j��λ���//typeΪ����//1Ϊ����//2Ϊ�޸�//3Ϊ��� 
{
	struct book *pnew;
	time_t timep; 
	struct tm *p; 
	int howtype=0;//������������ͱ��� 
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
			sprintf(pnew->lendtime,"%4d.%2d.%2d",(1900+p->tm_year), (1+p->tm_mon),p->tm_mday);//��ȡ�������ڣ���Ϊ�������� 
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
			cuowu(k+25,j-2,howtype, pnew->lendtime);
			cuowu(k+25,j-1,howtype, pnew->backtime);
		}
	}
	else
	{
		sprintf(pnew->lendtime,"0000.00.00");
		sprintf(pnew->backtime,"0000.00.00");
	}
	allsort();//�������� 
	return phead;
}
void gotoxy(int x, int y)//��궨λ���� 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void paintrectangle(int i,int j,int a,int b)//����һ�����ο� 
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
void paint_ps()
{
	int j;
	int i=70;
	int k=5;
	int weitiao[4]={0,0,0,0}; 
	gotoxy(15,1);
	printf("��ӭ%sʹ��ͼ�����ϵͳ��",flag_name);
	gotoxy(0,2);
	printf("***************************************************************"); 
	if(user_type==1)
	{
		paintrectangle(i-4,k-2,16,19); 
	}
	else 
	{
		paintrectangle(i-4,k-2,16,10);//�û�����˵��� 
		weitiao[0]=-2;//�������� 
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
	if(user_type==1)
	{
		gotoxy(i,k+12);
		printf("��s������ͼ��");
		gotoxy(i,k+14);
		printf("��a��ȫ��ɾ��");
	}
	gotoxy(i,k+16+weitiao[2]);
	printf("��esc�˳�ʹ��");  
}
int output(int i,int j,int k)
{
	struct book *temp=phead;
	int cj=0;
	int bk_num=1;
	while(bk_num!=k)//�������̶����鼮 ִ����� 
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
	return j;//���ع���е�λ��		
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
int ask_for(int i,int j,int type)//Ѱ��ִ�в��� //i,j��λ���//type��ʾִ��Ѱ��ʱ������ʾ��Ϣ������ 
{
	char ch;
	gotoxy(i,j);
	char todo[40];
	char sort[20][30]={"������ѯ","ɾ����Ϣ","����ɾ��","�����޸�","�޸���Ϣ","������Ϣ","ȫ��ɾ��","��¼","ע��","Ϊ����Ա","��������","��������"};
	sprintf(todo,"�Ƿ�%s��Y/N?",sort[type-1]);
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
		printf("��������Ϣ��");
		cuowu(12,3,0,str);
		while(temp!=NULL)
		{
			bk_num++;
			if(compare(str,temp)==1)//ģ���ж����� 
			{
				success_flag++;//���������־ 
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
			printf("�������,���޴��飡");
			flag=ask_for(0,6,1);
		}
		else
		{
			flag=ask_for(0,j,1);	
		}
		if(flag==1)//������ѯ�ָ� 
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
	for(i=0;i<sizenumber-size+1;i++)//����Ž���ģ���ж� 
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
	for(i=0;i<sizename-size+1;i++)//����������ģ���ж� 
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
	for(i=0;i<sizekind-size+1;i++)//���������ģ���ж� 
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
	for(i=0;i<sizeadress-size+1;i++)//�Գ��������ģ���ж� 
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
	for(i=0;i<sizeauthor-size+1;i++)//�����߽���ģ���ж� 
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
void deletebook(int type)//ɾ��ͼ��//type��ʾɾ������//1Ϊ����ɾ��//2Ϊȫ��ɾ�� 
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
				gotoxy(0,4);
				printf("�������,���޴��飡");
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
		flag=ask_for(i,j++,7);//��������ִ���жϣ���ֹ��ɾ�ļ� 
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
					printf("ɾ���ɹ�����ǰ���ݿ������ݣ�");
				}
				else
				{
					gotoxy(0,j);
					printf("δɾ��ȫ�����ݣ�");
				}
				flag=0;
			}
			else
			{
				gotoxy(0,j);
				printf("δɾ��ȫ�����ݣ�");
			}
		}
		else
		{
			gotoxy(0,j);
			printf("δɾ��ȫ�����ݣ�");
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
		if(ch==13&&count>=i+6)//���� 6λ����������س����˳���������//����ִ�� 
		{
			k=20;
		}
		else if(ch==8&&count>i)//��ɾ����ɾ�������һλ���� 
		{
			if(count<=i+16)
			{
				printf("\b \b");
			}
			count--;
		}
		else if(ch!=8&&ch!=13&&count<=i+16)//��������λ��ֹͣ���� 
		{
			keystore1[count-i]=ch;
			printf("*");
			count++;
		}
	}
	sprintf(keystr,"%s",keystore1);
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
			j++;
			gotoxy(i,j);
			printf("������󣬲��޴���!");
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
				phead=creat(j,i,2,temp);//����ǰ�߸��Ϲ��ܺ����޸� 
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
					printf("�Բ��𣬸����ѱ�������黹ʱ��:%s",temp->backtime);
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
void try_to_do()//�˵����ж�ִ�� 
{
	char c;
	c=getch();
	if(user_type==1)//����Աʱ�Ϸ������ַ� 
	{
		while(c!=27&&c!='m'&&c!='n'&&c!='c'&&c!='k'&&c!='s'&&c!='l'&&c!='b'&&c!='a') 
		{
			c=getch();
		}
	}
	else if(user_type==2)//�û�ʱ�Ϸ������ַ� 
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
int login()//��½���� 
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
		printf("�˺�:   �������˺�/�ǳ�");
		gotoxy(4,8);
		printf("����:   ����������");
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
			if(success>=3)//��δ���ϵͳ�Զ��˳� 
			{
				gotoxy(4,13);
				printf("��δ��󣬰ݰݣ�");
				allflag=0; 
				break;
			}
		} 
		if(success<3&&success_flag!=0)//ͨ����ִ����һ����������ӡ�ǳƵ�ȫ���ǳ� 
		{
			if(userclass==1)
			{
				sprintf(flag_name,"%s����Ա",username);	
				return 1;		
			}
			else
			{
				sprintf(flag_name,"%sͬѧ",username);
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
void number(char numberstr[])//��������˺� 
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
void sign()//ע�� 
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
		printf("���벻һ�£�");//���벻һ�����·��������趨���� 
		Sleep(1000);
		gotoxy(12,11);
		printf("               ");
		shuru_key(12,8,user_key);
		fflush(stdin); 
		shuru_key(12,11,userkey);
		fflush(stdin);
	}
	if(ask_for(4,14,10))//����Աע��Ҫ�����Ա���� 
	{
		while(1)
		{
			gotoxy(4,16);
			printf("���룺  ���������Ա���룡");
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
		printf("�˺�Ϊ��%s,��Ǻã�",usernumber);
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
	while(allflag)//�ⲿ��½��֤���� 
	{
		system("cls");
		gotoxy(24,7);
		printf("*******<1>��¼*******");
		gotoxy(24,9);
		printf("*******<2>ע��*******");
		gotoxy(24,11);
		printf("*******<3>�˳�*******");
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
					while(allflag)//ִ�������� 
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
