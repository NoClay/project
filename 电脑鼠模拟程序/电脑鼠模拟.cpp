/*********************************************************************************************************
头文件包含
*********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <graphics.h>
#include <io.h>
/*********************************************************************************************************
常量宏定义
*********************************************************************************************************/
#define wh 30
#define WALL 1
#define ROAD 0
#define START 2
#define END 3
#define N 20
#define up 0
#define down 1
#define left 2
#define right 3
#define back 4
#define PI 3.1415926535
/*********************************************************************************************************
全局变量定义
*********************************************************************************************************/
typedef struct 
{
	int x;
	int y;
	int di;
}InitParam;
InitParam MinPixel;
InitParam MaxPixel;
InitParam MaxScar;
InitParam MinStage;
InitParam MaxStage;
int allflag;
typedef struct
{
	int di[4];
	int num;
}MazeState;
MazeState **map;
int MazeSize;
int MazeStart=0;
int MazeEnd;
typedef struct{
	InitParam* top;
	InitParam* base;
	int stacksize;
}stack;
stack s;
time_t t1,t2;
int  front;
/*********************************************************************************************************
函数声明
*********************************************************************************************************/
void InitSystem();/*初始化系统*/
void initstack();
void Push(int x,int y);
InitParam pop();
void SearchMaze();
void PaintBox(int x1, int y1, int x2, int y2, int type1,int type2);//画出方块，分为打开和未打开的两种
void PaintTip(int type);
void PaintLine(int x,int y,int dir,int type);
int CheckDo(int x,int y,int dir,int type);
void RotateCar(int i,int j,int dir );
void MoveCar(int i,int j,int dir,int type);
void CreateMaze();
void Update(int i,int j,int number);
void HelloWorld();
int CountTu(int x,int y);
void AskForSize();/*询问迷宫的大小,起点和终止点*/
void MouseCrontol(int type);
/*********************************************************************************************************
初始化栈
*********************************************************************************************************/
void initstack()
{
    s.base=(InitParam*)malloc(sizeof(MazeSize)*MazeSize*MazeSize);
    s.top=s.base;
    s.stacksize=MazeSize*MazeSize;
}

