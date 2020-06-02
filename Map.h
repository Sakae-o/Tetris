#pragma once

#include"Block.h"
#include"Map.h"

const int MAXY = 24;
const int MAXX = 15;

class Block;

class Map {
public:
	Map(int xx, int yy);

	void DrawMap();		//显示游戏区域
	void clearMap();

	int Clear_Line();	//判断并执行消行，返回的是消的行数
	void Add_line(int cnt);	//同时对方加cnt行，调用时cnt为对方方块的Clear_Line的值

	int Clear_update();		//消行后更新地图,返回的是消的行数
	void Add_update(int cnt);			//增行后更新地图

	int getTop();		//获取当前最顶行所在位置
	bool judgeOver();	//判断游戏是否结束

	friend void fuse(Map& M, Block& B);

	int map[MAXY][MAXX];	//地图数据
	int x, y;		//左上角的像素坐标
};
