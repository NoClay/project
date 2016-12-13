#include <graphics.h>
#include <conio.h>

void main()
{
	// 初始化绘图窗口
	initgraph(640, 480);
	IMAGE image,image1;
		loadimage(&image,_T("c:/电脑鼠模拟程序/图片/dir.jpg"));
	loadimage(&image1,_T("c:/电脑鼠模拟程序/图片/eraser.jpg"));
			putimage(0,0,&image);
			getch();
				putimage(0,0,&image1);
	getch();
	closegraph();
}