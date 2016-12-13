#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <graphics.h>
#define wh 15
#define HEIGHT 31
#define WIDTH 25
#define WALL 1
#define ROAD 0
#define START 2
#define END 3
#define ESC 5
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
typedef struct 
{
	int x;
	int y;
}InitParam;
InitParam mazesize;
InitParam start;
InitParam end;
InitParam minpixel;
InitParam maxpixel;
InitParam maxscar;
char StroreStr[50]="F:/Դ����/������ģ�����/ͼƬ/";
char Guide[4][20]={"�������Թ�","������Թ�","��ʼ������","�Ƴ�ģ����"};
int **map;
int CheckChar(char ch);/*�ж�һ���ַ��Ƿ�Ϊ�����ַ�*/
InitParam AnalyzeParam(char str[]);/*�����ַ�������ȡ�Թ��Ĵ�С*/
void AskForSize();/*ѯ���Թ��Ĵ�С*/
void create_maze(int x,int y);
void paint_maze();
void paint_box(int x1,int y1,int x2,int y2,int type);
int CheckChar(char ch)/*�ж�һ���ַ��Ƿ�Ϊ�����ַ�*/
{
	char str[2];
	int i;
	for(i=0;i<10;i++)
	{
		sprintf(str,"%d",i);
		if(str[0]==ch)
		{
			return i;
		}
	}
	return -1;
}
InitParam AnalyzeParam(char str[])/*�����ַ�������ȡ�����Ĵ�С*/
{
	InitParam param;
	int i=strlen(str)-1;
	int key=1;
	param.x=0;
	param.y=0;
	for(;CheckChar(str[i])>-1;i--)
	{
		param.y+=(CheckChar(str[i]))*key;
		key*=10;	
	}
	for(;CheckChar(str[i])==-1;i--)
	key=1;
	for(;i>=0;i--)
	{
		param.x+=(CheckChar(str[i]))*key;
		key*=10;
	}
	return param;
}
void AskForStore()
{
	int i;
	map=(int**)malloc(mazesize.x*sizeof(int*));
	for(i=0;i<mazesize.x;i++)
	{
		map[i]=(int*)malloc(mazesize.y*sizeof(int));
	}
}
void AskForSize()/*ѯ���Թ��Ĵ�С,������ֹ��*/
{
	char DefaultSize[20]="31,25";
	char NowSize[20];
	InputBox(NowSize,sizeof(NowSize),"�����������Թ��Ŀ�ߣ�","���ɾ����Թ�",DefaultSize,100,50,1);
	if(strcmp(NowSize,DefaultSize)==0)
	{
		mazesize.y=25;
		mazesize.x=31;
	}
	else
	{
		mazesize=AnalyzeParam(NowSize);
	}
	AskForStore();
	sprintf(DefaultSize,"%s","0,0");
	InputBox(NowSize,sizeof(NowSize),"�����������ĳ�ʼλ�ã�","���ɾ����Թ�",DefaultSize,100,50,1);
	if(strcmp(NowSize,DefaultSize)==0)
	{
		start.y=0;
		start.x=0;
	}
	else
	{
		start=AnalyzeParam(NowSize);
	}
	sprintf(DefaultSize,"%s","30,24");
	InputBox(NowSize,sizeof(NowSize),"��������������ֹλ�ã�","���ɾ����Թ�",DefaultSize,100,50,1);
	if(strcmp(NowSize,DefaultSize)==0)
	{
		end.y=24;
		end.x=20;
	}
	else
	{
		end=AnalyzeParam(NowSize);
	}
}
/*void create_maze(int x,int y)
{
    int c[4][2]={0,1,1,0,0,-1,-1,0};
    int i,j,t;
    for(i=0;i<4;i++)
    {
        j=rand()%4;
        t=c[i][0];c[i][0]=c[j][0];c[j][0]=t;
        t=c[i][1];c[i][1]=c[j][1];c[j][1]=t;
    }
    map[x][y]=ROAD;
    for(i=0;i<4;i++)
        if(map[x+2*c[i][0]][y+2*c[i][1]]==WALL)
        {
            map[x+c[i][0]][y+c[i][1]]=ROAD;
            create_maze(x+2*c[i][0],y+2*c[i][1]);
        }
}
void CreateMaze(int type)
{
	switch(type)
	{
	case 1:create_maze();
	}
}*/
InitParam CountPixel(int x,int y)/*����ĳһ������Ͻǵ�����λ��*/
{
	InitParam pixel;
	pixel.x=(x-1)*wh;
	pixel.y=(y-1)*wh;
	return pixel;
}
void PaintRectangle(int x1, int y1, int x2, int y2, int type)//�������飬��Ϊ�򿪺�Ϊ�򿪵�����
{
	setlinecolor(WHITE);
	rectangle(x1,y1,x2,y2);
	switch(type)
	{
	case 1:setfillcolor(WHITE);break;
	case 0:setfillcolor(BLACK);break;
	}
	floodfill((x1+x2)/2,(y1+y2)/2,WHITE);
}
void PaintBox(int x1, int y1, int x2, int y2, int type)//�������飬��Ϊ�򿪺�Ϊ�򿪵�����
{
	setcolor(WHITE);
	rectangle(x1, y1, x2, y2);
	setlinestyle(PS_SOLID, 1);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	if (type == 1)
	{
		setcolor(WHITE);
	}
	else if (type == 2)
	{
		setcolor(DARKGRAY);
	}
	line(x1, y1, x2, y1);
	line(x1, y1 + 1, x2, y1 + 1);
	line(x1, y1, x1, y2);
	line(x1 + 1, y1 + 1, x1 + 1, y2);
	if (type == 1)
	{
		setcolor(DARKGRAY);
	}
	else if (type == 2)
	{
		setcolor(WHITE);
	}
	line(x2, y1, x2, y2);
	line(x2 - 1, y1 + 1, x2 - 1, y2);
	line(x1, y2, x2, y2);
	line(x1 + 1, y2 - 1, x2 - 1, y2 - 1);
}
void InitSystem()
{
	int i;
	initgraph(640,480);
	loadimage(NULL,"F:/Դ����/������ģ�����/ͼƬ/system1.jpg",640,480,1);
	loadimage(NULL,"F:/Դ����/������ģ�����/ͼƬ/0.png",640,480,1);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	settextstyle(15,9,"����");
	setwritemode(R2_MERGEPEN);
	for(i=0;i<4;i++)
	{
		outtextxy(130+i*100,330,Guide[i]);
	}
	getch();
	AskForSize();
	maxscar.x=wh*(mazesize.x+4);
	maxscar.y=wh*(mazesize.y+4);
	initgraph(maxscar.x,maxscar.y);
	getch();
	closegraph();
}
int main()
{
	InitSystem();
	return 0;
}