#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<string>
#include<graphics.h>
#include<conio.h>
#include"Map.h"
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

