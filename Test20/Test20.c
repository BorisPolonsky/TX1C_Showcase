/*
Oscilloscope
Baud 9600Hz
8N1
*/
#include <reg52.h>
volatile unsigned char OCW,CHi,STAT1,STAT2,temp,rtemp;

/*OCW:
D7D6=OCWX

OCW0:
D7D6:00

D2-D0 i
D3 Run/Stop
D5D4
0*:NO TRIG
10:TRIG RISING EDGE
11:TRIG DESCENDING EDGE

OCW1
6 bits in STAT2 for delay()


STAT1

D2-D0 i
D3 Run/Stop
D5D4
0*:NO TRIG
10:TRIG RISING EDGE
11:TRIG DESCENDING EDGE

D7D6:Former PIN status
00 LOW
01 HIGH
1* UNKNOWN
*/
void init();
void delay(unsigned char);
void main()
{
	init();
	while(1)
	{
		while(!(STAT1&0x08));
		temp=P2;
		if(temp&(1<<CHi))
		{
			if((STAT1&0xC0)==0)
			{
				SBUF='/';
				while(!TI);
				TI=0;
				if((STAT1&0x30)==0x20)
					STAT1=STAT1&0xF7;
			}
			STAT1=STAT1&0x7F|0x40;
			SBUF='-';
			while(!TI);
			TI=0;
		}
		else
		{
			if((STAT1&0xC0)==0x40)
			{
				SBUF='\\';
				while(!TI);
				TI=0;
				if((STAT1&0x30)==0x30)
					STAT1=STAT1&0xF7;
			}
			STAT1=STAT1&0x3F;
			SBUF='_';
			while(!TI);
			TI=0;
		}
		delay(STAT2);
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
	STAT1=0xC8;
	STAT2=100;
	P1=0xFE;
}

void Rev() interrupt 4
{
	if(RI)
	{
		RI=0;
		rtemp=SBUF;
		switch(rtemp>>6)
		{
		case 0:
			STAT1=rtemp|0x80;
			CHi=STAT1&0x07;
			P1=~(1<<CHi);
			break;
		case 1:
			STAT2=rtemp&0x3F;
			break;
		}
	}
}

void delay(unsigned char n)
{
unsigned char i,j;                          ;
	for(i=0;i<n;i++)
		for(j=0;j<255;j++);
}
