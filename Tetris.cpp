#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<string>
#include<graphics.h>
#include<conio.h>
#include<Windows.h>

#include"Block.h"
#include"Game.h"
#include"Map.h"
#include"Game.h"

#define Width 1180
#define Hight 600
#define MAXY 24
#define MAXX 15
#define LEN 18
using namespace std;


Map P1_map(200, 0), P2_map(650, 0);   //两玩家的地图

void initial();     //初始画面
void textstyle();   //设置文字
void update_with_input();   //有输入的更新
void update_without_input();    //无输入的更新

int main()
{
    initial();

    double y = 0;
    BeginBatchDraw();

    while (1) {
        Block A,B;
        A.InitialBlock();

        A.DrawBlock(200);

        FlushBatchDraw();
        Sleep(8);

        A.clearBlock(200);
        update_with_input();


    }
    EndBatchDraw();
    getch();
    closegraph();
    return 0;
}


void initial() {
    initgraph(Width, Hight);    //设置背景
    setbkcolor(BLACK);
    cleardevice();

    P1_map.DrawMap();       //绘制初始地图
    P2_map.DrawMap();

    setcolor(WHITE);     //显示规则等
    setlinestyle(PS_SOLID, 4);
    rectangle(10, 10, 180, 500);
    rectangle(980, 10, 1160, 500);
    rectangle(200, 520, 960, 575);

    textstyle();
}

void textstyle() {
    settextcolor(WHITE);
    settextstyle(30, 0, _T("黑体"));
    outtextxy(60, 20, "玩家A");
    outtextxy(1030, 20, "玩家B");
    outtextxy(210, 530, "空格 : 开始/暂停");
    outtextxy(730, 530, "ESC : 退出");

    settextstyle(18, 0, _T("抗锯齿效果"));
    outtextxy(20, 65, "下一块:");
    outtextxy(990, 65, "下一块:");

    settextstyle(20, 13, _T("抗锯齿效果"));
    outtextxy(20, 300, "W : 旋转");
    outtextxy(20, 350, "S : 加速");
    outtextxy(20, 400, "A : 左移");
    outtextxy(20, 450, "D : 右移");
    outtextxy(990, 300, "↑ : 旋转");
    outtextxy(990, 350, "↓ : 加速");
    outtextxy(990, 400, "← : 左移");
    outtextxy(990, 450, "→ : 右移");
}

void update_with_input() {
    char input;
    if (kbhit()) {      // 暂停or开始
        input = getch();
        if (input == ' ') {
            Game::isStop = true;
            Game::GameStop();
        }
    }

}
