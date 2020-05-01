#pragma once
#include <vector>

/*
State״̬	
STATE_END	��ʾ��ǰ���̽���
STATE_UPPER	��ǰִ�ӷ�Ϊ�ϲ������������еĴ�д����
STATE_LOWER	��ǰִ�ӷ�Ϊ�²������������е�Сд����
*/
const int STATE_END = -1;
const int STATE_UPPER = 1;
const int STATE_LOWER = 0;

//	���ڳ�ʼ�������ֵ
const int INF = 0x3f3f3f3f;

//	��������
class Coord
{
public:
	int x, y;
};

/*	
���ӵ��ƶ�·��
Coord From	��ʾ���ӵ���ʼλ��
Coord To	��ʾ���ӵ��յ�λ��
*/
class Movement
{
public:
	Coord From, To;
};


/*
_Search�����ķ���ֵ
Eval		��ֵ
Move_His	�ƶ�·��
*/
class Search_Returns
{
public:
	int Eval;
	std::vector<Movement> Move_His;
	Search_Returns(int _Eval, std::vector<Movement> _Move_His): Eval(_Eval), Move_His(_Move_His) {}
};

//	���̵Ĵ�С
static const int Chess_H = 13;
static const int Chess_W = 5;

/*
�洢��ʽ����Word��һ���������ô�д��������Сд��
*/
class Chess
{
public:
	std::vector<std::vector<char> >  Board;

	Chess()
	{
		Board.resize(Chess_H);
		for (int i = 0; i < Chess_H; i++)
			Board[i].resize(Chess_W);
	}
	
	void Display();
};

//	��minmax�����е��������
enum class PlayerType {
	MaximizingPlayer,
	MinimizingPlayer
};

class Game
{
protected:
	Chess Board;
	int State;
public:
	Game(Chess _Board, int _State);
	Movement Search(int depth = 5);
private:
	Search_Returns _Search(Chess Cur_Board, int depth, int alpha, int beta, PlayerType Player, int State);
	bool Is_Over(const Chess& Cur_Board, const int& State);
	int Evaluate_Chess(const Chess& Cur_Board);
	std::vector<Movement> Search_Movement(const Chess& Board, const int& State);
	Chess Apply_Move(const Chess& Cur_Board, const Movement& V);
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

