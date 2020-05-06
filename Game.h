class Game {
public:
	void Welcome();		//负责介绍规则和操作，选择开始或退出
	void GameOver();	//显示胜方，选择重来或退出
	void GameStop();	//暂停游戏

	void KeyControl();		//处理键盘输入

	void HideCursor();	 //隐藏光标

};
