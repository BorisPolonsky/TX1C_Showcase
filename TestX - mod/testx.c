#include <reg52.h>

void delayms(unsigned int);
unsigned char at1=255,tt=0x18,tt1=0x18,at2=255,tt2=0x08,act1,act2,M1_REF_OFF,M2_REF_OFF;

void main()
{
	M1_REF_OFF=6.0*256.0/tt;
	M2_REF_OFF=6.0*256.0/tt;
	at1=M1_REF_OFF;
	at2=M2_REF_OFF;
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
		delayms(30);
	}
	while(1);
}

void delayms(unsigned int t)//ÑÓÊ±Ô¼tºÁÃë
{
	unsigned int x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}