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
char StroreStr[50]="F:/源代码/电脑鼠模拟程序/图片/";
char Guide[4][20]={"回字型迷宫","随机型迷宫","开始电脑鼠","推出模拟器"};
int **map;
int CheckChar(char ch);/*判断一个字符是否为数字字符*/
InitParam AnalyzeParam(char str[]);/*分析字符串，读取迷宫的大小*/
void AskForSize();/*询问迷宫的大小*/
void create_maze(int x,int y);
void paint_maze();
void paint_box(int x1,int y1,int x2,int y2,int type);
int CheckChar(char ch)/*判断一个字符是否为数字字符*/
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
InitParam AnalyzeParam(char str[])/*分析字符串，读取参数的大小*/
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
void AskForSize()/*询问迷宫的大小,起点和终止点*/
{
	char DefaultSize[20]="31,25";
	char NowSize[20];
	InputBox(NowSize,sizeof(NowSize),"请输入生成迷宫的宽高：","生成经典迷宫",DefaultSize,100,50,1);
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
	InputBox(NowSize,sizeof(NowSize),"请输入电脑鼠的初始位置：","生成经典迷宫",DefaultSize,100,50,1);
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
	InputBox(NowSize,sizeof(NowSize),"请输入电脑鼠的终止位置：","生成经典迷宫",DefaultSize,100,50,1);
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
InitParam CountPixel(int x,int y)/*计算某一点的左上角的像素位置*/
{
	InitParam pixel;
	pixel.x=(x-1)*wh;
	pixel.y=(y-1)*wh;
	return pixel;
}
void PaintRectangle(int x1, int y1, int x2, int y2, int type)//画出方块，分为打开和为打开的两种
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
void PaintBox(int x1, int y1, int x2, int y2, int type)//画出方块，分为打开和为打开的两种
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
	loadimage(NULL,"F:/源代码/电脑鼠模拟程序/图片/system1.jpg",640,480,1);
	loadimage(NULL,"F:/源代码/电脑鼠模拟程序/图片/0.png",640,480,1);
	settextcolor(BLACK);
	setbkcolor(WHITE);
	settextstyle(15,9,"宋体");
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