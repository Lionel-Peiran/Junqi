#pragma once
#include <iostream>
#include "chess.h"
#include "game.h"

typedef unsigned long long ull;

//	������˵������2^n��Table_Size������λ������٣������Ҿ��ò����ף�Hash��Mod����������
const int Table_Size = 1000003;

class Chess;
class Movement;
class Zobrist
{
private:
	ull Zobrist_Table[13][5][12 * 2 + 1];
	mutable int* Hash_Table;
	mutable int* Hash_Depth;
	bool* Hash_Bool;
	mutable int* Hash_Alpha;
	mutable int* Hash_Beta;
public:
	Zobrist();
	~Zobrist();
	ull Add_Piece(ull Chess, int x, int y, char Piece) const ;
	ull Remove_Piece(ull Chess, int x, int y, char Piece) const ;
	void Record_State(ull Chess, int Eval, int Depth, int Alpha, int Beta) const;
	std::pair<int, std::pair<int, int> > Search_State(ull Chess, int Depth) const;
	ull Evaluate_Chess(Chess C) const;
	ull Apply_Move(const Chess& C,const Movement& V, const ull& Zob) const;
	bool Same_Role(ull Chess, int Depth) const ;
};