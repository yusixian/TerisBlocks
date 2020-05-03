#pragma once
#ifndef _BLOCK_H
#define _BLOCK_H
#include <easyx.h>
#include <graphics.h>
#include <vector>
#define WIDTH 10
#define HEIGHT 20
#define UNIT 25
struct Teris_BLOCK {
	int dir[4];	 //��16���ƴ洢�ĸ��ֶ���˹������ĸ������ϵ���Ϣ
	COLORREF col;  //���ֶ���˹�������ɫ
	int occurence;
};
struct BLOCK {
	int x, y;
	int id;			//��ǰ������ 0��ʾI�ͷ���
	int direction;	//��ǰ����״̬���
	static Teris_BLOCK T_Blocks[7];
	int get_nowTB();  //��ȡ��16���ƴ洢�ĵ�ǰ����˹�������Ϣ
	COLORREF get_nowcol();
};
extern int blocks_maps[WIDTH][HEIGHT];
extern BLOCK now_block, next_block;

#endif