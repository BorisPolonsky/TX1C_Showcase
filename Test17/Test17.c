/**/
#include <reg52.h>

sbit X=P1^0;
sbit wela=P2^7;
unsigned int tt1,tt2,t1,t2,i,tt;
unsigned char code str[]={"  T1:RPM2:"};
unsigned char tch[2][6];
unsigned char ch;//
void delay(unsigned char);
void delayms(unsigned int);
void _1602wcomf(unsigned char);
void _1602wdataf(unsigned char);
void _1602init();
void init();
void MStartup();
void main()
{
	init();

	for(i=0;i<5;i++)
	{
		SBUF=str[i];
		while(!TI);
		TI=0;
	}

	RI=0;
	while(!RI);
	tt=SBUF;
	RI=0;

	SBUF=tt;
	while(!TI);
	TI=0;

	for(i=5;i<9;i++)
	{
		SBUF=str[i];
		while(!TI);
		TI=0;
	}
//	TH1=256-110;//9.946Î¢Ãë
//	TL1=256-110;


//	REN=0;
//	ES=0;
//	TR1=0;
	MStartup();
	TL0=256-tt;
	TH0=256-tt;
	ET0=1;
	TR0=1;
	while(1)
	{	
		if(RI==1)
		{
			tt=SBUF;
			if(tt!=0)
				TH0=256-tt;
			RI=0;
		}
	}
}

void init()
{
	TMOD=0x22;
	TH1=0xFD;//9.946Î¢Ãë
	TL1=0xFD;

	SCON=0x10;
	SM0=0;
	SM1=1;
	EA=1;
	ET0=1;
	ES=0;
	tt1=1000;
	tt2=1000;
	TR1=1;
}

void delay(unsigned char t)
{
	unsigned char i;
	for(i=t;i;i--);

/*time table (unit:10^(-6)s)
		delay(0);//9.77
		delay(1);//15.19
		delay(2);//21.70
		delay(3);//28.22
		delay(4);//34.72
		delay(5);//41.23
		delay(6);//47.75
		delay(7);//54.26
		delay(8);//60.77
*/
}

void delayms(unsigned int t)//ÑÓÊ±Ô¼tºÁÃë
{
	unsigned int x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

void _1602wcomf(unsigned char com)//Ð´Ö¸Áî
{
	P0=com;
	T1=0;//RS=L
	delay(5);
	T0=1;//E=1
	delay(5);
	T0=0;
}

void _1602wdataf(unsigned char dat)//Ð´Êý¾Ý
{
	P0=dat;
	T1=1;//RS=H
	delay(5);
	T0=1;//E=1
	delay(5);
	T0=0;
}

void _1602init()
{
	P0=0xFF;
	wela=0;
	_1602wcomf(0x38);
	_1602wcomf(0x0c);
	_1602wcomf(0x06);
	_1602wcomf(0x01);
	delay(10);
}


void MStartup()
{}

void clock() interrupt 1
{
	if(tt!=0)
		P1=~P1;
}
