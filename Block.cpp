#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<string>
#include<graphics.h>
#include<conio.h>

#include"Block.h"

#define Width 1180
#define Hight 600
#define MAXY 24
#define MAXX 15
#define LEN 18
using namespace std;

int all_block[5][4][4][4] = {
	{												//type0
		{{1,1,1,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}},
		{{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
		{{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
		{{1,0,0,0},{1,0,0,0},{1,1,0,0},{0,0,0,0}}
	},

	{												//type1
		{{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
		{{1,0,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},
		{{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}},
		{{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}
	},

	{												//type2
		{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
		{{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},
		{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
		{{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}
	},

	{												//type3
		{{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},
		{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
		{{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},
		{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
	},

	{												//type4
		{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
		{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
		{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
		{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}
	}
};



void Block::InitialBlock() {
	srand(time(0));

	type = rand() % 5;		//设置初始形状
	state = rand() % 5;
	memcpy(shape, all_block[type][state], 16 * sizeof(int));

	x = rand() % (MAXX - 5) + 1;	//设置十六宫格的左上角的地图坐标
	y = 5;

	red = rand() % 256;		//设置颜色
	green = rand() % 256;
	blue = rand() % 256;
}

void Block::DrawBlock(int map_x) {		//此处max_x为地图左上角的像素坐标，用于确认绘制的是1P的方块还是2P的方块
	setfillcolor(RGB(red, green, blue));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (shape[i][j] == 1) {
				int xx = map_x + (x + j) * (LEN + 3);
				int yy = (y + i) * (LEN + 3);
				solidrectangle(xx, yy, xx + LEN, yy + LEN);
			}
		}
	}
}

void Block::clearBlock(int map_x) {
	setfillcolor(BLACK);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (shape[i][j] == 1) {
				int xx = map_x + (x + j) * (LEN + 3);
				int yy = (y + i) * (LEN + 3);
				solidrectangle(xx, yy, xx + LEN, yy + LEN);
			}
		}
	}
}
