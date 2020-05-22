#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<string>
#include<graphics.h>
#include<conio.h>
#include<Windows.h>

#include"Game.h"

#define Width 1180
#define Hight 600
#define MAXY 24
#define MAXX 15
#define LEN 18
using namespace std;

bool Game::isStop = false;	//初始化暂停判断参数

void Game::GameStop() {
	while (isStop) {
		Sleep(100);
		char input;
		input = getch();
		if (input == ' ') {
			isStop = false;
		}
	}
}
