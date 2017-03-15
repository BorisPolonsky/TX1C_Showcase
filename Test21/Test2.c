/*
Single Motor Test
*/
#include <reg52.h>
unsigned char temp,TDR,RDR=0,cp=0;//DR - Duty Ratio. 
sbit PWM=P1^0;
void init();
void Motor_Ctrl();
void Motor_SpdUp();
void Motor_SlDn();
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
		Delayms(100);
	}
}

void Motor_SlDn()
{
	while(RDR>TDR)
	{
		RDR--;
		Delayms(100);
	}
}

void Delayms(unsigned int t)
{
	unsigned int x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

void IR() interrupt 1
{
	cp++;
	if(cp>RDR)
	{
		PWM=0;
		if(cp==101)
		{
			cp=1;
			PWM=1;
		}
	}
	else
	PWM=1;
}


