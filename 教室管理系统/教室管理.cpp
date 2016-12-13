#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#define skin_max 3
#define scrx 1024
#define scry 640
void init_ui();
void init_ui(int class_type)
{
	char str_skin[60];
	char str_icon[60];
	int str_skin_key=0;
	IMAGE image_skin,image_icon;
	srand((unsigned)time(NULL));
	str_skin_key=rand()%skin_max;
	initgraph(scrx, scry);
	sprintf(str_skin,"f:/教室管理系统/皮肤/skin%d.jpg",str_skin_key);
	loadimage(&image_skin,str_skin,scrx,scry);
	putimage(0,0,&image_skin);
	sprintf(str_icon,"f:/教室管理系统/头像/icon%d.jpg",class_type);
	loadimage(&image_icon,str_icon,scry/6,scry/6);
	putimage(5,5,&image_icon);
	setlinestyle(PS_SOLID,3);
	setlinecolor(WHITE);
	line(scrx/4,scry/6-3,scrx,scry/6-3);
	setlinestyle(PS_SOLID,1);
	setlinecolor(DARKGRAY);
	line(scrx/4,scry/5,scrx,scry/5);
	getch();
	closegraph();
}
void main()
{
	init_ui(0);
}