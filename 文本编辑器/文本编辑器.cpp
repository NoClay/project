/*ͷ�ļ�����*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

/*������������*/

void GoToXy(int x, int y);
void PaintPs();
void PaintRectangle(int i,int j,int a,int b);

/*ȫ�ֱ�������*/


/*������������*/
 
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
void PaintPs()
{
	int j;
	int i=70;
	int k=5; 
	gotoxy(15,1);
	printf("��ӭʹ��My word");
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


/*����������*/

int main()
{
	
} 
