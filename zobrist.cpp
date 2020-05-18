#include <cassert>
#include <map>
#include "zobrist.h"
#include "chess.h"
#include "game.h"


//	����unsigned long long ��С�������
static ull Rand_ULL()
{
	return ((((ull)rand()) & 0x0000000000007FFFull) |
		(((ull)rand() << 15) & 0x000000003FFF8000ull) |
		(((ull)rand() << 30) & 0x00001FFFC0000000ull) |
		(((ull)rand() << 45) & 0x07FFF00000000000ull) |
		(((ull)rand() << 60) & 0xF800000000000000ull)
		);
}

//	���ɺ���	��ʼ��ÿ��λ�õĲ�ͬ���ӵ�Ȩ�أ���ʼ��Hash��
Zobrist::Zobrist()
{
	for (int i = 0; i < Chess_H; i++)
		for (int j = 0; j < Chess_W; j++)
			for (int k = 0; k < Chess_Type * 2 + 1; k++)
				Zobrist_Table[i][j][k] = Rand_ULL();
	Hash_Table = new int[Table_Size];
	memset(Hash_Table, 0, sizeof(Hash_Table[0]) * Table_Size);
}

Zobrist::~Zobrist()
{
	delete[] Hash_Table;
}

//	���е�һ��λ�����һ������
ull Zobrist::Add_Piece(ull Chess, int x, int y, char Piece) const
{
	return Chess ^ Zobrist_Table[x][y][chessNum.at(Piece)];
}

//	���е�һ��λ��ȥ��һ������
ull Zobrist::Remove_Piece(ull Chess, int x, int y, char Piece) const
{
	return Chess ^ Zobrist_Table[x][y][chessNum.at(Piece)];
}

//	��¼״̬��Eval
void Zobrist::Record_State(ull Chess, int Eval) const
{
	/*
#ifdef DEBUG
	assert(Hash_Table[Chess % Table_Size] == 0);
#endif // DEBUG
	*/
	Hash_Table[Chess % Table_Size] = Eval;
}

//	��ѯ״̬��Eval
int Zobrist::Search_State(ull Chess) const
{
	if (Hash_Table[Chess % Table_Size] == 0)
		return -1;
	return Hash_Table[Chess % Table_Size];
}

ull Zobrist::Evaluate_Chess(Chess C) const
{
	ull Ret = 0;
	for (int i = 0; i < Chess_H; i++)
		for (int j = 0; j < Chess_W; j++)
			Ret = Add_Piece(Ret, i, j, C.Board[i][j]);
	return Ret;
}

ull Zobrist::Apply_Move(const Chess& C, const Movement& V, const ull& Zob) const
{

	ull Ret = Zob;
	int result = Rank_Judgement(C.Board[V.To.x][V.To.y], C.Board[V.From.x][V.From.y]);
	if (result == SAME_RANK) 
	{
		Ret = Remove_Piece(Zob, V.To.x, V.To.y, C.Board[V.To.x][V.To.y]);
		Ret = Remove_Piece(Zob, V.From.x, V.From.y, C.Board[V.From.x][V.From.y]);
		Ret = Add_Piece(Zob, V.To.x, V.To.y, BLANK);
		Ret = Add_Piece(Zob, V.From.x, V.From.y, BLANK);
	}
	if (result == ABOVE) 
	{

		Ret = Remove_Piece(Zob, V.From.x, V.From.y, C.Board[V.From.x][V.From.y]);
		Ret = Add_Piece(Zob, V.From.x, V.From.y, BLANK);
	}
	else {
		Ret = Remove_Piece(Zob, V.To.x, V.To.y, C.Board[V.To.x][V.To.y]);
		Ret = Remove_Piece(Zob, V.From.x, V.From.y, C.Board[V.From.x][V.From.y]);
		Ret = Add_Piece(Zob, V.To.x, V.To.y, C.Board[V.From.x][V.From.y]);
		Ret = Add_Piece(Zob, V.From.x, V.From.y, BLANK);
	}

	return Ret;
}




