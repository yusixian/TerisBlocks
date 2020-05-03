#pragma once
#pragma warning(disable : 4996)
#ifndef _PLAYER_H
#define _PLAYER_H
#include <cstdio>
#include <easyx.h>
#include <graphics.h>
class Player {
public:
	Player() : username(nullptr),password(0),score(0) {}//默认构造函数
	~Player() { if (username) delete username; }
	int get_score() { return score; }
	void update_score();	//更新屏幕上显示的分数。
	void clear_score();
	void plus_score(int combo);//根据连击数加分 并播放音效
private:
	char* username;
	int password;
	int score;
};
#endif