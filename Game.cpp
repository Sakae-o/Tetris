#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<string>
#include<graphics.h>
#include<conio.h>
#include<windows.h>

#include"Game.h"

#define Width 1180
#define Hight 600
#define MAXY 24
#define MAXX 15
#define LEN 18
using namespace std;


void Game::GameStop() {
	if (kbhit()) {
		if (getch() == ' ') {
			while (1) {
				if (kbhit() && getch() == ' ')
					break;
			}
		}
	}
}

bool Game::Welcome()
{
	settextcolor(WHITE);
	settextstyle(60, 0, _T("黑体"));
	outtextxy(440, 100, "我罗斯方块");
	settextstyle(30, 0, "黑体");
	outtextxy(200, 280, "我罗斯方块是俄罗斯方块的改进版");
	outtextxy(200, 380, "当一名玩家消去一行，就会让另一名玩家最底下增加随机一行");
	outtextxy(350, 500, "空格 : 开始        esc : 退出");
	char input;
	while (1) {
		input = getch();

		if (input == ' ')
		{
			Game::clearScreen();
			return true;
		}
		if (input == VK_ESCAPE)
		{
			Game::clearScreen();
			return false;
		}
	}
}

bool Game::GameOver(Map P1_map)
{
	Sleep(500);
	Game::clearScreen();
	
	settextcolor(WHITE);
	settextstyle(60, 0, _T("黑体"));
	outtextxy(440, 200, "GameOver");
	if (P1_map.getTop())
	{
		outtextxy(470, 300, "P1 win!");
	}
	else {
		outtextxy(470, 300, "P2 win!");
	}
	outtextxy(200, 500, "空格 : 重来     esc : 退出");
	FlushBatchDraw();

	char input;
	while (1) {
		input = getch();

		if (input == ' ')
		{
			Game::clearScreen();
			return false;
		}
		if (input == VK_ESCAPE)
		{
			Game::clearScreen();
			return true;
		}
	}
}

void Game::clearScreen() {
	setbkcolor(BLACK);
	cleardevice();
}

void Game::CloseGame() {
	if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
		exit(0);
	}
}
