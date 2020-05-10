#include <iostream>
#include <string>
#include "connect.h"


/*
(1)	ready
��������������淢��ready��������洦�ڿ���״̬��
*/
void Connect::Init()
{
	std::cout << "ready" << std::endl;
}

/*
input: �����������
(2)	<��ǰ���>
���潫��ǰ�����NCN����ʽʹ�ñ�׼���봫�ݸ����棬���濪ʼ����
����: ppdfd/plldz/z1g1y/yt1ty/s1g1s/jvgva/5/JVGVA/S1G1S/YT1TY/Z1G1Y/PLLDZ/PPDFD 0 0
(3)	init <��ǰ���>
���ڽ�����ʱ����ִ��ݸ����ֵ����棬��֤��ʼ�����ʱ�����һ�¡�
����: init ppdfd/plldz/z1g1y/yt1ty/s1g1s/jvgva/5/JVGVA/S1G1S/YT1TY/Z1G1Y/PLLDZ/PPDFD 0 0
(5)	end
��ֽ����������˳���

output��
Status			�Ƿ����
	���������Status == STATUS_END
		���� Status == STATUS_OK
Chess Board		�����������ݣ���¼��Board��
*/
int Connect::Get_Board(Chess & Board)
{
	int Status = STATUS_OK;
	
	char ch;
	int i = 0, j = 0;
	while (std::cin >> ch)
	{
		if (ch == 'i')
			for (int i = 0; i <= 3; i++)
				std::cin >> ch;
		else if (ch == 'e')
			return STATUS_END;
		else if (ch == '/')
			i++;
		else if (ch <= 53 && ch >= 49)
			for (int i = 48; i < (int)ch; i++)
			{
				Board[i][j] = '*';
				j++;
			}
		else
		{
			Board[i][j] = ch;
			j++;
		}

	}
	
	return Status;
}

/*
input:	Move�ṹ��
		Move.From	��ʾ��ʼ���� ���������ֱ�ʾ
		Move.To		��ʾ�յ����� ���������ֱ�ʾ
output: 
(4)	<���Ӿ���>
	ʹ�ñ�׼����ķ�ʽ�������������˺����淵�ؿ���״̬����Ǽ������㡣
����: h2i2
*/
void Connect::Send_Move(const Movement& Move)
{
	std::string Str_Move;

	std::string s1, s2, s3, s4;
	s1 = 'a' + 13 - Move.From.x;
	s2 = '0' + Move.From.y;
	s3 = 'a' + 13 - Move.To.x;
	s4 = '0' + Move.To.y;
	Str_Move = s1 + s2 + s3 + s4;

	std::cout << Str_Move << std::endl;
}




