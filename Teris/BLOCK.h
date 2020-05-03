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
	int dir[4];	 //以16进制存储的该种俄罗斯方块的四个方向上的信息
	COLORREF col;  //该种俄罗斯方块的颜色
	int occurence;
};
struct BLOCK {
	int x, y;
	int id;			//当前方块编号 0表示I型方块
	int direction;	//当前方块状态编号
	static Teris_BLOCK T_Blocks[7];
	int get_nowTB();  //获取以16进制存储的当前俄罗斯方块的信息
	COLORREF get_nowcol();
};
extern int blocks_maps[WIDTH][HEIGHT];
extern BLOCK now_block, next_block;

#endif