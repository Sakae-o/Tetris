#pragma once

#include"Map.h"
#include"Block.h"

class Map;

class Block {
public:
	void InitialBlock();	//初始化方块
	void DrawBlock(int map_x);		//绘制方块
	void clearBlock(int max_p);		//消除方块
	void DrewNext(int map_x, int map_y);		//在游戏区域旁打印下一个方块
	void clearNext(int map_x, int map_y);

	bool JudgeLeft(Map A);		//分别判断是否可以左移，右移，下落
	bool JudgeRight(Map A);
	bool JudgeDown(Map A);

	bool JudgeTransform(Map A);	//判断是否可以变形

	void Move_Transform(Map A, int player);		//执行移动，变形，消行

	void Down(Map A);		//自动下落

	friend void fuse(Map& M, Block& B);

	int down_control;		//此参数用于调节下落到底后的状态，使方块到底后还能再移动或变形1-2s再进入下一块

private:
	int shape[4][4];
	int x, y;		//这里的x，y表示中心的地图坐标
	float H,S,V;	//颜色数据

	int type;	//方块种类
	int state;	//方块当前的旋转方向

	int bottom;	//若y=0，该方块最底行所在的纵坐标值。此参数用来调整初始下落，确保方块在进入地图前不会被误判为无法下落
};


