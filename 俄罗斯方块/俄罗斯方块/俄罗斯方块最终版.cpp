#include<graphics.h>
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
void peizhi();
void initsystem();
void paint_box(int i, int j, int thecolor,int lock);
void paint_next();
void paint_score();
void clear_box(int i,int j);
void the_game();
void check_move();
void paint_all();
void check_score();
void check_success();
void move_to_end();
int scrx, scry, maxx, minx, miny, maxy;
int wh = 32;
int success_flag=0, score, all_flag = 1;
int allgame[22][12];//加上两边的边界和底线 
int allcolor[22][12];//每个方块的颜色
int tuxing[4][7][4][4] = {
	{
		{ { 0, 0, 0, 0 }, { 0, 0, 1, 0 }, { 0, 1, 1, 1 }, { 0, 0, 0, 0 }, },
		{ { 0, 0, 0, 0 }, { 0, 0, 1, 1 }, { 0, 1, 1, 0 }, { 0, 0, 0, 0 }, },
		{ { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1 }, { 0, 0, 0, 0 }, },
		{ { 0, 0, 0, 0 }, { 1, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 0 }, },
		{ { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, 1, 1, 0 }, { 0, 0, 0, 0 }, },
		{ { 0, 0, 0, 0 }, { 0, 0, 0, 1 }, { 0, 1, 1, 1 }, { 0, 0, 0, 0 }, },
		{ { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0, 0, 0, 0 }, },
	}
};//七种初始的图案 
struct box_state//对于某一个图形的状态描述 
{
	int bi;//表示选择的图形状态 
	int bj;//表示选择的图形种类 
	int gi;//表示当前块的纵向坐标 
	int gj;//表示当前块的横向坐标 
	int color;//表示当前块的颜色 
	int to_move_left;//向左边移动的条件 
	int to_move_right;//向右边移动的条件 
	int to_move_down;//向下移动的条件 
	int turn_around;//进行旋转的条件 
}boxs[3];//boxs[0]表示现在的状态 
void peizhi()//进行旋转，出现4*7=28种图案，包括重复的 
{
	int shuzu[4][4];
	int i, j, x, y;
	for (i = 1; i <4; i++)
	{
		for (j = 0; j < 7; j++)
		{
			for (x = 0; x < 4; x++)
			{
				for (y = 0; y < 4; y++)
				{
					shuzu[x][y] = tuxing[i - 1][j][x][y];
				}
			}
			for (x = 0; x < 4; x++)
			{
				for (y = 0; y < 4; y++)
				{
					tuxing[i][j][x][y] = shuzu[y][3 - x];
				}
			}
		}
	}
}
void clear_box(int i, int j)
{
	int x,y;
	x = (j - 1)*wh, y = (i - 4)*wh;
	clearrectangle(x, y, x + wh, y + wh);
}
void paint_box(int i, int j, int thecolor,int lock)//画出某一点的方格 //0代表锁定的游戏界面1代表未锁定的界面
{
	int x, y;
	if ((lock == 0 && i >= 4 && i < 21 && j >= 1 && j < 11) || lock == 1)
	{
		x = (j - 1)*wh, y = (i - 4)*wh;
		setcolor(WHITE);
		rectangle(x, y, x + wh, y + wh);
		setfillstyle(PS_SOLID);
		switch (thecolor)
		{
		case 0:setfillcolor(BLACK); break;
		case 1:setfillcolor(RED); break;
		case 2:setfillcolor(GREEN); break;
		case 3:setfillcolor(LIGHTGRAY); break;
		case 4:setfillcolor(BLUE); break;
		case 5:setfillcolor(DARKGRAY); break;
		case 6:setfillcolor(YELLOW); break;
		case 7:setfillcolor(LIGHTBLUE); break;
		}
		floodfill(x + wh / 2, y + wh / 2, WHITE);
	}
}
void paint_score()//画出分数 
{
	int i, num[6], z = 100000, sum, flag = 0;
	int x = 11 * wh, y = 13 * wh + wh / 2;
	sum = score;
	for (i = 0; i<6; i++)
	{
		num[i] = sum / z;
		sum = sum - num[i] * z;
		z = z / 10;
	}
	settextstyle(30, 0, _T("宋体"));
	setbkcolor(BLACK);
	setcolor(RED);
	for (i = 0; i < 6; i++)
	{
		if (num[i] != 0)
		{
			flag = 1;
		}
		else if (flag == 0 && i == 5)
		{
			outtextxy(x, y, '0');
		}
		if (flag == 1)
		{
			switch (num[i])
			{
			case 0: outtextxy(x, y, '0'); break;
			case 1: outtextxy(x, y, '1'); break;
			case 2: outtextxy(x, y, '2'); break;
			case 3: outtextxy(x, y, '3'); break;
			case 4: outtextxy(x, y, '4'); break;
			case 5: outtextxy(x, y, '5'); break;
			case 6: outtextxy(x, y, '6'); break;
			case 7: outtextxy(x, y, '7'); break;
			case 8: outtextxy(x, y, '8'); break;
			case 9: outtextxy(x, y, '9'); break;
			default: break;
			}
			x = x + wh / 2;
		}
	}
}
void initsystem()//初始化系统 
{
	int i, j;
	scrx = 18 * wh;
	scry = 17 * wh;
	initgraph(scrx, scry);
	setbkcolor(BLACK);
	maxx = 10 * wh;
	maxy = scry;
	miny = 0;
	minx = 0;
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID);
	line(maxx + 1, miny, maxx + 1, maxy);
	peizhi();
	success_flag = 0;
	score = 0;
	for (i = 0; i < 21; i++)
	{
		for (j = 1; j < 11; j++)
		{
			allgame[i][j] = 0;
		}
	}
	for (i = 0; i < 21; i++)
	{
		allgame[i][0]=2;
		allgame[i][11]=2;
	}
	for(i=0;i<12;i++)
	{
		allgame[21][i]=2;
	}
	settextcolor(BLUE);
	setbkcolor(BLACK);
	settextstyle(30, 0, _T("宋体"));
	outtextxy(maxx + wh / 2, miny + wh / 3 + 6 * wh, _T("NEXT:"));
	outtextxy(maxx + wh / 2, miny + 12 * wh + wh / 3, _T("SCORE:"));
	outtextxy(maxx + wh / 2, miny + wh / 3, _T("说明:"));
	settextcolor(WHITE);
	settextstyle(15, 0, _T("宋体"));
	outtextxy(maxx + wh / 2 + 2 * wh, miny + wh / 3 + 2 * wh, _T("k/K  开始"));
	outtextxy(maxx + wh / 2 + 2 * wh, miny + wh / 3 + 2 * wh + wh / 2, _T("r/R  重开"));
	outtextxy(maxx + wh / 2 + 2 * wh, miny + wh / 3 + 3 * wh, _T("a/A  向左"));
	outtextxy(maxx + wh / 2 + 2 * wh, miny + wh / 3 + 3 * wh + wh / 2, _T("s/S  向下"));
	outtextxy(maxx + wh / 2 + 2 * wh, miny + wh / 3 + 4 * wh, _T("d/D  向右"));
	outtextxy(maxx + wh / 2 + 2 * wh, miny + wh / 3 + 4 * wh + wh / 2, _T("w/W  旋转"));
	outtextxy(maxx + wh / 2 + 2 * wh, miny + wh / 3 + 5 * wh, _T("Esc  退出"));
	paint_score();
}
void paint_next()//画出下一个图形 
{
	int x, y;
	srand((unsigned)time(NULL));
	boxs[1].bi = rand() % 4;
	boxs[1].bj = rand() % 7;
	boxs[1].color = rand() % 7+1;
	for (x = 0; x < 4; x++)
		for (y = 0; y < 4; y++)
		{
			clear_box(x + 12, y + 13);
		}
	for (x = 0; x < 4; x++)
		for (y = 0; y < 4; y++)
		{
			if (tuxing[boxs[1].bi][boxs[1].bj][x][y] == 1)
			{
				paint_box(x + 12, y + 13, boxs[1].color, 1);
			}
		}
}
void check_move()//判断能否进行各种操作 
{
	int i, j;
	boxs[0].to_move_down = 0;
	boxs[0].to_move_left = 0;
	boxs[0].to_move_right = 0;
	boxs[0].turn_around = 0;
	for (i = boxs[0].gi; i < boxs[0].gi + 4; i++)//判断是否能向左移 
	{
		for (j = boxs[0].gj ; j < boxs[0].gj + 4; j++)
		{
			if (allgame[i][j-1] == 2 && allgame[i][j] == 1)
			{
				boxs[0].to_move_left = 1;
			}
		}
	}
	for (i = boxs[0].gi; i < boxs[0].gi + 4; i++)//判断是否能向右移 
	{
		for (j = boxs[0].gj; j < boxs[0].gj + 4; j++)
		{
			if (allgame[i][j] == 1 && allgame[i][j + 1] == 2)
			{
				boxs[0].to_move_right = 1;
			}
		}
	}
	for (i = boxs[0].gi; i < boxs[0].gi +4; i++)//判断是否能向下移 
	{
		for (j = boxs[0].gj; j < boxs[0].gj + 4; j++)
		{
			if (allgame[i][j] == 1 && allgame[i+1][j ] == 2)
			{
				boxs[0].to_move_down = 1;
			}
		}
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(allgame[i+boxs[0].gi][j+boxs[0].gj]==2&&tuxing[(boxs[0].bi+1)%4][boxs[0].bj][i][j]==1)
			{
				boxs[0].turn_around=1;
			}
		}
	}
}
void chuancan(int type)//进行各种操作 
{
	int i, j, k;
	if (type == 1)//把图形传入数组
	{
		boxs[0].gi = 0;
		boxs[0].gj = 3;
		for (i = 0; i < 4; i++)
			for (j = 3; j < 7; j++)
			{
				allgame[i][j] = tuxing[boxs[1].bi][boxs[1].bj][i][j - 3];
			}
	}
	else if (type == 2)//左移
	{
		for (i = boxs[0].gi+3; i>= boxs[0].gi ; i--)
		{
			for (j = boxs[0].gj; j < boxs[0].gj + 4; j++)
			{
				if (allgame[i][j] == 1)
				{
					allgame[i][j - 1] = allgame[i][j];
					allgame[i][j] = 0;
					clear_box(i, j);
					paint_box(i, j-1, boxs[0].color, 0);
				}
			}
		}
		boxs[0].gj--;
	}
	else if (type == 3)//右移
	{
		for (i = boxs[0].gi + 3; i > boxs[0].gi - 1; i--)
		{
			for (j = boxs[0].gj+3; j > boxs[0].gj -1; j--)
			{
				if (allgame[i][j] == 1)
				{
					allgame[i][j + 1] = allgame[i][j];
					allgame[i][j] = 0;
					clear_box(i, j);
					paint_box(i, j+1, boxs[0].color, 0);
				}
			}
		}
		boxs[0].gj++;
	}
	else if (type == 4)//下移
	{
		for (i = boxs[0].gi + 3; i > boxs[0].gi - 1; i--)
		{
			for (j = boxs[0].gj + 3; j > boxs[0].gj - 1; j--)
			{
				if (allgame[i][j] == 1)
				{
					allgame[i + 1][j] = allgame[i][j];
					allgame[i][j] = 0;
					clear_box(i, j);
					paint_box(i+1, j, boxs[0].color, 0);
				}
			}
		}
		boxs[0].gi++;
	}
	else if (type == 5)//旋转
	{
		boxs[0].bi = (boxs[0].bi + 1) % 4;
		for (i = boxs[0].gi; i < boxs[0].gi + 4; i++)
		{
			for (j = boxs[0].gj; j < boxs[0].gj + 4; j++)
			{
				if (allgame[i][j] == 1 && tuxing[boxs[0].bi][boxs[0].bj][i - boxs[0].gi][j - boxs[0].gj]==0)
				{
					clear_box(i, j);
					allgame[i][j] = 0;
				}
			}
		}
		for (i = boxs[0].gi; i < boxs[0].gi + 4; i++)
		{
			for (j = boxs[0].gj; j < boxs[0].gj + 4; j++)
			{
				 if (tuxing[boxs[0].bi][boxs[0].bj][i - boxs[0].gi][j - boxs[0].gj] == 1)
				{
					allgame[i][j] = 1;
					paint_box(i, j, boxs[0].color, 0);
				}
			}
		}
	}
	else if (type == 6)//消去
	{
		k = 4;
		while (k < 21)
		{
			for (i = 20; i > 3; i--)
			{
				k = i;
				for (j = 1; j < 11; j++)
				{
					if (allgame[i][j] == 0)
					{
						k = -1;
					}
				}
				if (k == i)//消去
				{
					score = score + 100;
					for (k; k > 4; k--)
					{
						for (j = 1; j < 11; j++)
						{
							allgame[k][j] = allgame[k - 1][j];
							allcolor[k][j] = allcolor[k - 1][j];
						}
					}
					for (j = 1; j < 11; j++)
					{
						allgame[4][j] = 0;
						allcolor[4][j] = 0;
					}
					clearrectangle(0, 0, maxx, maxy);
					paint_all();
					paint_score();
				}
			}
			k = 23;
		}
	}
	else if (type == 7)//改变当前值
	{
		for (i = boxs[0].gi; i < boxs[0].gi + 4; i++)
		{
			for (j = boxs[0].gj; j < boxs[0].gj + 4; j++)
			{
				if (allgame[i][j] == 1)
				{
					allgame[i][j] = 2;
					allcolor[i][j] = boxs[0].color;
				}
			}
		}
	}
}
void paint_all()
{
	int i, j;
	for (i = 4; i < 21; i++)
	{
		for (j = 1; j < 11; j++)
		{
			if (allgame[i][j] == 2)
			{
				paint_box(i, j, allcolor[i][j], 0);
			}
		}
	}
}
void check_success()
{
	int  j;
	for (j = 1; j < 11; j++)
	{
		if (allgame[4][j] == 2)
		{
			success_flag = 1;
		}
	}
}
void the_game()
{
	int flag = 1;
	char ch;
	clock_t st, et;
	st = 0;
	int stay_time = 1000;
	while (true)
	{
		flag = 1;
		boxs[0] = boxs[1];
		chuancan(1);
		check_move();
		check_success();
		paint_next();
		while (flag == 1 && success_flag == 0)
		{
			if (_kbhit())
			{
				check_move();
				ch = _getch();
				if ((ch == 'a' || ch == 'A') && boxs[0].to_move_left != 1)
				{
					chuancan(2);
				}
				if ((ch == 'd' || ch == 'D') && boxs[0].to_move_right != 1)
				{
					chuancan(3);
				}
				if ((ch == 's' || ch == 'S') && boxs[0].to_move_down != 1)
				{
					chuancan(4);
					Sleep(50);
				}
				if ((ch == 'w' || ch == 'W') && boxs[0].turn_around != 1)
				{
					chuancan(5);
				}
				if (ch == 27)
				{
					success_flag = 1;
					flag = 0;
				}
				if (ch == 'r' || ch == 'R')
				{
					return;
				}
				check_move();
			}
			et = clock();
			if (!_kbhit()&&(et-st)%stay_time==0)
			{
				check_move();
				if (boxs[0].to_move_down == 0)
				{
					Sleep(stay_time);
					chuancan(4);
					if (score < 5000)
					{
						stay_time = 1000 - 100 * (score / 500);
					}
					else
					{
						stay_time = 100;
					}
				}
			}		
			if (boxs[0].to_move_down == 1)
			{
				chuancan(7);
				chuancan(6);
				boxs[0] = boxs[2];
				boxs[1] = boxs[1];
				flag--;
				Sleep(100);
			}
		}
		if (success_flag == 1)
		{
			all_flag = 0;
			return;
		}
	}
}
int main()
{
	char key;
	while (all_flag)
	{
		initsystem();
		paint_next(); 
		key = _getch();
		if (key == 'k')
		{
			the_game();
		}
		else if (key == 27)
		{
			all_flag = 0;
		}
	}
	closegraph();
	return 0;
}