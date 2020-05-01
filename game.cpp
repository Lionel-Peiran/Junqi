#include <iostream>
#include <vector>
#include <cassert>
#include "game.h"

/*
input: 
	_Board	����״̬
	_State	ִ�ӷ�

function:
	���ɺ�������ʼ�����̺�ִ��״̬
*/
Game::Game(Chess _Board, int _State)
{
	Board = _Board;
	State = _State;
}

/*
input:
	depth	�������

output: 
	Move	��������

function:
	��������ȷ���������ӷ���
*/
Movement Game::Search(int depth)
{
	Movement Move;
	int alpha = -INF;
	int beta = INF;
	Search_Returns Ret = _Search(Board, depth, alpha, beta, PlayerType::MaximizingPlayer, State);
	if (!Ret.Move_His.empty())
		Move = Ret.Move_His.back();
	else
		assert(false);
	return Move;
}

/*
input:
	State	ִ�ӷ�

output:
	Oppte	����ִ�ӷ�

function:
	���ؽ���ִ��״̬
*/
static int Oppsite_State(int State)
{
	int Opp_State = 0;

	/* NEED CODE */

	return Opp_State;
}

/*
input:
	Cur_Board	��ǰ����
	Depth		��ǰ���
	Alpha		Alpha����
	Beta		Beta����
	Player		PlayerType MaximizingPlayer/MinimizingPlayer
	State		ִ�ӷ�

output:
	Search_Returns	_Search��������ֵ			
		Eval		��ǰ��ֵ
		Move_His	��ǰ���ŵ��ƶ�·��

function:
	����mimmax��������ʹ��alpha-beta��֦���������ŵ�����·���������ŵĽ�
*/
Search_Returns Game::_Search(Chess Cur_Board, int Depth, int Alpha, int Beta, PlayerType Player, int State)
{
	if (Depth == 0 || Is_Over(Cur_Board, State))
	{
		return Search_Returns(Evaluate_Chess(Cur_Board), std::vector<Movement>());
	}

	if (Player == PlayerType::MaximizingPlayer)
	{
		int Max_Eval = -INF;
		std::vector<Movement> Best_Move;
		std::vector<Movement> Move = Search_Movement(Cur_Board, State);
		for (std::vector<Movement>::iterator iter = Move.begin(); iter != Move.end(); iter++)
		{
			Movement V = *iter;
			Chess Next_Board = Apply_Move(Cur_Board, V);
			Search_Returns Ret = _Search(Next_Board, Depth - 1, Alpha, Beta, PlayerType::MinimizingPlayer, Oppsite_State(State));
			
			if (Ret.Eval > Max_Eval)
			{
				Max_Eval = Ret.Eval;
				Best_Move = Ret.Move_His;
				Best_Move.push_back(V);
				
				Alpha = (Ret.Eval > Alpha) ? Ret.Eval : Alpha;
				if (Beta <= Alpha)
					break;
			}
		}
		return Search_Returns(Max_Eval, Best_Move);
	}
	if (Player == PlayerType::MinimizingPlayer)
	{
		int Min_Eval = INF;
		std::vector<Movement> Best_Move;
		std::vector<Movement> Move = Search_Movement(Cur_Board, State);
		for (std::vector<Movement>::iterator iter = Move.begin(); iter != Move.end(); iter++)
		{
			Movement V = *iter;
			Chess Next_Board = Apply_Move(Cur_Board, V);
			Search_Returns Ret = _Search(Next_Board, Depth - 1, Alpha, Beta, PlayerType::MaximizingPlayer, Oppsite_State(State));
			
			if (Ret.Eval < Min_Eval)
			{
				Min_Eval = Ret.Eval;
				Best_Move = Ret.Move_His;
				Best_Move.push_back(V);
				
				Beta = (Ret.Eval < Beta) ? Ret.Eval : Beta;
				if (Beta <= Alpha)
					break;
			}
		}
		return Search_Returns(Min_Eval, Best_Move);
	}
	
	
	//	non-existent situation
	assert(false);
	return Search_Returns(0, std::vector<Movement>());
}


/*
input:
	Cur_Board	��������
	State	ִ�巽
		State == STATE_UPPER	��ʾִ�巽Ϊ��д�����Ϸ�
		State == STATE_LOWER	��ʾִ�巽ΪСд�����·�

output:
	true/false	��ǰִ�巽�������/�������

function:
	�жϵ�ǰִ�ӷ��Ƿ��������
*/

bool Game::Is_Over(const Chess& Cur_Board, const int& State)
{
	/* NEED CODE */
	return bool();
}

/*
input:
	Cur_Board	��������

output:
	Weight������Ȩ�أ� Сд������Ȩ�ؼ�ȥ��д������Ȩ��
	Weight = Weigh_lower - Weight_upper
	��ÿ�����ӽ��и�Ȩ������������и�ֵ��

function:
	�����̵���������
*/
int Game::Evaluate_Chess(const Chess& Cur_Board)
{
	/* NEED CODE */
	return 0;
}

/*
input:
	Cur_Board	��������
	State	ִ�巽
		State == STATE_UPPER	��ʾִ�巽Ϊ��д�����Ϸ�
		State == STATE_LOWER	��ʾִ�巽ΪСд�����·�

output:
	Move ��ʾÿ�����е�Movement���洢��vector��

function:
	Ѱ�������������ų�ֵ�����ռ�
*/
std::vector<Movement> Game::Search_Movement(const Chess& Board, const int& State)
{
	std::vector<Movement> Move;
	Move.clear();

	/* NEED CODE */

	return Move;
}

/*
input:
	Cur_Board	��������
	Move		���巽��

output:
	Board		����֮�������

function:
	ͨ��Move������������
*/

Chess Game::Apply_Move(const Chess& Cur_Board, const Movement& V)
{
	Chess Next_Board;

	/* NEED CODE */

	return Next_Board;
}


/*
function:
	���ӻ�����Ч������-+|��ʾ���ɣ���Ҫ���ڵ��ԡ�

*/
void Chess::Display()
{

}
