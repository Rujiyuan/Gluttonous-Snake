#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#define WALL 35//宏定义墙的边长（需为奇数）
int SX = WALL / 2, SY = WALL / 2, len = 4, map[WALL * WALL] = { 0 };//定义全局变量头的横纵坐标SX、SY，蛇长len，地图（-2:墙；-1:食物;0:空白;>0:蛇身）
char c = 'd', c1 = 'd', deaw[WALL * WALL * 2 + 1] = { 0 };//定义初始方向都为向右


//判断是否与原方向冲突函数
void judge()
{
	switch (c1) 
	{
	case 'a':case 'A': if (c != 'd') c = 'a'; break;
	case 'd':case 'D': if (c != 'a') c = 'd'; break;
	case 'w':case 'W': if (c != 's') c = 'w'; break;
	case 's':case 'S': if (c != 'w') c = 's'; break;
	case ' ': _getch();  break;//空格暂停
	case 27:exit(0); break;//Esc退出
	}
}


//更新头坐标函数
void update_snake()
{
	switch (c)//可穿边界，通过判断蛇的横纵坐标来改变蛇头的位置
	{
	case 'a':if (SX > 0) SX -= 1; else SX += WALL-1; break;
	case 'd':if (SX < WALL-1) SX += 1; else SX -= WALL-1; break;
	case 's':if (SY < WALL-1) SY += 1; else SY -= WALL-1; break;
	case 'w':if (SY > 0) SY -= 1; else SY += WALL-1; break;
	}
}


//绘制地图，绘制蛇身函数
void draw()
{
	int i;//定义循环变量
	if (map[SY * WALL + SX] == -1)//判断是否吃到食物
	{
		len++;//吃到食物蛇身加1
		do i = rand() % (WALL * WALL);//随机生成在游戏界面内的数，用do...while...来控制随机生成的数不与墙和蛇身重合
		while (map[i] == -2 || map[i] > 0);//保证食物生成位置为空地
		map[i] = -1;//吃掉食物后再随机生成食物
		sprintf_s(deaw, 32, "title 得分:%d", len - 4);//计分板，得分是蛇身减去一开始就有的四个蛇身长度
		system(deaw);//在窗口画出地图和蛇
	}
	else 
		for (i = 0; i < WALL * WALL; i++)//全部蛇身值-1
			if (map[i] > 0)map[i] -= 1;
	map[SY * WALL + SX] = len;//蛇头赋值
	for (i = 0; i < WALL * WALL * 2; i++)//更新绘制缓存
	{
		if (map[i / 2] == 0)deaw[i] = ' ';//因所绘制的图像占两个位置，都需/2
		else if (map[i / 2] > 0)deaw[i] = (i % 2) ? ')' : '(';//蛇身
		else if (map[i / 2] == -2)deaw[i] = (i & 1) ? ']' : '[';//墙
		else deaw[i] = '0';//食物
	}
}


//主函数
int main()
{
	srand((unsigned)malloc(1));//初始化随机数种子，malloc动态分布，返回随机地址
	void judge();//申明判断是否与原方向冲突函数
	void update_snake();//申明更新头坐标函数
	void draw();//申明绘制地图，绘制蛇身函数
	int rd, j;//，随机变量rd,循环变量j
	//char c1 = 'd';//定义初始方向为向右行
	for (j = 0; j < WALL; j += 2)//-2:墙
		map[j] = map[WALL * WALL - 1 - j] = map[j * WALL] = map[j * WALL + WALL - 1] = -2;//使四周的墙都隔一格分布
	for (j = 3; j < WALL - 3; j += 2)
		map[4 * WALL - 1 - j] = map[WALL * (WALL - 3) - 1 - j] = map[j * WALL + 3] = map[j * WALL + WALL - 4] = -2;
	sprintf_s(deaw, 32, "mode con: cols=%d lines=%d", WALL * 2, WALL);//修改控制台窗口大小
	system(deaw);
	for (int num = 6; num; num--)//生成多个食物，num控制数量，可改变num的数值来改地图中的食物个数
	{
		do rd = rand() % (WALL * WALL);//保证随机生成的数在在游戏界面内且生成的地方为空地，以do...while...实现
		while (map[rd] == -2 || map[rd] > 0);
		map[rd] = -1;//将随机生成食物的地址标为-1
	}
	for (system("title 得分:0"); 1; Sleep(100))//初始化计分板，无限循环，Sleep延时
	{
		if (_kbhit() && (c1 = _getch())) //判断是否有输入，有输入则赋值给c1,getch函数自动读取按下的字符，无需按回车键
			judge();//调用函数，判断是否与原方向冲突
		update_snake();//调用更新头坐标函数
		if (map[SY * WALL + SX] > 1 || map[SY * WALL + SX] == -2)
			exit(!_getch());//判断是否吃到自己或者撞墙
		draw();//调用绘制地图，绘制蛇身函数
		//system("cls");//清屏
		printf(deaw);//打印
	}
}
