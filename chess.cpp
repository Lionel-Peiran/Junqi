#include <iostream>
#include "chess.h"

/*
input:
Role	执棋方
	Role == Role_UPPER	表示执棋方为大写，即上方
	Role == Role_LOWER	表示执棋方为小写，即下方


output:
	true/false	当前执棋方无棋可走/有棋可走

function:
	根据棋盘this->Board，判断当前执子方是否无棋可走
*/

int Chess::Rank_Judgement(char a, char b)
{
	//新位置为空
	if (a == BLANK)
		return UNDER;
	if (b == BLANK)
		return ABOVE;
	if (a >= 'a' && a <= 'z')
		a = a - 'a' + 'A';
	if (b >= 'a' && b <= 'z')
		b = b - 'a' + 'A';
	if (a == 'Z' || b == 'Z' || a == b)//特殊：炸弹
		return SAME_RANK;
	if (a != 'G' && b == 'D' || a == 'D' && b != 'G')//特殊：地雷
		return SAME_RANK;
	if (a == 'G' && b == 'D')//特殊：工兵排雷
		return ABOVE;
	if (a == 'D' && b == 'G')//特殊：工兵排雷
		return UNDER;
	//以下为等级顺序
	int a_order;
	int b_order;
	for (int i = 0; i < strlen(RANK); i++) {
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
	//只考虑了双方大本营内的军旗有没有被吃
	if ((Board[0][1] == 'F' || Board[0][3] == 'F') && (Board[12][1] == 'f' || Board[12][3] == 'f'))
		return false;
	//找到棋盘内可移动的棋子
	char ch0 = 'A';
	char ch1 = 'Z';
	if (Role == ROLE_LOWER) {
		ch0 = 'a';
		ch1 = 'z';
	}
	for (int i = 0; i < Chess_H; i++) {
		for (int j = 0; j < Chess_W; j++) {
			if (Board[i][j] >= ch0 && Board[i][j] <= ch1)
			{
				if (chessMap.at(Board[i][j]) == chessClass::dilei)
					continue;
				if (chessMap.at(Board[i][j]) == chessClass::junqi)
					continue;
				return false;
			}
		}
	}
	return true;
}



/*
input:
Role	执棋方
	Role == Role_UPPER	表示执棋方为大写，即上方
	Role == Role_LOWER	表示执棋方为小写，即下方


output:
	Weight，棋盘权重， 当前的执子方棋减去对方执子方棋
	Weight = Weigh_Role - Weight_Opp_Role
	对每个棋子进行赋权，具体可以自行赋值。

function:
	对棋盘的评估函数
*/
//const char RANK[] = "AJSVTYLPGF";
int Chess::Evaluater(const int x, const int y, const char ch)
{
	int value = 0;;
	//正常等级
	if (ch == 'g' || ch == 'G')
		value = 100;
	else if (ch == 'p' || ch == 'P')
		value = 100;
	else if (ch == 'l' || ch == 'L')//X2
		value = 200;
	else if (ch == 'y' || ch == 'Y')//X3
		value = 400;
	else if (ch == 't' || ch == 'T')//X4
		value = 800;
	else if (ch == 'v' || ch == 'V')//X5
		value = 1600;
	else if (ch == 's' || ch == 'S')//X6
		value = 3200;
	else if (ch == 'j' || ch == 'J')//X7
		value = 6400;
	else if (ch == 'a' || ch == 'A')//X8
		value = 12800;
	else if (ch == 'f' || ch == 'F')//X8
		value = 51200;
	else if (ch == 'z' || ch == 'Z')
		value = 800;//希望炸弹至少消灭团长，或者团长以下的单位可主动消灭炸弹
	else if (ch == 'd' || ch == 'D')
		value = 400;//地雷不视为威胁，营长或营长以下都可主动牺牲

	//加入行营所占的权重，希望尽可能占领多的行营
	return (int)(1 + 0.005 * Station[x][y] + 0.001 * Railway[x][y]) * value;

}

int Chess::Evaluate_Chess(const int& Role)
{
	int UPPER = 0;
	int LOWER = 0;
	for (int i = 0; i < Chess_H; i++) {
		for (int j = 0; j < Chess_W; j++) {
			if (Board[i][j] >= 'A' && Board[i][j] <= 'Z')
				UPPER += Evaluater(i, j, Board[i][j]);
			else
				LOWER += Evaluater(i, j, Board[i][j]);
		}
	}
	if (Role == ROLE_LOWER)
		return LOWER - UPPER;
	else
		return UPPER - LOWER;
}


/*
input:
	Move			走棋方向

output:
	Next_Board		更新之后的棋盘

function:
	通过Move结合this->Board来更新棋盘
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
		Next_Board.Board[V.To.x][V.To.y] = BLANK;
		Next_Board.Board[V.From.x][V.From.y] = BLANK;
	}
	else if (result == ABOVE) {
		Next_Board.Board[V.From.x][V.From.y] = BLANK;
	}
	else {
		Next_Board.Board[V.To.x][V.To.y] = Next_Board.Board[V.From.x][V.From.y];
		Next_Board.Board[V.From.x][V.From.y] = BLANK;
	}

	return Next_Board;
}


/*
function:
	简单的可视化棋盘效果，用-+|表示即可，主要用于调试。
	假如有颜色区别就更好了
*/
void Chess::Display()
{
	const Coord board = { Chess_W, Chess_H };
	//	std::cout << "Display Testcase" << std::endl;
	//	1. 清屏
	cls();
	//	2. 设置界面大小
	setconsoleborder(130, 40);

	//	3. 画界面和棋子
	common_draw_background(board, true, true, true, { 0,0 });
	Display_Chess(Board, board, true, true);
	//	4. 恢复默认设置
	setcolor();
	std::cout << std::endl << std::endl;
}


//	该棋子为执棋方
static bool Is_Role_Chess(char ch, int Role)
{
	if (Role == ROLE_UPPER && ch >= 'A' && ch <= 'Z')
		return true;
	if (Role == ROLE_LOWER && ch >= 'a' && ch <= 'z')
		return true;
	return false;
}


//	该棋子为工兵
static bool Is_GongBing(char ch)
{
	return (ch == 'g') || (ch == 'G');
}

//	合法位置
static bool Is_Valid(int x, int y)
{
	//  目的地为山界
	if (Field[x][y] == (int)BoardClass::empty)
		return false;
	return (x >= 0 && x < Chess_H&& y >= 0 && y < Chess_W);
}


//	在铁路上
static bool Is_Railway(int x, int y)
{
	return Railway[x][y];
}

//	在行营中
static bool Is_Station(int x, int y)
{
	return Station[x][y];
}

//	有棋子
static bool Has_Chess(char ch)
{
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

static bool Special_move(int x, int y, int cur_x, int cur_y)
{
	if (abs(x - cur_x) + abs(y - cur_y) > 1)
		return false;
	return true;
}

bool Chess::Is_Movable(Movement M)
{
	char From = Board[M.From.x][M.From.y];
	char To = Board[M.To.x][M.To.y];
	int x = M.From.x;
	int y = M.From.y;
	int cur_x = M.To.x;
	int cur_y = M.To.y;

	//  特殊位置判断
	//  目的地为山界
	if (Field[cur_x][cur_y] == (int)BoardClass::empty)
		return false;
	//  不可侧向移动的位置
	if (SpecialPos[cur_x][cur_y] || SpecialPos[x][y])
		return Special_move(x, y, cur_x, cur_y);
	//  吃子判断
	//	强制要求吃子
	if (To == BLANK)
		return false;

	if (chessMap.at(From) == chessClass::dilei)
		return false;
	if (chessMap.at(From) == chessClass::junqi)
		return false;

	//	对方的棋子大
	if (Rank_Judgement(From, To) == UNDER)
		return false;

	//	方向是行营且有棋子
	if (Is_Station(M.To.x, M.To.y) && Has_Chess(To))
		return false;
	return true;
}

void Chess::Set_Board(int x, int y, int ch)
{
	Board[x][y] = ch;
}

/*
input:
Role	执棋方
	Role == Role_UPPER	表示执棋方为大写，即上方
	Role == Role_LOWER	表示执棋方为小写，即下方

output:
	Move 表示每个可行的Movement，存储在vector中

function:
	寻找搜索方向，有着充分的想象空间
*/

int Chess::Selector(Chess chess,const int&Role,Movement M)
{
	int before = Evaluate_Chess(Role);
	chess.Apply_Move(M);
	int after = Evaluate_Chess(Role);
	return after - before;
}
bool cmp(std::pair<int, Movement> a, std::pair<int, Movement> b)
{
	return a.first > b.first;
}
std::vector<Movement> Chess::SelectMoveMent(std::vector <Movement> M,const int&Role)
{
	Chess T;
	for (int i = 0; i < Chess_H; i++)
		for (int j = 0; j < Chess_W; j++)
			T.Board[i][j] = this->Board[i][j];//复刻一个棋盘
	std::vector<std::pair<int, Movement>> pair;
	for (int i = 0; i < M.size(); i++) {
		int temp = Selector(T,Role,M[i]);
		pair.push_back(std::make_pair(temp, M[i]));
	}
	sort(pair.begin(), pair.end(), [](std::pair<int, Movement> a, std::pair<int, Movement> b) {return a.first > b.first; });
	std::vector<Movement> result;
	for (int i = 0; i < pair.size(); i++)
		result.push_back(pair[i].second);
	return result;
}

void Chess::BFSSearch(int x, int y, std::vector<Coord> &Pos)
{
	static bool check[Chess_H][Chess_W] = { 0 };
	check[x][y] = true;
	//只在碰到棋子时结束，且目前只记录碰到棋子时的坐标
	if (Has_Chess(Board[x][y])) {
		Coord P(x, y);
		Pos.push_back(P);
		return;
	}
	Coord P(x, y);
	Pos.push_back(P);
	for (int k = 0; k < 4; k++) {
		if (!check[x + HV_DirectX[k]][y + HV_DirectY[k]] && Is_Valid(x + HV_DirectX[k], y + HV_DirectY[k]))
			if (Is_Railway(x + HV_DirectX[k], y + HV_DirectY[k]))
				BFSSearch(x + HV_DirectX[k], y + HV_DirectY[k], Pos);
	}
}

bool Expand_Move(std::vector<Movement>& Move, const int cur_x, const int cur_y, const int next_x, const int next_y, const char next_ch, const int Role)
{
	Movement V = Movement(Coord(cur_x, cur_y), Coord(next_x, next_y));
	if (!(Is_Railway(cur_x, cur_y) && Is_Railway(next_y, next_y)))
		return false;
	if (Is_Role_Chess(next_ch, Role))
		return false;
	if (Has_Chess(next_ch))
	{	
		Move.push_back(V);
		return false;
	}	
	Move.push_back(V);
	return true;
}

bool Cross_Move(std::vector<Movement>& Move, const int cur_x, const int cur_y, const int next_x, const int next_y, const char next_ch, const int Role)
{
	Movement V = Movement(Coord(cur_x, cur_y), Coord(next_x, next_y));
	if (Is_Role_Chess(next_ch, Role))
		return false;
	if (Is_Station(next_x, next_y) && Has_Chess(next_ch))
		return false;
	if (!(Is_Station(cur_x, cur_y) || Is_Station(next_x, next_y)))
		return false;
	Move.push_back(V);
	return true;
}

std::vector<Movement> Chess::Search_Movement(const int& Role)
{
	std::vector<Movement> Move;
	Move.clear();

	for (int i = 0; i < Chess_H; i++) {
		for (int j = 0; j < Chess_W; j++) {
			if (Is_Role_Chess(Board[i][j], Role) && chessMap.at(Board[i][j])!= chessClass::junqi)
			{
				if (Is_GongBing(Board[i][j])) {
					//只考虑在铁路上的情况，其他情况在下面会考虑到
					if (Is_Railway(i, j)) {
						std::vector<Coord> Pos;
						Pos.clear();
						BFSSearch(i, j, Pos);
						for (int k = 0; k < Pos.size(); k++) {
							if (Is_Role_Chess(Board[Pos[k].x][Pos[k].y], Role))
								continue;
							Movement M = Movement(Coord(i, j), Pos[k]);
							if (!Is_Movable(M))
								continue;
							Move.push_back(M);
						}
					}
				}


				//	上下左右方向，铁路上自动扩展
				for (int k = 0; k < 4; k++)
					for (int d = 1; d <= Chess_H; d++)
					{
						int next_x = i + HV_DirectX[k] * d;
						int next_y = j + HV_DirectY[k] * d;
						if (!Is_Valid(next_x, next_y))
							break;
						bool Ret = Expand_Move(Move, i, j, next_x, next_y, Board[next_x][next_y], Role);
						//	如果已经碰到棋子或者脱离铁轨，即不能够再搜索了
						if (!Ret)
							break;
					}

				// 斜向方向
				for (int k = 0; k < 4; k++)
				{
					int next_x = i + Cross_DirectX[k];
					int next_y = j + Cross_DirectY[k];
					if (!Is_Valid(next_x, next_y))
						break;
					bool _ = Cross_Move(Move, i, j, next_x, next_y, Board[next_x][next_y], Role);
				}
			}
		}
		//	std::cout <<"Move.size:"<< Move.size() << std::endl;
	}
	return Move;
}





//	返回棋盘相应位置的颜色
inline int isColor(int linePos) {
	if (linePos >= 0 && linePos < frontEndPos - 1)
		return COLOR_BLUE;
	else if (linePos == frontEndPos - 1)
		return COLOR_BLACK;
	else
		return COLOR_RED;
}

//	画棋盘
inline void common_draw_background(const Coord sizeofall, bool border, bool solid, bool display, const Coord cursor) {
	const char* Solid[][13] = { {"║", "═","╔" ,"╗" ,"╚" , "╝", "╠" ,"╣" ,"╦═","╩═","═╬","  " ,"  ║" },
	{ "┃","━","┏","┓","┗","┛","┣","┫","┳━","┻━","━╋" ,"  " ,"  ┃" } };
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

//	画棋子
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

