#pragma once

class Game {
public:
	static void Welcome();		//负责介绍规则和操作，选择开始或退出
	static void GameOver();	//显示胜方，选择重来或退出
	static void GameStop();	//暂停游戏

	static void KeyControl();		//处理键盘输入


	static bool isStop;		//判断是否处于暂停
};
