#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>
#include "game.h"
#include "connect.h"
#include "zobrist.h"

//#define ENABLE_ZOB
#define ENABLE_ALPHABETA

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

#ifdef DEBUG
	int begin_time = (int)time(0);
#endif // DEBUG

	Eval_Move Ret = _Search(Board, Depth, alpha, beta, PlayerType::MaximizingPlayer, Role, Zob, Zob_Chess);

#ifdef DEBUG
	int finish_time = (int)time(0);
	std::cout << "search time:" << finish_time - begin_time << std::endl;
	getchar();
	getchar();
#endif // DEBUG

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

	if (Depth == 0 || Cur_Board.Is_Over(Cur_Role))
	{
		//	Eval����ʼ�շ��صĻ���ִ�ӷ������Ž�
		return std::make_pair(Cur_Board.Evaluate_Chess(this->Role), std::vector<Movement>());
	}



	bool Zob_Memory = false;
	int Zob_Num = 0;
	int Zob_Depth = 0;
	Chess Zob_Chess;
	
#ifdef ENABLE_ZOB
	//	Zob.Search_State(Cur_Zob) != -1 means exist state
	if (Zob.Search_State(Cur_Zob, Depth).first != -1 && Zob.Same_Role(Cur_Zob, Depth))
	{
		Zob_Memory = true;
		//if (Depth == 6)
		//	std::cout << "Using Zobist" << " " << "Depth = " << Depth << std::endl;
		return std::make_pair(Zob.Search_State(Cur_Zob, Depth).first, std::vector<Movement>());

		Zob_Num = Zob.Search_State(Cur_Zob, Depth).first;
		Zob_Depth = Zob.Get_Depth(Cur_Zob);
		Zob_Chess = Zob.Get_Chess(Cur_Zob);
	}
#endif

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
			Eval_Move Ret;

			assert(Zob.Evaluate_Chess(Next_Board) == Next_Zob);
			if (Zob.Evaluate_Chess(Next_Board) != Next_Zob)
			{
				Next_Zob = Zob.Apply_Move(Cur_Board, V, Cur_Zob);
				getchar();
			}
			
			
			Ret = _Search(Next_Board, Depth - 1, Alpha, Beta, PlayerType::MinimizingPlayer, Oppsite_Role(Cur_Role), Zob, Next_Zob);

			int Eval = Ret.first;
			std::vector<Movement> Move_His = Ret.second;

			Zob.Record_State(Next_Zob, Eval, Depth - 1, Alpha, Beta, Next_Board);


			if (Depth == SEARCH_DEPTH)
			{

				std::cout << "Depth == " << SEARCH_DEPTH << " " << (char)('A' + 12 - V.From.x) << V.From.y << " " << (char)('A' + 12 - V.To.x) << V.To.y << " Eval:" << Eval << " Heur Eval:" << Next_Board.Evaluate_Chess(Cur_Role) << std::endl;;

				//getchar(); getchar();
				//Cur_Board.Display();


			}


			if (Eval > Max_Eval)
			{
				Max_Eval = Eval;
				Best_Move = Move_His;
				Best_Move.push_back(V);


				Alpha = (Eval > Alpha) ? Eval : Alpha;
#ifdef ENABLE_ALPHABETA
				if (Beta <= Alpha)
					break;
#endif
			}
		}
		if (Zob_Memory)
		{
			std::cout << "Zob Eval:" << Zob_Num << " Zob Depth:" << Zob_Depth << " Max_Eval:" << Max_Eval << " Cur Dpeth:" << Depth << std::endl;
			std::cout << "Zob_Board:" << Zob.Evaluate_Chess(Zob_Chess) % Table_Size << " Cur_Board:" << Zob.Evaluate_Chess(Cur_Board) % Table_Size << std::endl;

			if (!(Zob_Chess == Cur_Board))
			{
				std::cout << "Different Board" << std::endl;
				getchar();
				getchar();
				Zob_Chess.Display();
				getchar();
				getchar();
				Cur_Board.Display();
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
			Eval_Move Ret;

			Ret = _Search(Next_Board, Depth - 1, Alpha, Beta, PlayerType::MaximizingPlayer, Oppsite_Role(Cur_Role), Zob, Next_Zob);

			int Eval = Ret.first;
			std::vector<Movement> Move_His = Ret.second;
			//	ʵ����Ӧ������������¼������˵��һ�����ء�
			Zob.Record_State(Next_Zob, Eval, Depth - 1, Alpha, Beta, Next_Board);


			if (Eval < Min_Eval)
			{
				Min_Eval = Eval;
				Best_Move = Move_His;
				Best_Move.push_back(V);

				Beta = (Eval < Beta) ? Eval : Beta;
#ifdef ENABLE_ALPHABETA
				if (Beta <= Alpha)
					break;
#endif
			}
		}
		return std::make_pair(Min_Eval, Best_Move);
	}


	//	non-existent situation
	assert(false);
	return std::make_pair(0, std::vector<Movement>());
}


