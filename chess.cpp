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

bool Chess::Is_Over(const int& Role)
{
	/* NEED CODE */
	return bool();
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
	/* NEED CODE */
	return 0;
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

