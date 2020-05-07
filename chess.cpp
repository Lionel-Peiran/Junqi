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
			Next_Board.Board[i][j] = Board[i][j];
		}
	}
	int result = Rank_Judgement(Next_Board.Board[V.To.x][V.To.y], Next_Board.Board[V.From.x][V.From.y]);
	if (result == SAME_RANK) {
		Next_Board.Board[V.To.x][V.To.y] = blank;
		Next_Board.Board[V.From.x][V.From.y] = blank;
	}
	else if (result == ABOVE) {
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
	const Coord board = { Chess_W, Chess_H };
	//	std::cout << "Display Testcase" << std::endl;
	//	1. ����
	cls();
	//	2. ���ý����С
	setconsoleborder(130, 40);
	TransChessBoard(Board);
	//	3. �����������
	common_draw_background(board, true, true, true, { 0,0 });
	Display_Chess(Board, board, true, true);
	//	4. �ָ�Ĭ������
	setcolor();
	std::cout << std::endl << std::endl;
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

	//	1. ������ת����'*'(placeholder)
	TransChessBoard(Board);

	//	2. ��������Board��Ѱ�����Ͳ���
	PieceBoard pb(Board);
	Movement New_Move;
	for (unsigned i = 0; i < Board.size(); i++) {
		for (unsigned j = 0; j < Board[i].size(); j++) {
			PieceCeil ceil = pb.getCeil(i, j);
			//	��ȡ���������·����Ŀɷ��ʵĸ���
			std::vector<PieceCeil> v1 = pb.get4NearestCeil(ceil);
			//	�ر�������������
			if (pb.getCeil(i, j).getPiece().getId() == chessClass::gongbing) {
				std::vector<PieceCeil> v2 = pb.getBFSCeil(ceil);
				v1.insert(v1.end(), v2.begin(), v2.end());
			}
			for (std::vector<PieceCeil>::iterator iter = v1.begin(); iter != v1.end(); iter++) {
				AttackResult attackrslt = ceil.getPiece().attack((*iter).getPiece());
				//	���������������Ӫ��ҹ������������ͬ���ھ�����ô����vector��
				if (Field[(*iter).getX()][(*iter).getY()] != (int)BoardClass::station && (attackrslt == AttackResult::Bigger || attackrslt == AttackResult::Equal)) {
					New_Move.From = { ceil.getX(),ceil.getY() };
					New_Move.To = { (*iter).getX(), (*iter).getY() };
					Move.push_back(New_Move);
				}
			}
		}
	}

	return Move;
}



/*	inline ����  */

//	����Ӧ������ת��������ռλ����'*'��
inline void TransChessBoard(std::vector<std::vector<char> >& BoardData) {
	for (std::vector<std::vector<char>>::iterator iter = BoardData.begin(); iter != BoardData.end(); iter++) {
		for (std::vector<char>::iterator it = (*iter).begin(); it != (*iter).end();) {
			if (*it >= '0' && *it <= '9') {
				int item = *it - '0';
				it = (*iter).erase(it);
				it = (*iter).insert(it, item, placeholder);
			}
			else
				it++;
		}
	}
}

//	����������Ӧλ�õ���ɫ
inline int isColor(int linePos) {
	if (linePos >= 0 && linePos < frontEndPos - 1)
		return COLOR_BLUE;
	else if (linePos == frontEndPos - 1)
		return COLOR_BLACK;
	else
		return COLOR_RED;
}

