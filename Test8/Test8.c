/*
����ͨ��
��ѭ��:���գ�����
��ʱ��T1���������ʷ�����



BUG:ֻ�ܷ�������λ,�жϲ���λ��Ӱ�������
����:T1��ʱ������봮�ڵĹ�ϵ
*/

#include <reg52.h>
unsigned int flag;//flag:���գ�����ָʾ,1Ϊ����
unsigned char ch;//�洢���յ���Ϣ
void init();
void main()
{
	init();
	while(1)
	{
		if(flag)
		{
			while(!RI);
			RI=0;
			ch=SBUF;
			P1=0x0f;//���պ����λ����
			flag=0;
		}
		else
		{
			SBUF=ch;
			while(!TI);
			TI=0;
			P1=0xf0;//���ͺ����λ����
			flag=1;
		}
	}
}

void init()
{
	SM0=0;
	SM1=1;//-----��ʽ1
	REN=1;//�������
	TR1=1;//������ʱ��1
	TMOD=0x20;//���ö�ʱ��1Ϊ��ʽ2
	TH1=0xFD;//TH��ĳ�ֵ�Զ�����TL1
	TL1=0xFD;
	EA=1;
//	ES=1;
	flag=1;
}

void fun() interrupt 4
{
	if(flag)
	{
		RI=0;
		ch=SBUF;
		P1=0x0f;
		flag=0;
	}
	else
	{
		TI=0;
		P1=0xf0;
		flag=1;
	}
}

