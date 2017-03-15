/*
串口通信实验
以16进制发送一个0-65536之间的任一数(分2字节)，当单片机收到后在数码管上动态显示出来，波特率自定。

*/

#include <reg52.h>
unsigned int num;
sbit dula=P2^6;
sbit wela=P2^7;
unsigned char code table[]={
	0x3f,0x06,0x5b,0x4f,0x66,
	0x6d,0x7d,0x07,0x7f,0x6f
};
void init();
void delay(unsigned int);
void main()
{
	init();
	while(1)
	{
		P0=0xDF;
		wela=1;
		wela=0;
		P0=table[num%10];
		dula=1;
		dula=0;
		delay(2);

		P0=0xEF;
		wela=1;
		wela=0;
		P0=table[(num/10)%10];
		dula=1;
		dula=0;
		delay(2);

		P0=0xF7;
		wela=1;
		wela=0;
		P0=table[(num/100)%10];
		dula=1;
		dula=0;
		delay(2);

		P0=0xFB;
		wela=1;
		wela=0;
		P0=table[(num/1000)%10];
		dula=1;
		dula=0;
		delay(2);

		P0=0xFD;
		wela=1;
		wela=0;
		P0=table[(num/10000)%10];
		dula=1;
		dula=0;
		delay(2);
	}
}

void init()
{
	TMOD=0x20;
	TH1=0xFD;
	TL1=0xFD;
	TR1=1;

	EA=1;

	SM0=0;
	SM1=1;
	REN=1;
	ES=1;
}

void delay(unsigned int t)
{
	unsigned int x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

void ser() interrupt 4
{
	RI=0;
	num=num*256+SBUF;
}
