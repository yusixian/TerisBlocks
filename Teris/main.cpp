#include <iostream>
#include "Player.h"
#include "funtion.h"
using namespace std;
int main() {
	init();//初始化并开始一盘新游戏
	CMD c;
	while (1) {
		c = Get_CMD();
		Deal_with(c);
		if (c == ESC) {
			HWND wnd = GetHWnd();
			if (MessageBox(wnd, _T("您确认要退出游戏吗？"), _T("提示"), MB_YESNO | MB_ICONQUESTION) == IDYES)
				Quit();
		}
	}
	return 0;
}