/*********************************************************************************************************
入栈
*********************************************************************************************************/
void Push(int x,int y,int dir)
{
	InitParam p;
	p.x=x;
	p.y=y;
	p.di=dir;
	*s.top++=p;
}
/*********************************************************************************************************
出栈
*********************************************************************************************************/
InitParam pop()
{
	return *(--s.top);
}
/*********************************************************************************************************
电脑鼠算法
*********************************************************************************************************/
void SearchMaze()
{
	int flag0=1;
	int i,j;
	int sum=1;
	long int number;
	MOUSEMSG m;	// 定义鼠标消息
	InitParam pixel;
	IMAGE image2,image1;
	loadimage(&image2,_T("c:/电脑鼠模拟程序/图片/car.jpg"));
	loadimage(&image1,_T("c:/电脑鼠模拟程序/图片/easer.jpg"));
	InitParam instead;	
	for(i=0;i<MazeSize-1;i++)
	{
		for(j=0;j<MazeSize-1;j++)
		{
			map[i][j].num=0;
		}
	}
	i=j=0;
	pixel.x=MinPixel.x+(j-1)*wh;
	pixel.y=MinPixel.y+(i-1)*wh;
	putimage(pixel.x+3,pixel.y+3,&image2);
	PaintTip(2);
	initstack();
	while(true)
	{
		// 获取一条鼠标消息
		if(MouseHit())
		{
			m = GetMouseMsg();
		}
		t2=time(NULL);
		number=t2-t1;
		Update(i,j,number);
		switch(m.uMsg)
		{
		case WM_MOUSEMOVE:
			break;
		case WM_LBUTTONDOWN:
			{
				i=CountTu(m.x,m.y);	
				if(i==0)
				{
					InitSystem();
				}
				else if(i==2)
				{
					flag0=0;
				}
				else if(i==3)
				{
					flag0=1;
				}
				else if(i==4)
				{
					allflag=0;
					return ;
				}
			};break;
		case WM_RBUTTONUP:break;
		}
		/*********************************************************************************************************
		电脑鼠搜索 
		*********************************************************************************************************/
		if((i!=MazeSize-1||j!=MazeSize-1)&&flag0)
		{
			if(map[i][j].di[up]==0&&map[i][j].num==0)
			{
				Push(i,j,up);
				map[i][j].num=sum;
				MoveCar(i,j,up,2);
				sum++;
				i--;
			}
			else if(map[i][j].di[right]==0&&map[i][j].num==0)
			{
				Push(i,j,right);
				map[i][j].num=sum;
				MoveCar(i,j,right,2);
				sum++;
				j++;
			}
			else if(map[i][j].di[left]==0&&map[i][j].num==0)
			{
				Push(i,j,left);
				map[i][j].num=sum;
				MoveCar(i,j,left,2);
				sum++;
				j--;
			}
			else if(map[i][j].di[down]==0&&map[i][j].num==0)
			{
				Push(i,j,down);
				map[i][j].num=sum;
				MoveCar(i,j,down,2);
				sum++;
				i++;
			}
			else
			{	
				pixel.x=MinPixel.x+(j-1)*wh;
				pixel.y=MinPixel.y+(i-1)*wh;
				putimage(pixel.x+3,pixel.y+3,&image2);
				instead=pop();
				i=instead.x;
				j=instead.y;
				pixel.x=MinPixel.x+(j-1)*wh;
				pixel.y=MinPixel.y+(i-1)*wh;
				putimage(pixel.x+3,pixel.y+3,&image2);
				sum--;
			} 
		}
	}
}
/*********************************************************************************************************
画出迷宫
*********************************************************************************************************/
void PaintBox(int x1, int y1, int x2, int y2, int type1,int type2)//画出方块，分为打开和未打开的两种
{
	if(type1==2)
	{
		setcolor(BLACK);
		rectangle(x1, y1, x2, y2);
		setfillstyle(SOLID_FILL);
		setfillcolor(BLACK);
		floodfill((x1+x2)/2,(y1+y2)/2,BLACK);
	}
	else if(type1==1)
	{
		setcolor(WHITE);
		rectangle(x1, y1, x2, y2);
		setlinestyle(PS_SOLID, 1);
		setfillstyle(SOLID_FILL, LIGHTGRAY);
	}
	if (type2 == 1)
	{
		setcolor(WHITE);
	}
	else if (type2 == 2)
	{
		setcolor(DARKGRAY);
	}
	line(x1, y1, x2, y1);
	line(x1, y1 + 1, x2, y1 + 1);
	line(x1, y1, x1, y2);
	line(x1 + 1, y1 + 1, x1 + 1, y2);
	if (type2 == 1)
	{
		setcolor(DARKGRAY);
	}
	else if (type2 == 2)
	{
		setcolor(WHITE);
	}
	line(x2, y1, x2, y2);
	line(x2 - 1, y1 + 1, x2 - 1, y2);
	line(x1, y2, x2, y2);
	line(x1 + 1, y2 - 1, x2 - 1, y2 - 1);
}
/*********************************************************************************************************
提示内容
*********************************************************************************************************/
void PaintTip(int type)
{
	int i=15;
	if(type==1)
	{	
		PaintBox(MaxStage.x+wh/2,MinStage.y,MaxScar.x-wh/2,MinStage.y+2*wh/2,1,1);
		PaintBox(MaxStage.x+wh/2,MinStage.y+3*wh/2,MaxScar.x-wh/2,MinStage.y+5*wh/2,1,1);
		PaintBox(MaxStage.x+wh/2,MinStage.y+6*wh/2,MaxScar.x-wh/2,MinStage.y+8*wh/2,1,1);	
		PaintBox(MaxStage.x+wh/2,MinStage.y+9*wh/2,MaxScar.x-wh/2,MinStage.y+11*wh/2,1,1);	
		PaintBox(MaxStage.x+wh/2,MinStage.y+12*wh/2,MaxScar.x-wh/2,MinStage.y+14*wh/2,1,1);	
		PaintBox(MaxStage.x+wh/2,MinStage.y+15*wh/2,MaxScar.x-wh/2,MinStage.y+31*wh/2,1,2);
		setbkcolor(LIGHTGRAY);
		settextcolor(BLACK);
		settextstyle(16, 0, _T("宋体"));
		outtextxy(MaxStage.x+wh+40,MinStage.y+7,_T("创建新迷宫"));
		outtextxy(MaxStage.x+wh+40,MinStage.y+7+3*wh/2,_T("开始电脑鼠"));
		outtextxy(MaxStage.x+wh+40,MinStage.y+7+6*wh/2,_T("暂停电脑鼠"));
		outtextxy(MaxStage.x+wh+40,MinStage.y+7+9*wh/2,_T("继续电脑鼠"));
		outtextxy(MaxStage.x+wh+40,MinStage.y+7+12*wh/2,_T("退出电脑鼠"));
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("移动向标："));i++;
		i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("按w键移动向标向上"));i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("按a键移动向标向左"));i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("按s键移动向标向下"));i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("按d键移动向标向右"));i++;
		i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("建造/拆除："));i++;
		i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("按i键上边建造/拆除"));i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("按j键左边建造/拆除"));i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("按k键下边建造/拆除"));i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("按l键右边建造/拆除"));i++;
		i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("按esc退出创建迷宫"));i++;
	}
	else
	{
		clearrectangle(MaxStage.x+wh/2,MinStage.y+15*wh/2,MaxScar.x-wh/2,MinStage.y+31*wh/2);
		PaintBox(MaxStage.x+wh/2,MinStage.y+15*wh/2,MaxScar.x-wh/2,MinStage.y+31*wh/2,1,2);
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("小车状态(1为障碍):"));i++;
		i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("上边:"));i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("下边:"));i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("左边:"));i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("右边:"));i++;
		i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("时间统计:"));i++;
		i++;
		outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("运行时间:"));i++;
		//	outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("遍历时间:"));i++;/*待拓展*/
		//	outtextxy(MaxStage.x+wh,MinStage.y+7+i*wh/2,_T("冲刺时间:"));i++;
	}
}
/*********************************************************************************************************
在某处一条线
*********************************************************************************************************/
void PaintLine(int x,int y,int dir,int type)
{
	int pixelx,pixely;
	pixelx=MinPixel.x+(y-1)*wh;
	pixely=MinPixel.y+(x-1)*wh;
	setlinestyle(PS_SOLID,3);
	if(type)
	{
		setlinecolor(RED);
	}
	else
	{
		setlinecolor(BLACK);
	}
	switch(dir)
	{
	case up:line(pixelx,pixely,pixelx+wh,pixely);break;
	case down:line(pixelx,pixely+wh,pixelx+wh,pixely+wh);break;
	case left:line(pixelx,pixely,pixelx,pixely+wh);break;
	case right:line(pixelx+wh,pixely,pixelx+wh,pixely+wh);break;
	};
}
/*********************************************************************************************************
判断操作是否合法
*********************************************************************************************************/
int CheckDo(int x,int y,int dir,int type)
{
	if(type==1)
	{
		if(dir==up&&x==0)	return 0;
		if(dir==down&&x==MazeSize-2)	return 0;
		if(dir==left&&y==0)	return 0;
		if(dir==right&&y==MazeSize-2)	return 0;
		return 1;
	}
	else 
	{
		if(dir==up&&x==0)	return 0;
		if(dir==down&&x==MazeSize-2)	return 0;
		if(dir==left&&y==0)	return 0;
		if(dir==right&&y==MazeSize-2)	return 0;
		return 1;
	}
}
/*********************************************************************************************************
小车转弯/*待拓展功能
*********************************************************************************************************/
void RotateCar(int i,int j,int dir )
{
	IMAGE img1,img2;
	InitParam pixel;
	pixel.x=MinPixel.x+(j-1)*wh;
	pixel.y=MinPixel.y+(i-1)*wh;
	getimage(&img1,pixel.x+3,pixel.y+3,20,20);
	switch(dir)
	{
	case right:rotateimage(&img2,&img1,PI / 2);putimage(pixel.x+3,pixel.y+3,&img2);break;
	case left:rotateimage(&img2,&img1,-PI / 2);putimage(pixel.x+3,pixel.y+3,&img2);break;
	case back:rotateimage(&img2,&img1,PI);putimage(pixel.x+3,pixel.y+3,&img2);break;
	}
}
/*********************************************************************************************************
移动小车
*********************************************************************************************************/
void MoveCar(int i,int j,int dir,int type)
{
	int ai=0,aj=0;
	int k;
	InitParam pixelto;
	pixelto.x=MinPixel.x+(j-1)*wh;
	pixelto.y=MinPixel.y+(i-1)*wh;
	IMAGE image,image1,image2;
	loadimage(&image,_T("c:/电脑鼠模拟程序/图片/dir.jpg"));
	loadimage(&image1,_T("c:/电脑鼠模拟程序/图片/eraser.jpg"));
	if(type==1)
	{
		putimage(pixelto.x+3,pixelto.y+3,&image1);   
		switch(dir)
		{
		case up:aj=-wh;break;
		case down:aj=wh;break;
		case left:ai=-wh;break;
		case right:ai=wh;break;
		};
		putimage(pixelto.x+ai+3,pixelto.y+aj+3,&image);
	}
	else
	{  
		switch(dir)
		{
		case up:
			{
				for(k=1;k<=30;k++)
				{
					getimage(&image2,pixelto.x+3,pixelto.y+4-k,20,20);
					putimage(pixelto.x+3,pixelto.y+4-k,&image1); 
					putimage(pixelto.x+3,pixelto.y+3-k,&image2);
					Sleep(50);
				}
			};break;
		case down:
			{
				for(k=1;k<=30;k++)
				{
					getimage(&image2,pixelto.x+3,pixelto.y+2+k,20,20);
					putimage(pixelto.x+3,pixelto.y+2+k,&image1); 
					putimage(pixelto.x+3,pixelto.y+k+3,&image2);
					Sleep(50);
				}
			};break;
		case left:
			{
				for(k=1;k<=30;k++)
				{
					getimage(&image2,pixelto.x+4-k,pixelto.y+3,20,20);
					putimage(pixelto.x+4-k,pixelto.y+3,&image1); 
					putimage(pixelto.x+3-k,pixelto.y+3,&image2);
					Sleep(50);
				}
			};break;
		case right:
			{
				for(k=1;k<=30;k++)
				{
					getimage(&image2,pixelto.x+2+k,pixelto.y+3,20,20);
					putimage(pixelto.x+2+k,pixelto.y+3,&image1); 
					putimage(pixelto.x+3+k,pixelto.y+3,&image2);
					Sleep(50);
				}
			};break;
		}
	}
}
/*********************************************************************************************************
创建迷宫
*********************************************************************************************************/
void CreateMaze()
{
	int i,j,k;
	IMAGE image,image1;
	InitParam pixel;
	char ch;
	loadimage(&image,_T("c:/电脑鼠模拟程序/图片/dir.jpg"));
	loadimage(&image1,_T("c:/电脑鼠模拟程序/图片/eraser.jpg"));
	for(i=0;i<MazeSize-1;i++)
	{
		for(j=0;j<MazeSize-1;j++)
		{
			for(k=0;k<4;k++)
			{
				map[i][j].di[k]=0;
			}
		}
	}
	for(i=0;i<MazeSize-1;i++)
	{
		map[i][0].di[left]=1;
		map[i][MazeSize-2].di[right]=1;
		PaintLine(i,0,left,map[i][0].di[left]);
		PaintLine(i,MazeSize-2,right,map[i][MazeSize-2].di[right]);
	}
	for(j=0;j<MazeSize-1;j++)
	{
		map[0][j].di[up]=1;
		map[MazeSize-2][j].di[down]=1;
		PaintLine(0,j,up,map[0][j].di[up]);
		PaintLine(MazeSize-2,j,down,map[MazeSize-2][j].di[down]);
	}
	map[0][0].di[right]=1;
	PaintLine(0,0,right,map[0][0].di[right]);
	map[MazeSize-2][MazeSize-2].di[left]=1;
	PaintLine(MazeSize-2,MazeSize-2,left,map[MazeSize-2][MazeSize-2].di[left]);
	i=0;j=0;
	pixel.x=MinPixel.x+(j-1)*wh;
	pixel.y=MinPixel.y+(i-1)*wh;
	putimage(pixel.x+3,pixel.y+3,&image);
	while(true)
	{
		flushall();
		ch=getch();
		if(ch=='w'||ch=='a'||ch=='s'||ch=='d'||ch=='j'||ch=='k'||ch=='l'||ch=='i')
		{
			switch(ch)
			{
			case 'w':{
				if(CheckDo(i,j,up,1))
				{
					MoveCar(i,j,up,1);
					i--;
				}			
					 };break;
			case 'a':{
				if(CheckDo(i,j,left,1))
				{
					MoveCar(i,j,left,1);
					j--;
				}			
					 };break;
			case 's':{
				if(CheckDo(i,j,down,1))
				{
					MoveCar(i,j,down,1);
					i++;
				}			
					 };break;
			case 'd':{
				if(CheckDo(i,j,right,1))
				{
					MoveCar(i,j,right,1);
					j++;
				}			
					 };break;
			case 'j':{
				if(CheckDo(i,j,left,2))
				{
					map[i][j].di[left]=(map[i][j].di[left]+1)%2;
					map[i][j-1].di[right]=(map[i][j-1].di[right])%2;
					PaintLine(i,j,left,map[i][j].di[left]);
				}			
					 };break;
			case 'k':{
				if(CheckDo(i,j,down,2))
				{
					map[i][j].di[down]=(map[i][j].di[down]+1)%2;
					map[i+1][j].di[up]=(map[i+1][j].di[down]+1)%2;
					PaintLine(i,j,down,map[i][j].di[down]);
				}			
					 };break;
			case 'i':{
				if(CheckDo(i,j,up,2))
				{
					map[i][j].di[up]=(map[i][j].di[up]+1)%2;
					map[i-1][j].di[down]=(map[i-1][j].di[down]+1)%2;
					PaintLine(i,j,up,map[i][j].di[up]);
				}			
					 };break;
			case 'l':{
				if(CheckDo(i,j,right,2))
				{
					map[i][j].di[right]=(map[i][j].di[right]+1)%2;
					map[i][j-1].di[left]=(map[i][j-1].di[left]+1)%2;
					PaintLine(i,j,right,map[i][j].di[right]);
				}			
					 };break;
			}
		}
		else if (ch==27)
		{
			return;
		}
	}
}
/*********************************************************************************************************
初始化系统
*********************************************************************************************************/
void InitSystem()
{
	FILE *fp=NULL;
	char str[60];
	int i,key;
	AskForSize();
	MinStage.x=5;
	MinStage.y=30;
	MaxStage.x=MinStage.x+(N+1)*wh;
	MaxStage.y=MinStage.y+(N+1)*wh;
	MaxScar.x=MaxStage.x+200;
	MaxScar.y=MaxStage.y+5;
	MinPixel.x=MinStage.x+(10-MazeSize/2+1)*wh;
	MinPixel.y=MinStage.y+(10-MazeSize/2+1)*wh;
	MaxPixel.x=MinPixel.x+(MazeSize-1)*wh;
	MaxPixel.y=MinPixel.y+(MazeSize-1)*wh;
	initgraph(MaxScar.x,MaxScar.y);
	setcolor(WHITE);
	rectangle(0, 0, MaxScar.x, MaxScar.y);//画出边框
	setfillstyle(SOLID_FILL);
	setfillcolor(LIGHTGRAY);
	floodfill(MaxScar.x/ 2, MaxScar.y / 2, WHITE);
	PaintBox(MinStage.x,MinStage.y,MaxStage.x,MaxStage.y,2,2);
	setbkcolor(LIGHTGRAY);
	settextcolor(BLACK);
	settextstyle(16, 0, _T("宋体"));
	fp=fopen("c:/电脑鼠模拟程序/word/word.txt","rt");
	if(fp==NULL)
	{
		sprintf(str,"Discovery requires expermentation!");
	}
	else
	{
		srand((unsigned)time(NULL));
		key=rand()%7+1;
		for(i=0;i<key;i++)
		{
			fscanf(fp,"%s\n",str);
		}
	}
	outtextxy(5, 5, str);
	fclose(fp);
	PaintTip(1);
	CreateMaze();
}
/*********************************************************************************************************
更新数据
*********************************************************************************************************/
void Update(int i,int j,int number)
{
	char str[20];
	InitParam pixel;
	pixel.x=MaxStage.x+wh+40;
	pixel.y=MinStage.y+7+17*wh/2;
	settextstyle(15, 0, _T("宋体"));
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	sprintf(str,"(%d,%d)",i,j);
	outtextxy(pixel.x,pixel.y-wh,str);
	sprintf(str,"%d",map[i][j].di[up]);
	outtextxy(pixel.x,pixel.y,str);
	sprintf(str,"%d",map[i][j].di[down]);
	outtextxy(pixel.x,pixel.y+wh/2,str);
	sprintf(str,"%d",map[i][j].di[left]);
	outtextxy(pixel.x,pixel.y+wh,str);
	sprintf(str,"%d",map[i][j].di[right]);
	outtextxy(pixel.x,pixel.y+3*wh/2,str);
	sprintf(str,"%ld秒",number);
	outtextxy(pixel.x+30,pixel.y+7*wh/2,str);	
}
/*********************************************************************************************************
开始界面
*********************************************************************************************************/
void HelloWorld()
{
	int flag=1;
	initgraph(640,480);
	loadimage(NULL,"c:/电脑鼠模拟程序/图片/system1.jpg",640,480,1);
	MOUSEMSG m;	// 定义鼠标消息
	while(flag)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_MOUSEMOVE:
			break;
		case WM_LBUTTONDOWN:
			if (m.x>300&&m.x<370&&m.y>260&&m.y<300)
			{
				InitSystem();
				flag=0;
			}
			else if(m.x>300&&m.x<370&&m.y>340&&m.y<380)
			{
				closegraph();
			}
			break;
		case WM_RBUTTONUP:break;
		}
	}
}
/*********************************************************************************************************
计算光标左击的位置，以及启动的按钮
-1--不在菜单区域
0--创建新迷宫
1--开始电脑鼠
2--暂停电脑鼠
3--继续电脑鼠
4--退出电脑鼠
*********************************************************************************************************/
int CountTu(int x,int y)
{
	int i=0;
	if(x>=(MaxStage.x+wh/2)&&x<=(MaxScar.x-wh/2))
	{
		for(i=0;i<5;i++)
		{
			if(y>=(MinStage.y+3*i*wh/2)&&y<=(MinStage.y+(2+3*i)*wh/2))
			{
				return i;
			}
		}
	}
	return -1;
}
/*********************************************************************************************************
询问迷宫的大小，第一步实现8*8，16*16，自定义在拓展范围内
*********************************************************************************************************/
void AskForSize()/*询问迷宫的大小,起点和终止点*/
{
	char DefaultSize[5]="1";
	char NowSize[5];
	int i;
	InputBox(NowSize,sizeof(NowSize),"1:8*8\n2:16*16","请输入迷宫的规格",DefaultSize,100,50,1);
	if(!strcmp(DefaultSize,NowSize))
	{
		MazeSize=8;
		MazeEnd=6;	
	}
	else
	{	
		MazeSize=16;
		MazeEnd=14;
	}
	map=(MazeState **)malloc((MazeSize-1)*sizeof(MazeState *));
	for(i=0;i<(MazeSize-1);i++)
	{
		map[i]=(MazeState*)malloc((MazeSize-1)*sizeof(MazeState));
	}
}
int main()
{
	int i;
	allflag=1;
	MOUSEMSG m;	// 定义鼠标消息
	HelloWorld();
	while(allflag)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_MOUSEMOVE:
			break;
		case WM_LBUTTONDOWN:
			{
				i=CountTu(m.x,m.y);	
				if(i==0)
				{
					InitSystem();
				}
				else if(i==1)
				{
					t1=time(NULL);
					SearchMaze();
				}
				else if(i==4)
				{
					allflag=0;
				}
			};break;
		case WM_RBUTTONUP:break;
		}
	}
	return 0;
}
