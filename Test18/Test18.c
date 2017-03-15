/*
tt,tt1,tt2>=7
MStart Freq:300Hz
*/
#include <reg52.h>

sbit cp1=P1^0;
sbit cp2=P1^1;
sbit wela=P2^7;
sbit act1=P1^4;
sbit act2=P1^5;
sbit M1_OFF=P1^6;
sbit M2_OFF=P1^7;

unsigned char tt1,tt2,t1,t2,i,tt,Data,Comd,Data,at1,at2,M1_REF_OFF,M2_REF_OFF;
unsigned char code str[]={"T0:D1:D2:Set"};
void delay(unsigned char);
void delayms(unsigned int);
void init();
void MStartup();
void MShutdown();
void MPCH_1();
void MPCH_2();
void main()
{
	init();

	for(i=0;i<3;i++)
	{
		SBUF=str[i];
		while(!TI);
		TI=0;
	}

	RI=0;
	while(!RI);
	i=SBUF;
	RI=0;
	if(i>0x22)
	tt=i;

	for(i=3;i<6;i++)
	{
		SBUF=str[i];
		while(!TI);
		TI=0;
	}


	while(!RI);
	i=SBUF;
	RI=0;
	if(tt*255>1536)
	tt1=i;

	for(i=6;i<9;i++)
	{
		SBUF=str[i];
		while(!TI);
		TI=0;
	}

	while(!RI);
	i=SBUF;
	RI=0;
	if(tt*255>1536)
	tt2=i;

	for(i=9;i<12;i++)
	{
		SBUF=str[i];
		while(!TI);
		TI=0;
	}

//	TH1=256-110;//9.946Œ¢√Î
//	TL1=256-110;


//	REN=0;
//	ES=0;
//	TR1=0;
	TL0=256-tt;
	TH0=256-tt;
	ET0=1;
	M1_OFF=0;
	M2_OFF=0;
	M1_REF_OFF=6.0*256.0/tt;
	M2_REF_OFF=6.0*256.0/tt;
	while(1)
	{
		if(RI)
		{
			Comd=SBUF;
			RI=0;

			switch(Comd)
			{
				case 0x00://default
				//Comd=Data;
				break;

				case 0xAE://Activate
				MStartup();
				break;

				case 0xCE://Disactivate
				MShutdown();
				break;

				case 0xB1://Set tt1
				while(!RI);
				Data=SBUF;
				RI=0;
				if(Data!=0)
				{
					tt1=Data;
					MPCH_1();
					Data=0;
				}
				break;
				
				case 0xB2://Set tt2
				while(!RI);
				Data=SBUF;
				RI=0;
				if(Data!=0)
				{
					tt2=Data;
					MPCH_2();
					Data=0;
				}
				break;
				default:
				;
			}
		}			
	}
}

void init()
{
	TMOD=0x22;
	TH1=0xFD;
	TL1=0xFD;

	SCON=0x10;
	SM0=0;
	SM1=1;
	EA=1;
	ET0=1;
	ES=0;
	tt=0x23;
	tt1=16;
	tt2=16;
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

void delayms(unsigned int t)//—” ±‘ºt∫¡√Î
{
	unsigned int x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

void MStartup()
{
	at1=M1_REF_OFF;
	at2=M2_REF_OFF;
	TR0=1;
	act1=0;
	act2=0;
	M1_OFF=1;
	M2_OFF=1;
	for(;at1>tt1||at2>tt2;)
	{
		if(at1>tt1)
			at1--;
		else
			act1=1;
		if(at2>tt2)
			at2--;
		else
			act2=1;
		delayms(75);
	}
	at1=tt1;
	act1=1;
	at2=tt2;
	act2=1;
}

void MShutdown()
{
	act1=0;
	act2=0;
	for(;at1<M1_REF_OFF||at2<M2_REF_OFF;)
	{
		if(at1<M1_REF_OFF)
			at1++;
		else
		{
			act1=1;
			M1_OFF=0;
		}
		if(at2<M2_REF_OFF)
			at2++;
		else
		{
			act2=1;
			M2_OFF=0;
		}
		delayms(40);
	}
	TR0=0;
	
}

void MPCH_1()
{
	if(tt1!=0)
	{
		act1=0;
		for(;tt1>at1;at1++)
			delayms(80);
		for(;tt1<at1;at1--)
			delayms(80);
		act1=1;
	}

}

void MPCH_2()
{
	if(tt2!=0)
	{
		act2=0;
		for(;tt2>at2;at2++)
			delayms(80);
		for(;tt2<at2;at2--)
			delayms(80);
		act2=1;
	}
}


void clock() interrupt 1
{
	t1++;
	t2++;
	if(tt!=0)
	{
		if(t1>=at1)
		{
			cp1=~cp1;
			t1=t1-at1;
		}

		if(t2>=at2)
		{
			cp2=~cp2;
			t2=t2-at2;
		}
	}
}//>35Œ¢√Î

