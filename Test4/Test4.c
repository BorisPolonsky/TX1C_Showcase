/*
	This is just a Timer.
	Freq:11.0592MHz
*/
#include <reg52.h>
#include <intrins.h>
void delay(unsigned int t);
unsigned int h,m,s,tt;
unsigned char ch;
unsigned char code table[]={
	0x3f,0x06,0x5b,0x4f,0x66,
	0x6d,0x7d,0x07,0x7f,0x6f
};
sbit Beep=P2^3;
sbit dula=P2^6;
sbit wela=P2^7;
sbit bt1=P3^4;
sbit bt2=P3^5;
sbit bt3=P3^6;
sbit bt4=P3^7;
sbit c0=P0^0;
sbit c1=P0^1;
sbit c2=P0^2;
sbit c3=P0^3;
sbit c4=P0^4;
sbit c5=P0^5;
void main()
{
	EA=1;
	EX0=1;
	TCON=0x01;
	ET0=1;
	TMOD=0x01;
	TH0=(65536-46080)/256;
	TL0=(65536-46080)%256;
	ch=0xFE;
	P1=ch;
//	bt1=1;
//	bt2=1;
//	bt3=1;
//	bt4=1;
//	TR0=1;
	while(1)
	{
	if(tt==20)
		{
			tt=0;
			s++;
			ch=_crol_(ch,1);
			P1=ch;
		}
		if(s==60)
		{
			s=0;m++;
			if(m==60)
			{
				m=0;h++;
				if(h==24)
					h=0;
			}
		}
		P0=table[s%10];
		dula=1;
		dula=0;
		P0=~0x20;
		wela=1;
		wela=0;
		delay(2);

		P0=table[(s/10)%10];
		dula=1;
		dula=0;
		P0=~0x10;
		wela=1;
		wela=0;
		delay(2);

		P0=table[m%10];
		dula=1;
		dula=0;
		P0=~0x08;
		wela=1;
		wela=0;
		delay(2);

		P0=table[m/10];
		dula=1;
		dula=0;
		P0=~0x04;
		wela=1;
		wela=0;
		delay(2);
		
		P0=table[h%10];
		dula=1;
		dula=0;
		P0=~0x02;
		wela=1;
		wela=0;
		delay(2);
		
		P0=table[h/10];
		dula=1;
		dula=0;
		P0=~0x01;
		wela=1;
		wela=0;
		delay(2);
		if(!bt1)
		{
			delay(8);
			if(!bt1)
				{
					if(h==23)
						h=0;
					else
						h++;
					while(!bt1);
					delay(8);
					while(!bt1);
				}

		}
		if(!bt2)
		{
			delay(8);
			if(!bt2)
				{
					while(bt2);
					delay(8);
					while(bt2);
					if(m==59)
						{
							m=0;
							if(h==23)
								h=0;
							else
								h++;
						}
					else
						m++;
					while(!bt2);
					delay(8);
					while(!bt2);
				}
		}
		if(!bt3)
		{
			delay(8);
			if(!bt3)
				{
					while(bt3);
					delay(8);
					while(bt3);
					TR0=~TR0;
					while(!bt3);
					delay(8);
					while(!bt3);
				}
		}
		if(!bt4)
		{
			delay(8);
			if(!bt4)
				{
					while(bt4);
					delay(8);
					while(bt4);
					TR0=0;
					TH0=(65536-46080)/256;
					TL0=(65536-46080)%256;
					h=0;
					m=0;
					s=0;
					ch=0xFE;
					P1=0xFE;
					while(!bt4);
					delay(8);
					while(!bt4);
				}
		}
	}
}

void fun1() interrupt 0
{
	TR0=~TR0;
	P0=0xFF;
}

void clock() interrupt 1
{
	TH0=(65536-46080)/256;
	TL0=(65536-46080)%256;
	tt++;
}

void delay(unsigned int t)				
{
	unsigned int i,j;
	for(i=t;i>0;i--)		      //i=xms¼´ÑÓÊ±Ô¼xmsºÁÃë
		for(j=110;j>0;j--);
}
