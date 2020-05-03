#include <iostream>
#include "connect.h"
#include "game.h"
#include "main.h"

/*
 ����: Junqi.exe �C-role 1 �C-time 60
	ע�� ����role��0��ʾ�췽��1��ʾ�ڷ���
		����time����ʾ��������ʱ�䣬��λ�롣

*/

int main(int argc, char * argv[])
{
	Connect Con;
	Con.Init();

	//	ȱʡ����£�ִ����
	//	int State = STATE_LOWER;
	

	//	�趨ִ�ӷ�
	Game Junqi;
	Junqi.Arg_Init(argc, argv);

	while (true)
	{
		Chess Board;
		int Status = Con.Get_Board(Board);
		if (Status == STATUS_END)
			break;

		Board.Display();

		Movement Move = Junqi.Search(Board);

		Board = Board.Apply_Move(Move);
		Board.Display();

		Con.Send_Move(Move);

	}
	return 0;
}