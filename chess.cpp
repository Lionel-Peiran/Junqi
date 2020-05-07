#include <iostream>
#include "chess.h"

/*
input:
Role	ִ�巽
	Role == Role_UPPER	��ʾִ�巽Ϊ��д�����Ϸ�
	Role == Role_LOWER	��ʾִ�巽ΪСд�����·�


output:
	true/false	��ǰִ�巽�������/�������

function:
	��������this->Board���жϵ�ǰִ�ӷ��Ƿ��������
*/

int Chess::Rank_Judgement(char a, char b)
{
	//��λ��Ϊ��
	if (a == blank)
		return UNDER;
	if (b == blank)
		return ABOVE;
	if (a >= 'a' && a <= 'z')
		a = a - 'a' + 'A';
	if (b >= 'a' && b <= 'z')
		b = b - 'a' + 'A';
	if (a == 'Z' || b == 'Z'||a == b)//���⣺ը��
		return SAME_RANK;
	if (a != 'G' && b == 'D' || a == 'D' && b != 'G')//���⣺����
		return SAME_RANK;
	if (a == 'G' && b == 'D')//���⣺��������
		return ABOVE;
	if (a == 'D' && b == 'G')//���⣺��������
		return UNDER;
	//����Ϊ�ȼ�˳��
	int a_order;
	int b_order;
	for (int i = 0; i < 10; i++) {
		if (a == RANK[i])
			a_order = i;
		if (b == RANK[i])
			b_order = i;
	}
	if (a_order < b_order)
		return ABOVE;
	else
		return UNDER;
}

bool Chess::Is_Over(const int& Role)
{
	/* NEED CODE */
	//ֻ������˫����Ӫ�ڵľ�����û�б���
	if((Board[0][1]=='F'||Board[0][3]=='F')&&(Board[12][1]=='f'||Board[12][3]=='f'))
		return false;
	return true;
}



/*
input:
Role	ִ�巽
	Role == Role_UPPER	��ʾִ�巽Ϊ��д�����Ϸ�
	Role == Role_LOWER	��ʾִ�巽ΪСд�����·�


output:
	Weight������Ȩ�أ� ��ǰ��ִ�ӷ����ȥ�Է�ִ�ӷ���
	Weight = Weigh_Role - Weight_Opp_Role
	��ÿ�����ӽ��и�Ȩ������������и�ֵ��

function:
	�����̵���������
*/


int Chess::Evaluate_Chess(const int& Role)
{
	int UPPER = 0;
	int LOWER = 0;
	for (int i = 0; i < Chess_H; i++) {
		for (int j = 0; j < Chess_W; j++) {
			if (Board[i][j] >= 'A' && Board[i][j] <= 'Z')
				UPPER++;
			else
				LOWER++;
		}
	}
	if (Role == ROLE_LOWER)
		return LOWER - UPPER;
	else
		return UPPER - LOWER;
}


/*
input:
Role	ִ�巽
	Role == Role_UPPER	��ʾִ�巽Ϊ��д�����Ϸ�
	Role == Role_LOWER	��ʾִ�巽ΪСд�����·�

output:
	Move ��ʾÿ�����е�Movement���洢��vector��

function:
	Ѱ�������������ų�ֵ�����ռ�
*/
std::vector<Movement> Chess::Search_Movement(const int& Role)
{
	std::vector<Movement> Move;
	Move.clear();

	/* NEED CODE */

	return Move;
}



/*
input:
	Move			���巽��

output:
	Next_Board		����֮�������

function:
	ͨ��Move���this->Board����������
*/

Chess Chess::Apply_Move(const Movement& V)
{
	Chess Next_Board;
	for (int i = 0; i < Chess_H; i++) {
		for (int j = 0; j < Chess_W; j++) {
			Next_Board.Board[i][j] == Board[i][j];
		}
	}
	int result = Rank_Judgement(Next_Board.Board[V.To.x][V.To.y], Next_Board.Board[V.From.x][V.From.y]);
	if (result == SAME_RANK) {
		Next_Board.Board[V.To.x][V.To.y] = blank;
		Next_Board.Board[V.From.x][V.From.y] = blank;
	}
	else if (result = ABOVE) {
		Next_Board.Board[V.From.x][V.From.y] = blank;
	}
	else {
		Next_Board.Board[V.To.x][V.To.y] = Next_Board.Board[V.From.x][V.From.y];
		Next_Board.Board[V.From.x][V.From.y] = blank;
	}
	/* NEED CODE */

	return Next_Board;
}


/*
function:
	�򵥵Ŀ��ӻ�����Ч������-+|��ʾ���ɣ���Ҫ���ڵ��ԡ�
	��������ɫ����͸�����
*/
void Chess::Display()
{

	/* NEED CODE */

}

