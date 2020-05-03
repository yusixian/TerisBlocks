#include "funtion.h"
DWORD oldtime = 0;
Player p1;
void init() {
	initgraph(420, 545);
	srand((unsigned)time(NULL));  //初始化随机数种子
	setbkcolor(BKCOLOR);		  //设置背景色
	setbkmode(TRANSPARENT);		  // 设置图案填充的背景色为透明
	cleardevice();				  //用当前背景色清屏

	// 显示操作说明
	setcolor(0x000000);
	settextstyle(20, 0, _T("幼圆"));
	outtextxy(295, 130, _T("下一个方块"));

	outtextxy(300, 355, _T("操作说明："));
	outtextxy(300, 380, _T("上：旋转"));
	outtextxy(300, 405, _T("左：左移"));
	outtextxy(300, 430, _T("右：右移"));
	outtextxy(300, 455, _T("下：下移"));
	outtextxy(300, 480, _T("空格：沉底"));
	outtextxy(300, 505, _T("ESC：退出"));
	outtextxy(315, 200, _T("当前分数"));
	// 设置坐标原点
	setorigin(20, 20);

	// 绘制游戏区边界
	rectangle(-1, -1, WIDTH * UNIT + 2, HEIGHT * UNIT + 2);
	rectangle((WIDTH + 1) * UNIT, 0, (WIDTH + 5) * UNIT, 4 * UNIT);
	// for (int i = 1; i <= 20; i++) {
	// 	line(0, i * UNIT, 10 * UNIT, i * UNIT);//绘制游戏界面横线
	// }
	// for (int i = 1; i <= 10; i++) {
	// 	line(i * UNIT, 0, i * UNIT, 20 * UNIT);//绘制游戏界面竖线
	// }
	// for (int i = 1; i <= 4; i++) {
	// 	line((WIDTH + 1) * UNIT, i * UNIT, (WIDTH + 5) * UNIT, i *
	// UNIT);//绘制预览界面横线 	line((WIDTH + 1 + i)* UNIT, 0, (WIDTH + 1 +
	// i)
	// * UNIT, 4 * UNIT);//绘制预览界面竖线
	// }
	// Draw_NewBlock();
	p1.update_score();
	New_Game();
}
void New_Game() {
	srand((unsigned)time(NULL));  //初始化随机数种子
	setfillcolor(BKCOLOR);
	solidrectangle(0, 0, WIDTH * UNIT, HEIGHT * UNIT);
	memset(blocks_maps, 0, sizeof(blocks_maps));
	p1.clear_score();
	p1.update_score();
	next_block.id = rand() % 7;
	next_block.direction = rand() % 4;
	next_block.x = 11;
	next_block.y = 0;
	New_Block();
}
bool Check_Block(BLOCK block) {
	int d = block.get_nowTB();	//获取以16进制存储的当前俄罗斯方块的信息
	for (int i = 0; i < 16; i++, d <<= 1) {
		if (d & 0x8000) {  //取出每一位，若为1则检查该位置方块
			int ux = block.x + i % 4;
			int uy = block.y + i / 4;
			if (ux < 0 || ux >= WIDTH || uy >= HEIGHT)	//坐标不合法
				return false;
			if (uy >= 0 &&
				blocks_maps[ux][uy] == 1)  //坐标合法，该位置有方块了则也不行
				return false;
		}
	}
	return true;
}
void Edit_UnitBlock(int x, int y, COLORREF col, Editmode mode) {
	int right = (x + 1) * UNIT;
	int bottom = (y + 1) * UNIT;
	int left = right - UNIT;
	int top = bottom - UNIT;
	switch (mode) {
		case DRAW:
			setlinecolor(0x000000);	 //不固定的用黑线描边
			roundrect(left, top, right, bottom, 8, 8);
			setfillcolor(col);
			solidroundrect(left + 2, top + 2, right - 2, bottom - 2, 5, 5);
			break;
		case CLEAR:
			setfillcolor(BKCOLOR);
			solidrectangle(left, top, right, bottom);
			break;
		case FIX:
			setlinecolor(0xc0c0c0);	 //固定的用银线描边
			roundrect(left, top, right, bottom, 8, 8);
			setfillcolor(col);
			solidroundrect(left + 2, top + 2, right - 2, bottom - 2, 5, 5);
			break;
		default: break;
	}
}
void Edit_Block(BLOCK block, Editmode mode) {
	int d = block.get_nowTB();	//获取以16进制存储的当前俄罗斯方块的信息
	for (int i = 0; i < 16; i++, d <<= 1) {
		if (d & 0x8000) {  //取出每一位，若为1则绘制该位置方块
			int ux = block.x + i % 4;
			int uy = block.y + i / 4;
			if (uy >= 0)
				Edit_UnitBlock(ux, uy, block.get_nowcol(), mode);
		}
	}
}
void Avoid_Repeat() {
	int id = next_block.id;
	next_block.T_Blocks[id].occurence;
	while (next_block.T_Blocks[id].occurence >= 2) {
		next_block.id = rand() % 7;
		next_block.direction = rand() % 4;
		if (next_block.id == id)
			continue;
	}
	next_block.T_Blocks[id].occurence = 0;
}
void New_Block() {	//创建新方块 将当前方块置为下一个方块 再随机获取下一个方块
	now_block.direction = next_block.direction;
	now_block.id = next_block.id;
	now_block.x = 3, now_block.y = -3;
	next_block.x = 11, next_block.y = 0;
	next_block.id = rand() % 7;
	next_block.direction = rand() % 4;
	Avoid_Repeat();
	int b = now_block.get_nowTB();
	while ((b & 0xF) == 0) {  //当最下边那排没有方块时，下移 直至有局部显示
		now_block.y++;
		b >>= 4;
	}
	//绘制当前方块
	Edit_Block(now_block);
	//绘制预览区方块
	setfillcolor(BKCOLOR);
	solidrectangle((WIDTH + 1) * UNIT + 1, 1, (WIDTH + 5) * UNIT - 1,
				   4 * UNIT - 1);  //覆盖上一次的方块
	Edit_Block(next_block);
}
CMD Get_CMD() {
	while (1) {
		DWORD newtime = GetTickCount();	 //获取新时间
		if (newtime - oldtime >= 500) {	 //时间间隔大于500ms了则下落一格
			oldtime = newtime;
			return DOWN;
		}
		if (_kbhit()) {	 //若有键盘按键，则返回真
			switch (_getch()) {
				case 'w':
				case 'W': return ROTATE;
				case 's':
				case 'S': return DOWN;
				case 'a':
				case 'A': return LEFT;
				case 'd':
				case 'D': return RIGHT;
				case ' ': return SINK;	//快速下沉
				case 27: return ESC;	// ESC键
				case 0:	 //读取功能键或别的键时，_getch()第一次返回0或0xE0，第二次返回对应键值。
				case 0xE0:
					switch (_getch()) {
						case 72: return ROTATE;	 //↑
						case 80: return DOWN;	 //↓
						case 75: return LEFT;	 //←
						case 77: return RIGHT;	 //→
					}
			}
		}
		Sleep(30);
	}
}
void Deal_with(CMD c) {
	switch (c) {
		case ROTATE: CMD_ROTATE(); break;
		case DOWN: CMD_DOWN(); break;
		case LEFT: CMD_LEFT(); break;
		case RIGHT: CMD_RIGHT(); break;
		case SINK: CMD_SINK(); break;
		case ESC: break;
	}
}
void Fix_BLOCK(BLOCK block) {
	int d = block.get_nowTB();	//获取以16进制存储的当前俄罗斯方块的信息
	for (int i = 0; i < 16; i++, d <<= 1) {
		if (d & 0x8000) {  //取出每一位，若为1则标记该位置方块
			int ux = block.x + i % 4;
			int uy = block.y + i / 4;
			if (uy <= 0) {	//固定方块的高度超过游戏界面高度
				Game_Over();
				return;
			}
			else
				blocks_maps[ux][uy] = 1;
		}
	}
}
void Quit() {
	closegraph();
	exit(0);
}
void Game_Over() {
	HWND wnd = GetHWnd();
	if (MessageBox(wnd, _T("游戏结束\n是否重新开始游戏？"), _T("提示"),
				   MB_YESNO | MB_ICONQUESTION) == IDYES)
		New_Game();
	else
		Quit();
}
void Rotate(int dir, int dx) {
	Edit_Block(now_block, CLEAR);
	now_block.direction = dir;
	now_block.x += dx;
	Edit_Block(now_block);
}
void CMD_ROTATE() {
	BLOCK temp = now_block;
	int dx = 0;
	temp.direction++;
	temp.direction %= 4;
	if (Check_Block(temp)) {
		Rotate(temp.direction, dx);
		return;
	}
	temp.x = now_block.x - 1;
	if (Check_Block(temp)) {
		dx = -1;
		Rotate(temp.direction, dx);
		return;
	}
	temp.x = now_block.x + 1;
	if (Check_Block(temp)) {
		dx = 1;
		Rotate(temp.direction, dx);
		return;
	}
	temp.x = now_block.x - 2;
	if (Check_Block(temp)) {
		dx = -2;
		Rotate(temp.direction, dx);
		return;
	}
	temp.x = now_block.x + 2;
	if (Check_Block(temp)) {
		dx = 2;
		Rotate(temp.direction, dx);
		return;
	}
}
void CMD_DOWN() {
	BLOCK temp = now_block;
	temp.y++;
	if (Check_Block(temp)) {
		Edit_Block(now_block, CLEAR);
		Edit_Block(temp);
		now_block = temp;
	}
	else
		CMD_SINK();
}
void CMD_LEFT() {
	BLOCK temp = now_block;
	temp.x--;
	if (Check_Block(temp)) {
		Edit_Block(now_block, CLEAR);
		now_block = temp;
		Edit_Block(now_block);
	}
}
void CMD_RIGHT() {
	BLOCK temp = now_block;
	temp.x++;
	if (Check_Block(temp)) {
		Edit_Block(now_block, CLEAR);
		now_block = temp;
		Edit_Block(now_block);
	}
}
void CMD_SINK() {
	//擦除当前方块
	Edit_Block(now_block, CLEAR);
	BLOCK temp = now_block;
	temp.y++;
	while (Check_Block(temp)) {	 //下移当前方块直到不能再下移
		now_block.y++;
		temp.y++;
	}
	//固定并绘制当前方块
	Edit_Block(now_block, FIX);
	Fix_BLOCK(now_block);
	//检测是否有要消除的行（一次最多消除4行）
	bool flag = false;
	bool line[4] = {false};	 //标记方块涉及的四行是否被消除
	int combo = 0;
	for (int i = 0; i < 4; i++) {  //从上到下 标记该行是否被消除
		int y = now_block.y + i;
		int cnt = 0;
		for (int x = 0; x < WIDTH; x++) {
			if (blocks_maps[x][y] == 1)
				cnt++;
		}
		if (cnt == WIDTH) {	 //该行需要被消除
			combo++;
			flag = true;
			line[i] = true;
			setfillcolor(LIGHTGREEN);
			setlinecolor(LIGHTGREEN);
			setfillstyle(BS_HATCHED, HS_BDIAGONAL);
			solidrectangle(0, y * UNIT, WIDTH * UNIT, (y + 1) * UNIT);
			setfillstyle(BS_SOLID);
		}
	}
	if (flag) {	 //消除~
		p1.plus_score(combo);
		Sleep(250);
		IMAGE img;
		for (int i = 0; i < 4; i++) {
			if (line[i]) {	//该行需要被消除，从当前行上一行开始，将下一行变成该行的标志，后清空该行
				for (int y = now_block.y + i - 1; y > 0; y--) {
					for (int x = 0; x < WIDTH; x++) {
						blocks_maps[x][y + 1] = blocks_maps[x][y];
						blocks_maps[x][y] = 0;
					}
				}
				getimage(&img, 0, 0, WIDTH * UNIT, (now_block.y + i) * UNIT);
				putimage(0, UNIT, &img);
			}
		}
	}
	p1.update_score();
	//产生新方块
	New_Block();
}