#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<string>
#include<graphics.h>
#include<conio.h>
#include<windows.h>

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

Map P1_map(200, 0), P2_map(650, 0);   //两玩家的地图
Block P1_Block, P2_Block, P1_Next, P2_Next;

void initial();     //初始画面
void textstyle();   //设置文字
void update_with_input();   //有输入的更新
void update_without_input();    //无输入的更新


int main()
{
    srand(time(0));
    initgraph(Width, Hight);    //设置背景

    if (!Game::Welcome()) {
        goto end;
    }

begin:
    initial();
    BeginBatchDraw();

    while (1) {

        update_with_input();
        update_without_input();
        if (!P1_map.getTop() || !P2_map.getTop()) {
            if (!Game::GameOver(P1_map)) {
                EndBatchDraw();
                goto begin;
            }
            else {
                goto end;
            }
        }

        Sleep(120);

        FlushBatchDraw();

        P1_Next.clearNext(50, 120);
        P2_Next.clearNext(1050, 120);
    }

end:
    settextcolor(WHITE);
    settextstyle(100, 0, _T("黑体"));
    outtextxy(500, 220, "Bye");
    EndBatchDraw();
    getch();
    closegraph();
    return 0;
}



void Drawgraph() {
    
    setbkcolor(BLACK);
    cleardevice();
}

void initial() {
    Game::clearScreen();

    P1_map = Map(200, 0);
    P2_map = Map(650, 0);
    P1_map.DrawMap();       //绘制初始地图
    P2_map.DrawMap();


    P1_Block.InitialBlock();    //初始化双方的方块
    P2_Block.InitialBlock();
    P1_Next.InitialBlock();
    P2_Next.InitialBlock();

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
    outtextxy(50, 20, "玩家P1");
    outtextxy(1025, 20, "玩家P2");
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
    P1_Block.Move_Transform(P1_map, 1);
    P2_Block.Move_Transform(P2_map, 2);
    Game::GameStop();
}

void update_add_clear(Block& A, Block& B, Block& Next1, Block& Next2, Map& P1, Map& P2) {
    if (!A.JudgeDown(P1)) {
        A.down_control++;
        if (A.down_control == 7) {
            A.down_control = 0;
            fuse(P1, A);

            P2.Add_update(P1.Clear_update());
            B.DrawBlock(P2.x);

            A = Next1;
            Next1.InitialBlock();
        }
    }
    else {
        A.down_control = 0;
    }
}

void update_without_input() {
    if (down == 0) {            //控制下落速度
        P1_Block.Down(P1_map);
        P2_Block.Down(P2_map);
    }
    down++;
    if (down > 8) {
        down = 0;
    }

    update_add_clear(P1_Block, P2_Block, P1_Next, P2_Next, P1_map, P2_map);
    update_add_clear(P2_Block, P1_Block, P2_Next, P1_Next, P2_map, P1_map);

    P1_Next.DrewNext(50, 120);
    P2_Next.DrewNext(1050, 120);
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
