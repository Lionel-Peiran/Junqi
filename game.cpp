#include <iostream>
#include <vector>
#include <cassert>
#include "game.h"
#include "connect.h"
#include "zobrist.h"

const int ROLE_UPPER = 1;
const int ROLE_LOWER = 0;
const int ROLE_BLANK = -1;

/*
input:
����: Junqi.exe �C-role 1 �C-time 60
	ע�� ����role��0��ʾ�췽��1��ʾ�ڷ���
		����time����ʾ��������ʱ�䣬��λ�롣

output:

function:
	����Game���е�Role��Time_Limit
*/

void Game::Arg_Init(int argc, char* argv[])
{
	Role = atoi(argv[2]);
	Time_Limit = atoi(argv[4]);
}


/*
input:
	depth	�������

output:
	Move	�������ӷ���

function:
	��������ȷ���������ӷ���
*/
Movement Game::Search(Chess Board, int Depth)
{

	int alpha = -INF;
	int beta = INF;
	//	init Zobrist
	Zobrist Zob;
	ull Zob_Chess = Zob.Evaluate_Chess(Board);
	Eval_Move Ret = _Search(Board, Depth, alpha, beta, PlayerType::MaximizingPlayer, Role, Zob, Zob_Chess);


	return Ret.second.back();
}



/*
input:
	Cur_Role	ִ�ӷ�

output:
	Opp_Role	����ִ�ӷ�

function:

	���ؽ���ִ��״̬
*/

static int Oppsite_Role(int Cur_Role)
{
	int Opp_Role = 0;

	if (!Cur_Role)
		Opp_Role = 1;

	return Opp_Role;
}

/*
input:
	Cur_Board	��ǰ����
	Depth		��ǰ���
	Alpha		Alpha����
	Beta		Beta����
	Player		PlayerType MaximizingPlayer/MinimizingPlayer
	Cur_Role	ִ�ӷ�

output:
	Eval_Move		_Search��������ֵ
		Eval		��ǰ��ֵ
		Move_His	��ǰ���ŵ��ƶ�·��

function:
	����mimmax��������ʹ��alpha-beta��֦���������ŵ�����·���������ŵĽ�
*/
Eval_Move Game::_Search(Chess Cur_Board, int Depth, int Alpha, int Beta, PlayerType Player, int Cur_Role, const Zobrist& Zob, ull Cur_Zob)
{
	//	Zob.Search_State(Cur_Zob) != -1 means exist state
	if (Zob.Search_State(Cur_Zob) != -1)
	{
		return std::make_pair(Zob.Search_State(Cur_Zob), std::vector<Movement>());
	}
	if (Depth == 0 || Cur_Board.Is_Over(Cur_Role))
	{
		//	Eval����ʼ�շ��صĻ���ִ�ӷ������Ž�
		return std::make_pair(Cur_Board.Evaluate_Chess(this->Role), std::vector<Movement>());
	}
	//	std::cout << "Depth" << Depth << "Alpha" << Alpha << "Beta" << Beta << std::endl;
	//	���󻯵�ǰEval��Player
	if (Player == PlayerType::MaximizingPlayer)
	{
		int Max_Eval = -INF;
		std::vector<Movement> Best_Move;
		std::vector<Movement> Move = Cur_Board.Search_Movement(Cur_Role, Player);

		for (std::vector<Movement>::iterator iter = Move.begin(); iter != Move.end(); iter++)
		{
			Movement V = *iter;
			//	Con.Send_Move(V);������
			Chess Next_Board = Cur_Board.Apply_Move(V);
			ull Next_Zob = Zob.Apply_Move(Cur_Board, V, Cur_Zob);
			Eval_Move Ret = _Search(Next_Board, Depth - 1, Alpha, Beta, PlayerType::MinimizingPlayer, Oppsite_Role(Cur_Role), Zob, Next_Zob);

			int Eval = Ret.first;
			std::vector<Movement> Move_His = Ret.second;

			Zob.Record_State(Next_Zob, Eval);
			
			if (Depth == SEARCH_DEPTH)
			{
#ifdef DEBUG
				std::cout << "Depth == " << SEARCH_DEPTH << " " << (char)('A' + 12 - V.From.x) << V.From.y << " " << (char)('A' + 12 - V.To.x) << V.To.y << " Eval:" << Eval << " Heur Eval:" << Next_Board.Evaluate_Chess(Cur_Role) << std::endl;;
				//getchar(); getchar();
				//Cur_Board.Display();
#endif // DEBUG
			}


			if (Eval > Max_Eval)
			{
				Max_Eval = Eval;
				Best_Move = Move_His;
				Best_Move.push_back(V);

				Alpha = (Eval > Alpha) ? Eval : Alpha;
				if (Beta <= Alpha)
					break;
			}
		}
		return std::make_pair(Max_Eval, Best_Move);
	}
	//	��С����ǰEval��Player
	if (Player == PlayerType::MinimizingPlayer)
	{
		int Min_Eval = INF;
		std::vector<Movement> Best_Move;
		std::vector<Movement> Move = Cur_Board.Search_Movement(Cur_Role, Player);

		for (std::vector<Movement>::iterator iter = Move.begin(); iter != Move.end(); iter++)
		{
			Movement V = *iter;
			//	Con.Send_Move(V);������
			Chess Next_Board = Cur_Board.Apply_Move(V);
			ull Next_Zob = Zob.Apply_Move(Cur_Board, V, Cur_Zob);
			Eval_Move Ret = _Search(Next_Board, Depth - 1, Alpha, Beta, PlayerType::MaximizingPlayer, Oppsite_Role(Cur_Role), Zob, Next_Zob);

			int Eval = Ret.first;
			std::vector<Movement> Move_His = Ret.second;
			Zob.Record_State(Next_Zob, Eval);


			if (Eval < Min_Eval)
			{
				Min_Eval = Eval;
				Best_Move = Move_His;
				Best_Move.push_back(V);

				Beta = (Eval < Beta) ? Eval : Beta;
				if (Beta <= Alpha)
					break;
			}
		}
		return std::make_pair(Min_Eval, Best_Move);
	}


	//	non-existent situation
	assert(false);
	return std::make_pair(0, std::vector<Movement>());
}


