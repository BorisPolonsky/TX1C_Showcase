/*
����ͨ��ʵ��
��4800bps�Ӽ����������һ�ֽ����ݣ�����Ƭ���յ������ݺ��ڴ�����ǰ����һ���(16����)Ȼ����ͬ������һ�����������������ų���255ʱ���㡣
*/
#include <reg52.h>
unsigned int num;//���
unsigned char ch;//���ڴ洢�յ���һ�ֽ�����
void init();
void main()
{
	init();
	while(1)
	{
		while(!RI);
		RI=0;
		ch=SBUF;
		SBUF=num++;
		while(!TI);
		TI=0;
		SBUF=ch;
		while(!TI);
		TI=0;
	}
}

void init()
{
	TMOD=0x20;
	TL1=0xFA;
	TH1=0xFA;
	TR1=1;

	SM0=0;
	SM1=1;
	REN=1;
	EA=1;
}