//	������
inline void common_draw_background(const Coord sizeofall, bool border, bool solid, bool display, const Coord cursor) {
	const char* Solid[][13] = { {"�U", "�T","�X" ,"�[" ,"�^" , "�a", "�d" ,"�g" ,"�j�T","�m�T","�T�p","  " ,"  �U" },
	{ "��","��","��","��","��","��","��","��","�ש�","�ߩ�","����" ,"  " ,"  ��" } };
	enum class Pos { vertical, horizonal, lefttop, righttop, leftbottom, rightbottom, leftmid, rightmid, upmid, downmid, center, empty, straight };

	//	four corners
	showstr(2 * display + cursor.x, 1 + display + cursor.y, Solid[solid][(int)Pos::lefttop], COLOR_HWHITE, COLOR_BLACK);
	showstr(2 * display + 2 * sizeofall.x + 2 + 2 * border * (sizeofall.x - 1) + cursor.x, 1 + display + cursor.y, Solid[solid][(int)Pos::righttop], COLOR_HWHITE, COLOR_BLACK);
	showstr(2 * display + cursor.x, 1 + display + sizeofall.y + border * (sizeofall.y - 1) + 1 + cursor.y, Solid[solid][(int)Pos::leftbottom], COLOR_HWHITE, COLOR_BLACK);
	showstr(2 * display + 2 * sizeofall.x + 2 + 2 * border * (sizeofall.x - 1) + cursor.x, 1 + display + sizeofall.y + border * (sizeofall.y - 1) + 1 + cursor.y, Solid[solid][(int)Pos::rightbottom], COLOR_HWHITE, COLOR_BLACK);

	//	horizonal
	showstr(2 * display + 2 + cursor.x, 1 + display + cursor.y, Solid[solid][(int)Pos::horizonal], COLOR_HWHITE, COLOR_BLACK, (sizeofall.x - 1) * (border + 1) + 1);
	showstr(2 * display + 2 + cursor.x, 3 + display + (border + 1) * (sizeofall.y - 1) + cursor.y, Solid[solid][(int)Pos::horizonal], COLOR_HWHITE, COLOR_BLACK, (sizeofall.x - 1) * (border + 1) + 1);
	if (border) {
		showstr(2 * display + 4 + cursor.x, 1 + display + cursor.y, Solid[solid][(int)Pos::upmid], COLOR_HWHITE, COLOR_BLACK, sizeofall.x - 1);
		showstr(2 * display + 4 + cursor.x, 2 * sizeofall.y + 1 + display + cursor.y, Solid[solid][(int)Pos::downmid], COLOR_HWHITE, COLOR_BLACK, sizeofall.x - 1);
	}

	//	vertical
	for (int i = 0; i < sizeofall.y; i++) {
		showstr(2 * display + cursor.x, 2 + display + i * (border + 1) + cursor.y, Solid[solid][(int)Pos::vertical], COLOR_HWHITE, COLOR_BLACK);
		showstr(2 * display + 2 * (1 + border) * (sizeofall.x - 1) + 4 + cursor.x, 2 + display + i * (border + 1) + cursor.y, Solid[solid][(int)Pos::vertical], COLOR_HWHITE, COLOR_BLACK);
		showstr(2 * display + 2 + cursor.x, 2 + display + i + cursor.y, Solid[solid][(int)Pos::empty], COLOR_HWHITE, COLOR_BLACK, (sizeofall.x - 1) * (border + 1) + 1);
	}
	if (border) {
		for (int i = 0; i < sizeofall.y - 1; i++) {
			showstr(2 * display + cursor.x, 2 * i + 3 + display + cursor.y, Solid[solid][(int)Pos::leftmid], COLOR_HWHITE, COLOR_BLACK);
			showstr(2 * display + 4 * sizeofall.x + cursor.x, 2 * i + 3 + display + cursor.y, Solid[solid][(int)Pos::rightmid], COLOR_HWHITE, COLOR_BLACK);
			showstr(2 * display + 2 + cursor.x, 2 * i + 2 + display + cursor.y, Solid[solid][(int)Pos::straight], COLOR_HWHITE, COLOR_BLACK, sizeofall.x);
			showstr(2 * display + 2 + cursor.x, 2 * i + 3 + display + cursor.y, Solid[solid][(int)Pos::center], COLOR_HWHITE, COLOR_BLACK, sizeofall.x - 1);
			showstr(2 * display + 2 + 4 * (sizeofall.x - 1) + cursor.x, 2 * i + 3 + display + cursor.y, Solid[solid][(int)Pos::horizonal], COLOR_HWHITE, COLOR_BLACK);
		}
		showstr(2 * display + cursor.x, 2 * sizeofall.y + display + cursor.y, Solid[solid][(int)Pos::vertical], COLOR_HWHITE, COLOR_BLACK);
		showstr(2 * display + 4 * sizeofall.x + cursor.x, 2 * sizeofall.y + display + cursor.y, Solid[solid][(int)Pos::vertical], COLOR_HWHITE, COLOR_BLACK);
		showstr(2 * display + 2 + cursor.x, 2 * sizeofall.y + display + cursor.y, Solid[solid][(int)Pos::straight], COLOR_HWHITE, COLOR_BLACK, sizeofall.x);
	}

	//	display coordinates
	if (display) {
		for (int i = 0; i < sizeofall.x; i++) {
			showch(5 + 2 * (border + 1) * i, 1, '0' + i);
		}
		for (int i = 0; i < sizeofall.y; i++) {
			showch(0, 3 + (border + 1) * i, 'A' + sizeofall.y - 1 - i);
		}
	}
}

