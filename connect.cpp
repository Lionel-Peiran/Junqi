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
	
	/* NEED CODE */
	
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

	/* NEED CODE */

	std::cout << Str_Move << std::endl;
}




