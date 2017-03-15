/*
DAøÿ÷∆µ∆¡¡∂»Ω•±‰
*/

#include <reg52.h>
unsigned char ch;
unsigned int flag;
sbit wela=P2^7;
void init();
void delay(unsigned int);
void main()
{
	init();
	while(1)
	{
		if(flag)
		{
			ch++;
			if(ch==0xff)
				flag=0;
			P0=ch;
			delay(20);
		}
		else
		{
			ch--;
			if(ch==0)
				flag=1;
			P0=ch;
			delay(20);
		}
	}
}

void init()
{
	ch=0x00;
	flag=1;
	wela=0;

	INT0=0;
	WR=0;
}

void delay(unsigned int t)
{
	unsigned int x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}