//	������
inline void Display_Chess(std::vector<std::vector<char> >  Board, class Coord sizeofall, bool border, bool display) {
	if (Board.size() != sizeofall.y || Board[0].size() != sizeofall.x)
		return;

	for (unsigned i = 0; i < Board.size(); i++) {
		for (unsigned j = 0; j < Board[i].size(); j++) {
			showch(2 * display + 2 + 2 * j * (border + 1), 2 + display + i * (border + 1), Board[i][j], COLOR_HWHITE, isColor(i));
		}
		std::cout << std::endl;
	}
}


/*	Piece Implementation  */

Piece::Piece(const char ch) {
	chessClass myId = chessClass::none;
	for (std::vector<std::pair<char, chessClass>>::const_iterator iter = chessPiece.begin(); iter < chessPiece.end(); iter++) {
		if ((*iter).first == ch) {
			myId = (*iter).second;
			break;
		}
	}
	this->id = myId;
	this->role = (ch >= 'a' && ch <= 'z') ? ROLE_LOWER : (ch >= 'A' && ch <= 'Z' ? ROLE_UPPER : ROLE_BLANK);
}

char Piece::getchessClass() const {
	char target = placeholder;
	for (std::vector<std::pair<char, chessClass>>::const_iterator iter = chessPiece.begin(); iter < chessPiece.end(); iter++) {
		if ((*iter).second == this->id) {	//	(*iter).first һ����Сд�ģ���Ϊ���鶨������⣻Ҫ�ĵĻ���һ�仰
			target = this->role == ROLE_LOWER ? (*iter).first : (this->role == ROLE_UPPER ? (*iter).first + 'A' - 'a' : placeholder);
			break;
		}
	}
	return target;
}

AttackResult Piece::attack(const Piece& target) {
	chessClass p = this->getId();
	chessClass t = target.getId();
	if (p == chessClass::dilei || p == chessClass::junqi)
		return AttackResult::None;
	else if (p == chessClass::zhadan || t == chessClass::zhadan)
		return AttackResult::Equal;
	else if (p != chessClass::gongbing && t == chessClass::dilei)
		return AttackResult::Equal;
	else if (p == chessClass::gongbing && t == chessClass::dilei)
		return AttackResult::Bigger;
	else if (p > t)
		return AttackResult::Bigger;
	else if (p == t)
		return AttackResult::Equal;
	else //	if (p < t)
		return AttackResult::Smaller;
}

/*	PieceCeil Implementation  */

ConnWay PieceCeil::isConnPieceCeil(PieceCeil& ceil) {
	if (!this->isValidCeil() || !ceil.isValidCeil())	//	�±곬������
		return ConnWay::none;
	if (Field[this->x][this->y] == (int)BoardClass::empty || Field[ceil.x][ceil.y] == (int)BoardClass::empty)	//	ɽ��λ��
		return ConnWay::none;
	if (this->x == ceil.x && this->y == ceil.y)			//	ͬһ�����
		return ConnWay::none;
	if (abs(this->x - ceil.x) > 1 || abs(this->y - ceil.y) > 1)	//	������λ�ã�8������
		return ConnWay::none;
	if (Railway[this->x][this->y] == 1 && Railway[ceil.x][ceil.y] == 1)	//	��·��·����
		return ConnWay::Railway;
	else if (Field[this->x][this->y] == (int)BoardClass::station || Field[ceil.x][ceil.y] == (int)BoardClass::station)
		return ConnWay::Highway;
	else if ((abs(this->x - ceil.x) == 1 && abs(this->y - ceil.y) == 0)		//	����վ�㶼�Ƿ���Ӫ��������·����
		|| (abs(this->x - ceil.x) == 0 && abs(this->y - ceil.y) == 1))
		return ConnWay::Highway;
	else
		return ConnWay::none;
}

/*	PieceBoard Implementation  */

