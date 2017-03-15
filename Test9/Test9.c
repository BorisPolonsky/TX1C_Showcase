/*
����ͨ��ʵ��
����λ������1����Ƭ��ʱ����������400msƵ�ʷ�������2ʱ��200msƵ�ʷ�������3ʱ��100msƵ�ʷ�������4ʱ���з�������
*/
#include <reg52.h>
sbit FM=P2^3;
unsigned char ch;
void init();
void delay(unsigned int);
void fmfun(unsigned int);
void main()
{
	init();
	while(1)
	{
		switch(ch)
		{
		case '1':
			fmfun(400);
			break;
		case '2':
			fmfun(200);
			break;
		case '3':
			fmfun(100);
			break;
		case '4':
			FM=1;
			break;
		default:
			P1=ch;
		}
	}		
}

void init()
{
	EA=1;
	TMOD=0x20;
	TL1=0xFD;
	TH1=0xFD;
	TR1=1;

	REN=1;
	SM0=0;
	SM1=1;
	ES=1;
	ch='4';
}

void delay(unsigned int t)
{
	unsigned int x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

void fmfun(unsigned int tt)//�÷�������һ������(Լtt����)�ڷ���
{
	FM=0;
	delay(tt/2);
	FM=1;
	delay(tt/2);
}

void ser() interrupt 4
{	
	ch=SBUF;
	RI=0;
}
