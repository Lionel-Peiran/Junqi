#pragma once
#include <vector>
#include "chess.h"

/*
State״̬	
STATE_END	��ʾ��ǰ���̽���
STATE_UPPER	��ǰִ�ӷ�Ϊ�ϲ������������еĴ�д����
STATE_LOWER	��ǰִ�ӷ�Ϊ�²������������е�Сд����
*/
const int STATUS_END = -1;
const int STATUS_OK = 0;

/*
Role	ִ�巽
	Role == Role_UPPER	��ʾִ�巽Ϊ��д�����Ϸ�
	Role == Role_LOWER	��ʾִ�巽ΪСд�����·�
*/
const int ROLE_UPPER = 1;
const int ROLE_LOWER = 0;



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


//	��minmax�����е��������
enum class PlayerType {
	MaximizingPlayer,
	MinimizingPlayer
};

//	Return of function "_Search"
typedef std::pair<int, std::vector<Movement> > Eval_Move;

/*
Role	ִ�巽
	Role == Role_UPPER	��ʾִ�巽Ϊ��д�����Ϸ�
	Role == Role_LOWER	��ʾִ�巽ΪСд�����·�

Time_Limit	ʱ������
	Ŀǰ��û�������ơ�
*/

class Game
{
protected:
	int Role;
	int Time_Limit;
public:
	void Arg_Init(int argc, char * argv[]);
	Movement Search(Chess Board, int Depth = 5);
private:
	Eval_Move _Search(Chess Cur_Board, int Depth, int Alpha, int Beta, PlayerType Player, int Cur_State);

};