std::vector<PieceCeil> PieceBoard::get4NearestCeil(PieceCeil cur) {
	std::vector<PieceCeil> nearestCeil;

	//	��·�����
	if (Railway[cur.getX()][cur.getY()] == 1) {
		int cur_x = cur.getX(), cur_y = cur.getY(), j = 0;
		for (int i = 0; i < sizeof(Direction) / sizeof(Coord); i++) {
			PieceCeil next = this->pieceboard[cur_x + Direction[i][0]][cur_y + Direction[i][1]];
			PieceCeil searchCeil = next;
			j = 1;
			while (cur.isConnPieceCeil(searchCeil) == ConnWay::Railway) {
				if (!cur.isValidCeil() || !searchCeil.isValidCeil())
					break;
				if (searchCeil.getPiece().getId() != chessClass::none)
					break;
				j++;
				searchCeil = this->pieceboard[cur_x + j * Direction[i][0]][cur_y + j * Direction[i][1]];
			}
			if (cur.isConnPieceCeil(next) == ConnWay::Railway && !searchCeil.isSameRolePiece(cur))
				nearestCeil.push_back(searchCeil);
		}
	}

	//	��·�����
	for (int i = 0; i < sizeof(FullDirection) / sizeof(Coord); i++) {
		int cur_x = cur.getX(), cur_y = cur.getY();
		PieceCeil next = this->pieceboard[cur_x + FullDirection[i][0]][cur_y + FullDirection[i][1]];
		if (cur.isConnPieceCeil(next) == ConnWay::Highway && next.getPiece().getId() != chessClass::none)
			nearestCeil.push_back(next);
	}

	return nearestCeil;
}


std::vector<PieceCeil> PieceBoard::getBFSCeil(PieceCeil cur) {
	std::vector<PieceCeil> BFSCeil;
	if (cur.getPiece().getId() != chessClass::gongbing)
		return BFSCeil;

	//	BFS������·����
	std::queue<PieceCeil> q;
	q.push(cur);
	while (!q.empty()) {
		PieceCeil ceil = q.front();
		q.pop();
		for (int i = 0; i < sizeof(Direction) / sizeof(Coord); i++) {
			int cur_x = ceil.getX(), cur_y = ceil.getY();
			PieceCeil next = this->getCeil(cur_x + Direction[i][0], cur_y + Direction[i][1]);
			if (!next.isValidCeil())
				continue;
			if (ceil.isConnPieceCeil(next) == ConnWay::Railway && next.getPiece().getId() == chessClass::none)
				q.push(next);
			if (ceil.isConnPieceCeil(next) == ConnWay::Railway && next.getPiece().getId() != chessClass::none)
				BFSCeil.push_back(next);
		}
	}

	//	��·����
	for (int i = 0; i < sizeof(FullDirection) / sizeof(Coord); i++) {
		int cur_x = cur.getX(), cur_y = cur.getY();
		PieceCeil next = this->pieceboard[cur_x + FullDirection[i][0]][cur_y + FullDirection[i][1]];
		if (cur.isConnPieceCeil(next) == ConnWay::Highway && next.getPiece().getId() != chessClass::none)
			BFSCeil.push_back(next);
	}

	return BFSCeil;
}

/*	Testcase  */
void test(std::vector<std::vector<char> >  Board) {
	PieceBoard pb(Board);
	if (0) {
		for (unsigned i = 0; i < Board.size(); i++) {
			for (unsigned j = 0; j < Board[i].size(); j++) {
				std::cout << pb.getCeil(i, j) << ' ';
			}
			std::cout << std::endl;
		}
	}
	if (0) {
		std::cout << (int)pb.getCeil(0, 1).isConnPieceCeil(pb.getCeil(0, 2)) << std::endl;	//	Highway
		std::cout << (int)pb.getCeil(0, 1).isConnPieceCeil(pb.getCeil(1, 1)) << std::endl;	//	Highway
		std::cout << (int)pb.getCeil(0, 0).isConnPieceCeil(pb.getCeil(1, 0)) << std::endl;	//	Highway
		std::cout << (int)pb.getCeil(1, 0).isConnPieceCeil(pb.getCeil(2, 1)) << std::endl;	//	Highway
		std::cout << (int)pb.getCeil(2, 0).isConnPieceCeil(pb.getCeil(2, 1)) << std::endl;	//	Highway
		std::cout << (int)pb.getCeil(1, 0).isConnPieceCeil(pb.getCeil(2, 0)) << std::endl;	//	Railway
		std::cout << (int)pb.getCeil(2, 1).isConnPieceCeil(pb.getCeil(3, 1)) << std::endl;	//	Highway
		std::cout << (int)pb.getCeil(1, 0).isConnPieceCeil(pb.getCeil(5, 0)) << std::endl;	//	none
	}

}

