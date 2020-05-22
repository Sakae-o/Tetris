#pragma once


class Block {
public:
	void InitialBlock();	//初始化方块
	void DrawBlock(int map_x);		//绘制方块
	void clearBlock(int max_p);		//消除方块
	void DrewNext();		//在游戏区域旁打印下一个方块

	bool JudgeLeft();		//分别判断是否可以左移，右移，下落
	bool JudgeRight();
	bool JudgeDown();

	bool JudgeTransform();	//判断是否可以变形

	void Move();		//执行移动，变形，消行
	void Transform();

	void Down();		//自动下落
	void accelerate();	//手动加速

private:
	int shape[4][4];
	int x, y;		//这里的x，y表示中心的地图坐标
	int red, green, blue;	//颜色数据

	int type;	//方块种类
	int state;	//方块当前的旋转方向
};

