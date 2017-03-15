/*
Single Motor Test
1602 Display
*/
#include <reg52.h>
#include "1602cmd.h"
unsigned char temp,TDR,RDR=0,cp=0;//DR - Duty Ratio. 
code unsigned char Line1[]="Duty Ratio:";
sbit PWM=P2^0;
sbit wela=P2^7;
void init();
void Motor_Ctrl();
void Motor_SpdUp();
void Motor_SlDn();

void _1602init();
void RDRUpdate();
void Delayms(unsigned int);
void main()
{
	init();
	while(1)
	{
		while(!RI);
		temp=SBUF;
		RI=0;
		if(temp>100)
		;
		else
		{
			TDR=temp;
			Motor_Ctrl();
		}
	}
}

void init()
{
	wela=0;
	_1602init();
	REN=1;
	SM1=1;
	PCON=PCON&0x7F;//SMOD=0
	TH1=0xFD;
	TL1=0xFD;
	TMOD=0x22;
	TR1=1;

	TH0=100;
	TL0=100;
	TR0=1;
	ET0=1;

	PWM=0;

	EA=1;
}
void Motor_Ctrl()
{
	if(RDR<TDR)
		Motor_SpdUp();
	if(RDR>TDR)
		Motor_SlDn();
}

void Motor_SpdUp()
{
	while(RDR<TDR)
	{
		RDR++;
		RDRUpdate();
		Delayms(100);
	}
}

void Motor_SlDn()
{
	while(RDR>TDR)
	{
		RDR--;
		RDRUpdate();
		Delayms(100);
	}
}

void Delayms(unsigned int t)
{
	unsigned int x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

void _1602init()
{
	unsigned char i;
//	_1602Cls();
	_1602EntryModeSet(1,0);
	_1602FuncSet(1,1,0);
	_1602DisplayCtrl(1,0,0);

	_1602SetCur(0,0);
	for(i=0;i<11;i++)
		_1602WChar(Line1[i]);
	_1602SetCur(0,1);
	for(i=0;i<3;i++)
		_1602WChar('0');
	_1602WChar('%');	
}

void RDRUpdate()
{
	_1602SetCur(0,1);
	_1602WChar(RDR/100+0x30);
	_1602WChar(RDR/10%10+0x30);
	_1602WChar(RDR%10+0x30);
}

void IR() interrupt 1
{
	cp++;
	if(cp==100)
		cp=0;
	if(cp<RDR)
		PWM=1;
	else
		PWM=0;
}
