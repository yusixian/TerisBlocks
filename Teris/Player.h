#pragma once
#pragma warning(disable : 4996)
#ifndef _PLAYER_H
#define _PLAYER_H
#include <cstdio>
#include <easyx.h>
#include <graphics.h>
class Player {
public:
	Player() : username(nullptr),password(0),score(0) {}//Ĭ�Ϲ��캯��
	~Player() { if (username) delete username; }
	int get_score() { return score; }
	void update_score();	//������Ļ����ʾ�ķ�����
	void clear_score();
	void plus_score(int combo);//�����������ӷ� ��������Ч
private:
	char* username;
	int password;
	int score;
};
#endif