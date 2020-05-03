#include "BLOCK.h"
int blocks_maps[WIDTH][HEIGHT] = {0};
BLOCK now_block, next_block;
Teris_BLOCK BLOCK::T_Blocks[7]{
	{0x4444, 0x0f00, 0x4444, 0x0f00, BLUE,0},		// I型方块 蓝色
	{0x2260, 0x0e20, 0x0644, 0x0470, MAGENTA,0},	// J型方块 橙色
	{0x4460, 0x02e0, 0x0622, 0x0740, RED,0},		// L型方块 红色
	{0x0660, 0x0660, 0x0660, 0x0660, YELLOW,0},	// 田型方块 黄色
	{0x0630, 0x2640, 0x0630, 0x2640, GREEN,0},	// Z型方块 绿色
	{0x06c0, 0x4620, 0x06c0, 0x4620, CYAN,0},		// 反Z型方块 青色
	{0x4e00, 0x4c40, 0x0e40, 0x4640, BROWN,0}		// T型方块 棕色
};
int BLOCK::get_nowTB() {
	return T_Blocks[id].dir[direction];
}
COLORREF BLOCK::get_nowcol() {
	return T_Blocks[id].col;
}