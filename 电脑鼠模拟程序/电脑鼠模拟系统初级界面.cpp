#include <graphics.h>
#include <conio.h>

void main()
{
	// ��ʼ����ͼ����
	initgraph(640, 480);
	IMAGE image,image1;
		loadimage(&image,_T("c:/������ģ�����/ͼƬ/dir.jpg"));
	loadimage(&image1,_T("c:/������ģ�����/ͼƬ/eraser.jpg"));
			putimage(0,0,&image);
			getch();
				putimage(0,0,&image1);
	getch();
	closegraph();
}