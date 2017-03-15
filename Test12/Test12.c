#include <reg52.h>
sbit wela=P2^7;
void delay(unsigned int);
void init();
void wcomf(unsigned char);
void wdataf(unsigned char);
unsigned char code table1[]="0123456789";
unsigned char code table2[]="Good Day!";
unsigned int h,m,s,tt;
sbit bt1=P3^4;
sbit bt2=P3^5;
sbit bt3=P3^6;
sbit bt4=P3^7;
void main()
{
	init();
	while(1)
	{
		if(tt>=20)
		{
			tt=0;
			s++;
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
		}
		wcomf(0x80+0x46);
		wdataf(table1[s/10]);
		wdataf(table1[s%10]);

		wcomf(0x80+0x43);
		wdataf(table1[m/10]);
		wdataf(table1[m%10]);

		wcomf(0x80+0x40);
		wdataf(table1[h/10]);
		wdataf(table1[h%10]);
	}
}

void init()
{
	int i;
	P0=0xFF;
	wela=0;
	wcomf(0x38);
	wcomf(0x0c);
	wcomf(0x06);

	EA=1;
	EX0=1;
	TCON=0x01;
	ET0=1;
	TMOD=0x01;
	TH0=(65536-46080)/256;
	TL0=(65536-46080)%256;

	wcomf(0x80);
	for(i=0;i<9;i++)
		wdataf(table2[i]);
	wcomf(0x80+0x40);
	wdataf('0');
	wdataf('0');
	wdataf(':');
	wdataf('0');
	wdataf('0');
	wdataf(':');
	wdataf('0');
	wdataf('0');

	TR0=1;
}

void wcomf(unsigned char com)//Ð´Ö¸Áî
{
	P0=com;
	T1=0;//RS=L
	delay(5);
	T0=1;//E=1
	delay(5);
	T0=0;
}

void wdataf(unsigned char dat)//Ð´Êý¾Ý
{
	P0=dat;
	T1=1;//RS=H
	delay(5);
	T0=1;//E=1
	delay(5);
	T0=0;
}

void delay(unsigned int t)
{
	unsigned int x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

void clock() interrupt 1
{
	TH0=(65536-46080)/256;
	TL0=(65536-46080)%256;
	tt++;
}
