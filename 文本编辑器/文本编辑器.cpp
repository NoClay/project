/*头文件区域*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

/*函数声明区域*/

void GoToXy(int x, int y);
void PaintPs();
void PaintRectangle(int i,int j,int a,int b);

/*全局变量区域*/


/*函数定义区域*/
 
void GoToXy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void PaintRectangle(int i,int j,int a,int b)
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
void PaintPs()
{
	int j;
	int i=70;
	int k=5; 
	gotoxy(15,1);
	printf("欢迎使用My word");
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
	gotoxy(i,k+12);
	printf("按s键保存图书");
	gotoxy(i,k+14);
	printf("按a键全部删除");
	gotoxy(i,k+16+weitiao[2]);
	printf("按esc退出使用");  
}


/*主函数区域*/

int main()
{
	
} 
