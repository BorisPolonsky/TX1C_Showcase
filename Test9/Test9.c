/*
串口通信实验
由上位机发送1给单片机时，蜂鸣器以400ms频率发声，发2时以200ms频率发声，发3时以100ms频率发声，发4时关闲蜂鸣器。
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

void fmfun(unsigned int tt)//让蜂鸣器在一个周期(约tt毫秒)内发声
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
