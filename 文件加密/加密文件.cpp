#include<stdio.h>
#include<stdlib.h>
#include<io.h>
#include<fcntl.h>
#include<windows.h>
#include<string.h>
void lock_file(int type);
void lockit(char str[],int type);
int ask_for(int i,int type);
int check(char str_key[]);
int lock=1,unlock=2;
void lock_file(int type)
{
	FILE *f_lock;
	long int adress;
	char str[60];
	char str_key[60];
	int count;
	if(type==1)
	{
		printf("������Ҫ���ܵ��ļ���·�����ļ���������f:/ͨѶ¼.txt)\n");
	}
	else if(type==2)
	{
		printf("������Ҫ���ܵ��ļ���·�����ļ���������f:/ͨѶ¼.txt)\n");
	}
	fflush(stdin);
	gets(str_key);	
	adress=check(str_key);
	f_lock=fopen("f:/Դ����/�ļ�����/��������.txt","rt+");
	if(adress>=0)
	{
		fseek(f_lock,adress,0);
		fscanf(f_lock," %s %d",str,&count);
		if(type==1)
		{
			if(ask_for(count,lock))
			{
				lockit(str_key,lock);
				fseek(f_lock,adress,0);
				fprintf(f_lock,"\n\t%s\t%d\n",str_key,count+1);
			}
		}
		else if(type==2)
		{
			if(ask_for(count,unlock))
			{
				lockit(str_key,unlock);
				fseek(f_lock,adress,0);
				fprintf(f_lock,"\n\t%s\t%d\n",str_key,count-1);
			}
		}	
	}
	if(adress<0&&type==1)
	{
		if(ask_for(0,1))
		{
			lockit(str_key,lock);
			rewind(f_lock);
			fseek(f_lock,(0-(adress+1)),0);
			fprintf(f_lock,"\t%s\t%d\n",str_key,1);
		}
	}
	fclose(f_lock);
}
void lockit(char str[],int type)
{
	FILE *fnow;
	char *strlock;
	char ch;
	int fno;
	long int fsize,i=0;
	fnow=fopen(str,"rt+");
	fno=fileno(fnow);
	fsize=filelength(fno);
	strlock=(char *)malloc(fsize*sizeof(char));
	while(!feof(fnow))
	{
		ch=fgetc(fnow);
		strlock[i]=65535-ch;
		i++;
	}
	rewind(fnow);
	for(i=0;i<fsize;i++)
	{
		fputc(strlock[i],fnow);
	}
	fclose(fnow);
}
int ask_for(int i,int type)
{
	char ch;
	if(type==1)
	{
		printf("���ļ�����%d�Σ��Ƿ�������ܣ�Y/N?",i);
	}
	else if(type==2)
	{
		printf("���ļ�����%d�Σ��Ƿ�������ܣ�Y/N?",i);
	}
	ch=getchar();
	while(ch!='y'&&ch!='Y'&&ch!='n'&&ch!='N')
	{ 
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
int check(char str_key[])
{
	char str[60];
	long int adress,f_size;
	int count,success=0,f_no;
	FILE *f_lock;
	f_lock=fopen("f:/Դ����/�ļ�����/��������.txt","rt");
	f_no=fileno(f_lock);
	f_size=filelength(f_no);
	while((ftell(f_lock)!=f_size)&&success==0)
	{
		adress=ftell(f_lock);
		fscanf(f_lock," %s %d",str,&count);
		if(strcmp(str,str_key)==0)
		{
			success=1;
		} 
	}
	if(success==0)
	{
		adress=-1-f_size;
	}
	return adress;
}
int main()
{
	char key_store[60]="f:/��Ŀ����/ͼ�����ϵͳ/ͨѶ¼.txt";
	lockit(key_store,1);
}
