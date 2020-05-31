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

int down = 0;       //控制自动下落的时间间隔

Block A, B;
Map P1_map(200, 0), P2_map(650, 0);   //两玩家的地图

void initial();     //初始画面
void textstyle();   //设置文字
void update_with_input();   //有输入的更新
void update_without_input();    //无输入的更新

int main()
{
    srand(time(0));

initial:
    initial();

    double y = 0;
    BeginBatchDraw();

    Block Next1, Next2;
    Next1.InitialBlock();
    Next2.InitialBlock();

    A.InitialBlock();

    while (1) {

        update_with_input();
        update_without_input();

        if (!A.JudgeDown(P1_map)) {
            A.down_control++;
            if (A.down_control == 7) {
                A.down_control = 0;
                fuse(P1_map, A);

                P2_map.Add_update(P1_map.Clear_update());

                A = Next1;
                Next1.InitialBlock();
            }
        }
        else {
            A.down_control = 0;
        }


        Next1.DrewNext(50,120);
        Next2.DrewNext(1050, 120);


        Sleep(120);

        FlushBatchDraw();

        A.clearNext(50, 120);
    }

end:
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
    A.Move_Transform(P1_map,1);
    Game::GameStop();
}

void update_without_input() {
    if (down == 0) {
        A.Down(P1_map);
    }
    down++;
    if (down > 8) {
        down = 0;
    }

    
}

void fuse(Map &M, Block &A) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (A.shape[i][j] == 1) {
                M.map[A.y + i][A.x + j] = 1;
            }
        }
    }
}
