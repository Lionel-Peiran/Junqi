#pragma once
#include "game.h"


/*
��������ڽ���֮��Ľ�������
*/
class Connect
{
public:
	void Init();
	Chess Get_NCN(int& State);
	void Send_NCN(const Movement& Move);
};