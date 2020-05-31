#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<string>
#include<graphics.h>
#include<conio.h>

#include"Block.h"
#include"Map.h"

#define Width 1180
#define Hight 600
#define MAXY 24
#define MAXX 15
#define LEN 18
using namespace std;

int all_block[7][4][4][4] = {
	{												//type0
		{{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
		{{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
		{{0,0,0,0},{0,0,1,0},{1,1,1,0},{0,0,0,0}},
		{{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}}
	},

	{												//type1
		{{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
		{{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}},
		{{0,0,0,0},{1,0,0,0},{1,1,1,0},{0,0,0,0}},
		{{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}
	},

	{												//type2
		{{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}},
		{{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
		{{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
		{{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}
	},

	{												//type3
		{{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
		{{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
		{{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
		{{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}
	},

	{												//type4
		{{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
		{{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
		{{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
		{{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}}
	},

	{												//type5
		{{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}},
		{{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
		{{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}},
		{{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
	},

	{												//type6
		{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
		{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
		{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
		{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}
	}
};



void Block::InitialBlock() {
	do {						//设置初始形状，采取了一点特殊处理以平衡概率
		type = rand() % 21;
    } while (type == 20 || type == 19 || type == 17 || type == 18);
	while (type > 6) {
		type -= 7;
	}
	state = rand() % 4;

	memcpy(shape, all_block[type][state], 16 * sizeof(int));

	x = rand() % (MAXX - 5) + 1;	//设置十六宫格的左上角的地图坐标
    y = -4;

	H = rand() % 361;		//设置颜色
	S = (rand() % 41 + 40) / 100.0;
	V = (rand() % 11 + 90) / 100.0;

    down_control = 0;

    if (type == 6) {    //设置bottom值
        bottom = 1;
    }
    else {
        if (type != 5 || (type == 5 && (state == 0 || state == 2))) {
            bottom = 2;
        }
        else {
            bottom = 3;
        }
    }
}

void Block::DrawBlock(int map_x) {		//此处max_x为地图左上角的像素坐标，用于确认绘制的是1P的方块还是2P的方块
	setfillcolor(HSVtoRGB(H,S,V));
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

void Block::DrewNext(int map_x, int map_y) {
    setfillcolor(HSVtoRGB(H, S, V));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] == 1) {
                int xx = map_x + j * (LEN + 3);
                int yy = map_y + i * (LEN + 3);
                solidrectangle(xx, yy, xx + LEN, yy + LEN);
            }
        }
    }
}

void Block::clearNext(int map_x, int map_y) {
    setfillcolor(BLACK);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] == 1) {
                int xx = map_x + j * (LEN + 3);
                int yy = map_y + i * (LEN + 3);
                solidrectangle(xx, yy, xx + LEN, yy + LEN);
            }
        }
    }
}

bool Block::JudgeLeft(Map A)
{
    if (type == 0)
    {
        switch (state)
        {
        case 0:if (A.map[y + 1][x - 1] == 0 && A.map[y + 2][x - 1] == 0)return true; return false;
        case 1:if (A.map[y][x - 1] == 0 && A.map[y + 1][x] == 0 && A.map[y + 2][x] == 0)return true; return false;
        case 2:if (A.map[y + 1][x + 1] == 0 && A.map[y + 2][x - 1] == 0)return true; return false;
        case 3:if (A.map[y][x] == 0 && A.map[y + 1][x] == 0 && A.map[y + 2][x] == 0)return true; return false;
        }
    }
    if (type == 1)
    {
        switch (state)
        {
        case 0:if (A.map[y + 1][x - 1] == 0 && A.map[y + 2][x + 1] == 0)return true; return false;
        case 1:if (A.map[y][x] == 0 && A.map[y + 1][x] == 0 && A.map[y + 2][x - 1] == 0)return true; return false;
        case 2:if (A.map[y + 1][x - 1] == 0 && A.map[y + 2][x - 1] == 0)return true; return false;
        case 3:if (A.map[y][x] == 0 && A.map[y + 1][x] == 0 && A.map[y + 2][x] == 0)return true; return false;
        }
    }
    if (type == 2)
    {
        switch (state)
        {
        case 0:if (A.map[y + 1][x] == 0 && A.map[y + 2][x - 1] == 0)return true; return false;
        case 1:if (A.map[y][x] == 0 && A.map[y + 1][x] == 0 && A.map[y + 2][x] == 0)return true; return false;
        case 2:if (A.map[y + 1][x - 1] == 0 && A.map[y + 2][x] == 0)return true; return false;
        case 3:if (A.map[y][x] == 0 && A.map[y + 1][x - 1] == 0 && A.map[y + 2][x] == 0)return true; return false;
        }
    }
    if (type == 3)
    {
        switch (state)
        {
        case 0:
        case 2:if (A.map[y + 1][x - 1] == 0 && A.map[y + 2][x] == 0)return true; return false;
        case 1:
        case 3:if (A.map[y][x + 1] == 0 && A.map[y + 1][x] == 0 && A.map[y + 2][x] == 0)return true; return false;
        }
    }
    if (type == 4)
    {
        switch (state)
        {
        case 0:
        case 2:if (A.map[y + 1][x] == 0 && A.map[y + 2][x - 1] == 0)return true; return false;
        case 1:
        case 3:if (A.map[y][x] == 0 && A.map[y + 1][x] == 0 && A.map[y + 2][x + 1] == 0)return true; return false;
        }
    }
    if (type == 5)
    {
        switch (state)
        {
        case 0:
        case 2:if (A.map[y + 2][x - 1] == 0)return true; return false;
        case 1:
        case 3:if (A.map[y][x + 1] == 0 && A.map[y + 1][x + 1] == 0 && A.map[y + 2][x + 1] == 0 && A.map[y + 3][x + 1] == 0)return true; return false;
        }
    }
    if (type == 6)
    {
        if (A.map[y][x - 1] == 0 && A.map[y + 1][x - 1] == 0)return true; return false;
    }
}

bool Block::JudgeRight(Map A)
{
    if (type == 0)
    {
        switch (state)
        {
        case 0:if (A.map[y + 1][x + 3] == 0 && A.map[y + 2][x + 1] == 0)return true; return false;
        case 1:if (A.map[y][x + 2] == 0 && A.map[y + 1][x + 2] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        case 2:if (A.map[y + 1][x + 3] == 0 && A.map[y + 2][x + 3] == 0)return true; return false;
        case 3:if (A.map[y][x + 2] == 0 && A.map[y + 1][x + 2] == 0 && A.map[y + 2][x + 3] == 0)return true; return false;
        }
    }
    if (type == 1)
    {
        switch (state)
        {
        case 0:if (A.map[y + 1][x + 3] == 0 && A.map[y + 2][x + 3] == 0)return true; return false;
        case 1:if (A.map[y][x + 2] == 0 && A.map[y + 1][x + 2] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        case 2:if (A.map[y + 1][x + 1] == 0 && A.map[y + 2][x + 3] == 0)return true; return false;
        case 3:if (A.map[y][x + 3] == 0 && A.map[y + 1][x + 2] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        }
    }
    if (type == 2)
    {
        switch (state)
        {
        case 0:if (A.map[y + 1][x + 2] == 0 && A.map[y + 2][x + 3] == 0)return true; return false;
        case 1:if (A.map[y][x + 2] == 0 && A.map[y + 1][x + 3] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        case 2:if (A.map[y + 1][x + 3] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        case 3:if (A.map[y][x + 2] == 0 && A.map[y + 1][x + 2] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        }
    }
    if (type == 3)
    {
        switch (state)
        {
        case 0:
        case 2:if (A.map[y + 1][x + 2] == 0 && A.map[y + 2][x + 3] == 0)return true; return false;
        case 1:
        case 3:if (A.map[y][x + 3] == 0 && A.map[y + 1][x + 3] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        }
    }
    if (type == 4)
    {
        switch (state)
        {
        case 1:
        case 3:if (A.map[y][x + 2] == 0 && A.map[y + 1][x + 3] == 0 && A.map[y + 2][x + 3] == 0)return true; return false;
        case 0:
        case 2:if (A.map[y + 1][x + 3] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        default:break;
        }
    }
    if (type == 5)
    {
        switch (state)
        {
        case 0:
        case 2:if (A.map[y + 2][x + 4] == 0)return true; return false;
        case 1:
        case 3:if (A.map[y][x + 3] == 0 && A.map[y + 1][x + 3] == 0 && A.map[y + 2][x + 3] == 0 && A.map[y + 3][x + 3] == 0)return true; return false;
        }
    }
    if (type == 6)
    {
        if (A.map[y][x + 2] == 0 && A.map[y + 1][x + 2] == 0)return true; return false;
    }
}
bool Block::JudgeDown(Map A)
{
    if (y + bottom < 0) {
        return true;
    }
    if (type == 0)
    {
        switch (state)
        {
        case 0:if (A.map[y + 3][x] == 0 && A.map[y + 2][x + 1] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        case 1:if (y + bottom == -1) return true;
               if (y + bottom == 0 && A.map[y + 3][x + 1] == 0) return true;
               if (A.map[y + 1][x] == 0 && A.map[y + 3][x + 1] == 0)return true; return false;
        case 2:if (A.map[y + 3][x] == 0 && A.map[y + 3][x + 1] == 0 && A.map[y + 3][x + 2] == 0)return true; return false;
        case 3:if (A.map[y + 3][x + 1] == 0 && A.map[y + 3][x + 2] == 0)return true; return false;
        }
    }
    if (type == 1)
    {
        switch (state)
        {
        case 0:if (A.map[y + 2][x] == 0 && A.map[y + 2][x + 1] == 0 && A.map[y + 3][x + 2] == 0)return true; return false;
        case 1:if (A.map[y + 3][x] == 0 && A.map[y + 3][x + 1] == 0)return true; return false;
        case 2:if (A.map[y + 3][x] == 0 && A.map[y + 3][x + 1] == 0 && A.map[y + 3][x + 2] == 0)return true; return false;
        case 3:if (y + bottom == -1) return true;
            if (y + bottom == 0 && A.map[y + 3][x + 1] == 0) return true;
               if (A.map[y + 3][x + 1] == 0 && A.map[y + 1][x + 2] == 0)return true; return false;
        }
    }
    if (type == 2)
    {
        switch (state)
        {
        case 0:if (A.map[y + 3][x] == 0 && A.map[y + 3][x + 1] == 0 && A.map[y + 3][x + 2] == 0)return true; return false;
        case 1:if (A.map[y + 3][x + 1] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        case 2:if (A.map[y + 2][x] == 0 && A.map[y + 2][x + 2] == 0 && A.map[y + 3][x + 1] == 0)return true; return false;
        case 3:if (A.map[y + 2][x] == 0 && A.map[y + 3][x + 1] == 0)return true; return false;
        }
    }
    if (type == 3)
    {
        switch (state)
        {
        case 0:
        case 2:if (A.map[y + 2][x] == 0 && A.map[y + 3][x + 1] == 0 && A.map[y + 3][x + 2] == 0)return true; return false;
        case 1:
        case 3:if (A.map[y + 2][x + 2] == 0 && A.map[y + 3][x + 1] == 0)return true; return false;
        }
    }
    if (type == 4)
    {
        switch (state)
        {
        case 0:
        case 2:if (A.map[y + 2][x + 2] == 0 && A.map[y + 3][x] == 0 && A.map[y + 3][x + 1] == 0)return true; return false;
        case 1:
        case 3:if (A.map[y + 2][x + 1] == 0 && A.map[y + 3][x + 2] == 0)return true; return false;
        }
    }
    if (type == 5)
    {
        switch (state)
        {
        case 0:
        case 2:if (A.map[y + 3][x] == 0 && A.map[y + 3][x + 1] == 0 && A.map[y + 3][x + 2] == 0 && A.map[y + 3][x + 3] == 0)return true; return false;
        case 1:
        case 3:if (A.map[y + 4][x + 2] == 0)return true; return false;
        }
    }
    if (type == 6)
    {
        if (A.map[y + 2][x] == 0 && A.map[y + 2][x + 1] == 0)return true; return false;
    }
}

bool Block::JudgeTransform(Map A)
{
    if (type == 0)
    {
        switch (state)
        {
        case 0:if (A.map[y][x] == 0 && A.map[y][x + 1] == 0 && A.map[y + 2][x + 1] == 0)return true; return false;
        case 1:if (A.map[y + 2][x] == 0 && A.map[y + 2][x + 2] == 0 && A.map[y + 1][x + 2] == 0)return true; return false;
        case 2:if (A.map[y + 1][x + 1] == 0 && A.map[y][x + 1] == 0)return true; return false;
        case 3:if (A.map[y + 1][x] == 0 && A.map[y + 2][x] == 0 && A.map[y + 1][x + 2] == 0)return true; return false;
        }
    }
    if (type == 1)
    {
        switch (state)
        {
        case 0:if (A.map[y][x + 1] == 0 && A.map[y + 2][x] == 0 && A.map[y + 2][x + 1] == 0)return true; return false;
        case 1:if (A.map[y + 2][x + 2] == 0 && A.map[y + 1][x] == 0)return true; return false;
        case 2:if (A.map[y][x + 1] == 0 && A.map[y][x + 2] == 0 && A.map[y + 1][x + 1] == 0)return true; return false;
        case 3:if (A.map[y + 1][x] == 0 && A.map[y + 1][x + 2] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        }
    }
    if (type == 2)
    {
        switch (state)
        {
        case 0:if (A.map[y][x + 1] == 0 && A.map[y + 1][x + 2] == 0)return true; return false;
        case 1:if (A.map[y + 1][x] == 0)return true; return false;
        case 2:if (A.map[y][x + 1] == 0)return true; return false;
        case 3:if (A.map[y + 2][x] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        }
    }
    if (type == 3)
    {
        switch (state)
        {
        case 0:
        case 2:if (A.map[y][x + 2] == 0 && A.map[y + 1][x + 2] == 0)return true; return false;
        case 1:
        case 3:if (A.map[y + 1][x] == 0 && A.map[y + 2][x + 2] == 0)return true; return false;
        }
    }
    if (type == 4)
    {
        switch (state)
        {
        case 0:
        case 2:if (A.map[y + 2][x + 2] == 0 && A.map[y][x + 1] == 0)return true; return false;
        case 1:
        case 3:if (A.map[y + 2][x] == 0 && A.map[y + 2][x + 1] == 0)return true; return false;
        }
    }
    if (type == 5)
    {
        switch (state)
        {
        case 0:
        case 2:if (A.map[y][x + 2] == 0 && A.map[y + 1][x + 2] == 0 && A.map[y + 3][x + 2] == 0)return true; return false;
        case 1:
        case 3:if (A.map[y + 2][x] == 0 && A.map[y + 2][x + 1] == 0 && A.map[y + 2][x + 3] == 0)return true; return false;
        }
    }
    if (type == 6)
    {
        return true;
    }
}

void Block::Down(Map A) {
    if (JudgeDown(A)) {
        clearBlock(A.x);
        y++;
        DrawBlock(A.x);
    }
}

void Block::Move_Transform(Map A, int player) {
    if (player == 1) {
        if ((GetAsyncKeyState(0x41) & 0x8000)) {
            if (JudgeLeft(A)) {
                clearBlock(A.x);
                x--;
                DrawBlock(A.x);
            }
        }
        if ((GetAsyncKeyState(0x44) & 0x8000)) {
            if (JudgeRight(A)) {
                clearBlock(A.x);
                x++;
                DrawBlock(A.x);
            }
        }
        if ((GetAsyncKeyState(0x53) & 0x8000)) {
            if (JudgeDown(A)) {
                clearBlock(A.x);
                y++;
                DrawBlock(A.x);
            }
        }
        if ((GetAsyncKeyState(0x57) & 0x8000)) {
            if (JudgeTransform(A)) {
                clearBlock(A.x);

                state++;
                if (state > 3) {
                    state = 0;
                }
                memcpy(shape, all_block[type][state], 16 * sizeof(int));

                DrawBlock(A.x);
            }
        }
    }
    if (player == 2) {
        if ((GetAsyncKeyState(VK_LEFT) & 0x8000)) {
            if (JudgeLeft(A)) {
                clearBlock(A.x);
                x--;
                DrawBlock(A.x);
            }
        }
        if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
            if (JudgeRight(A)) {
                clearBlock(A.x);
                x++;
                DrawBlock(A.x);
            }
        }
        if ((GetAsyncKeyState(VK_DOWN) & 0x8000)) {
            if (JudgeDown(A)) {
                clearBlock(A.x);
                y++;
                DrawBlock(A.x);
            }
        }
        if ((GetAsyncKeyState(VK_UP) & 0x8000)) {
            if (JudgeTransform(A)) {
                clearBlock(A.x);

                state++;
                if (state > 3) {
                    state = 0;
                }
                memcpy(shape, all_block[type][state], 16 * sizeof(int));

                DrawBlock(A.x);
            }
        }
    }
}


