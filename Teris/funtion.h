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
enum Editmode {DRAW, CLEAR,FIX};//FIX��ʾ�Ѿ����׹̶��ķ��� ��Ե
enum CMD {ROTATE,DOWN,LEFT,RIGHT,SINK,ESC};
extern DWORD oldtime;
void init();//����Ϸ���ʼ���г�ʼ��
void New_Game();
void Edit_UnitBlock(int x, int y, COLORREF col, Editmode mode = DRAW);
//�༭����Ϸ����ĵ�Ԫ��1UNIT*1UNIT
bool Check_Block(BLOCK block);//���÷����Ƿ��ܷ�
void Edit_Block( BLOCK block, Editmode mode = DRAW);
//���ƶ���˹���飬ֻ�е�ǰ�����ܷ����Ҳ������ʱ����Ի���
void Avoid_Repeat();//��ֹ�����ظ������
void New_Block();
CMD Get_CMD();
void Deal_with(CMD c);
void Fix_BLOCK(BLOCK block);
void Rotate(int dir,int dx);
void CMD_ROTATE();	//��ת
void CMD_DOWN();//�³�
void CMD_LEFT();//����
void CMD_RIGHT();//����
void CMD_SINK();//����
void Quit();
void Game_Over();  //��Ϸ��������������
#endif
