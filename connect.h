#pragma once
#include "game.h"


/*
��������ڽ���֮��Ľ�������
*/
class Connect
{
public:
	void Init();
	int Get_Board(Chess &Board);
	void Send_Move(const Movement& Move);
};