#pragma once
#include"Map.h"
#include<string>

class Game {
public:
	static bool Welcome();		//负责介绍规则和操作，选择开始或退出
	static bool GameOver(Map P1_map);	//显示胜方，选择重来或退出
	static void GameStop();	//暂停游戏
	static void clearScreen(); //屏幕清为全黑
};
