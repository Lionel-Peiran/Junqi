#pragma once
#include <vector>
#include "game.h"

//	���̵Ĵ�С
static const int Chess_H = 13;
static const int Chess_W = 5;
const char blank = ' ';
const char RANK[10] = "AJSVTYLPG";//��������

#define SAME_RANK 0
#define ABOVE 1
#define UNDER -1

/*
�洢��ʽ����Word��һ���������ô�д��������Сд��
*/
class Chess
{
private:
	std::vector<std::vector<char> >  Board;
	int Rank_Judgement(char a, char b);
public:
	Chess()
	{
		Board.resize(Chess_H);
		for (int i = 0; i < Chess_H; i++)
			Board[i].resize(Chess_W);
	}

	bool Is_Over(const int& Role);
	int Evaluate_Chess(const int& Role);
	std::vector<Movement>  Search_Movement(const int& State);
	Chess Apply_Move(const Movement& V);
	void Display();
};



//	��·λ��
const int Railway[Chess_H][Chess_W]{
	{0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1},
	{1, 0, 1, 0, 1},
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0}
};

//	˾��*1������*1��ʦ��*2���ó�*2���ų�*2��Ӫ��*2������*3���ų�*3������*3������*3��ը��*2������*1�� ��25ö

