#pragma once
#ifndef _FUNTION_H
#define _FUNTION_H
#include <easyx.h>
#include <graphics.h>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <conio.h>
#include "Player.h"
#include "BLOCK.h"
using namespace std;
#define BKCOLOR 0xf0faff

extern Player p1;
enum Editmode {DRAW, CLEAR,FIX};//FIX表示已经沉底固定的方块 边缘
enum CMD {ROTATE,DOWN,LEFT,RIGHT,SINK,ESC};
extern DWORD oldtime;
void init();//在游戏的最开始进行初始化
void New_Game();
void Edit_UnitBlock(int x, int y, COLORREF col, Editmode mode = DRAW);
//编辑主游戏界面的单元格1UNIT*1UNIT
bool Check_Block(BLOCK block);//检查该方块是否能放
void Edit_Block( BLOCK block, Editmode mode = DRAW);
//绘制俄罗斯方块，只有当前区域能放下且不出界的时候可以绘制
void Avoid_Repeat();//防止方块重复过多次
void New_Block();
CMD Get_CMD();
void Deal_with(CMD c);
void Fix_BLOCK(BLOCK block);
void Rotate(int dir,int dx);
void CMD_ROTATE();	//旋转
void CMD_DOWN();//下沉
void CMD_LEFT();//左移
void CMD_RIGHT();//右移
void CMD_SINK();//沉底
void Quit();
void Game_Over();  //游戏结束，进行清理
#endif
