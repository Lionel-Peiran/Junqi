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
Chess Board		�����������ݣ���¼��Board��
State			�յ�initʱ��State = STATE_UPPER��������ִ�壩
				�յ�endʱ��State = STATE_END
				��������²����иĶ���
*/
Chess Connect::Get_NCN(int& State)
{
	Chess Board;

	/* NEED CODE */

	return Board;
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
void Connect::Send_NCN(const Movement& Move)
{
	std::string NCN;

	/* NEED CODE */

	std::cout << NCN << std::endl;
}




