#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<string>
#include<graphics.h>
#include<conio.h>
#include"Map.h"
#include"Block.h"

#define MAXY 24
#define MAXX 15
#define LEN 18
using namespace std;

Map::Map(int xx, int yy) {
	x = xx;
	y = yy;
	memset(map, 0, sizeof(map));
	for (int i = 0; i < MAXY; i++) {
		map[i][0] = 1;
	}
	for (int i = 0; i < MAXY; i++) {
		map[i][MAXX - 1] = 1;
	}
	for (int i = 1; i < MAXX - 1; i++) {
		map[MAXY - 1][i] = 1;
	}

}

void Map::DrawMap() {
	setfillcolor(WHITE);
	for (int i = 0; i < MAXY; i++) {
		for (int j = 0; j < MAXX; j++) {
			if (map[i][j] == 1) {
				int xx = x + j * (LEN + 3);		//这里的+3是预留了每个小方块之间的间距
				int yy = y + i * (LEN + 3);
				solidrectangle(xx, yy, xx + LEN, yy + LEN);
			}
		}
	}
}

void Map::clearMap() {
	setfillcolor(BLACK);
	for (int i = 0; i < MAXY; i++) {
		for (int j = 0; j < MAXX; j++) {
			int xx = x + j * (LEN + 3);		//这里的+3是预留了每个小方块之间的间距
			int yy = y + i * (LEN + 3);
			solidrectangle(xx, yy, xx + LEN, yy + LEN);
		}
	}
}

int Map::Clear_Line() {
	int cnt = 0;
	for (int i = 1; i < MAXY - 1; i++) {
		int flag = 1;
		for (int j = 1; j < MAXX - 1; j++) {
			if (map[i][j] == 0) {
				flag = 0;
				break;
			}
		}

		if (flag == 1) {
			for (int yy = i; yy > 0; yy--) {
				for (int j = 1; j < MAXX - 1; j++) {
					map[yy][j] = map[yy - 1][j];
				}
			}
			cnt++;
		}
	}
	return cnt;
}

int Map::getTop() {
	int top;					
	for (top = 0; top < MAXY - 1; top++) {
		for (int j = 1; j < MAXX - 1; j++) {
			if (map[top][j] == 1) {
				return top;
			}
		}
	}
}

void Map::Add_line(int cnt) {
	int top = getTop();

	while (cnt-- && top > 0) {
		for (int i = top - 1; i < MAXY - 2; i++) {
			for (int j = 1; j < MAXX - 1; j++) {
				map[i][j] = map[i + 1][j];
			}
		}
		top--;

		int flag = 0;		//用于判断，以防出现生成空行的情况
		int j = 2;
		while (!flag) {
			for (int i = 1; i < MAXX - 1; i++) {
				map[MAXY - j][i] = rand() % 2;
				if (map[MAXY - j][i]) {
					flag = 1;
				}
			}
		}
		j++;

	}
}

bool Map::judgeOver() {
	if (getTop()) {
		return true;
	}
	return false;
}


int Map::Clear_update() {
	clearMap();
	int cnt = Clear_Line();
	DrawMap();
	return cnt;
}
void Map::Add_update(int cnt) {
	clearMap();
	Add_line(cnt);
	DrawMap();
}


