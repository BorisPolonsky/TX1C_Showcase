/*
¾ØÕó¼üÅÌ²âÊÔ
*/
#include <reg52.h>
sbit dula=P2^6;
sbit wela=P2^7;
unsigned char temp;
unsigned char code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};

void delay(unsigned int);
void init();
void main()
{
	init();
	while(1)
	{
		P3=0xfe;
		if((P3&0xf0)!=0xf0)
		{
			delay(10);
			if((P3&0xf0)!=0xf0)
			{
				switch(P3&0xf0)
				{
				case 0xe0:
					P0=table[12];
					break;
				case 0xd0:
					P0=table[13];
					break;
				case 0xb0:
					P0=table[14];
					break;
				case 0x70:
					P0=table[15];
					break;
				default:
					P1=~P1;
				}
				while((P3&0xf0)!=0xf0);
			}
		}

		P3=0xfd;
		if((P3&0xf0)!=0xf0)
		{
			delay(10);
			if((P3&0xf0)!=0xf0)
			{
				switch(P3&0xf0)
				{
				case 0xe0:
					P0=table[8];
					break;
				case 0xd0:
					P0=table[9];
					break;
				case 0xb0:
					P0=table[10];
					break;
				case 0x70:
					P0=table[11];
					break;
				default:
					P1=~P1;
				}
				while((P3&0xf0)!=0xf0);
			}
		}

		P3=0xfb;
		if((P3&0xf0)!=0xf0)
		{
			delay(10);
			if((P3&0xf0)!=0xf0)
			{
				switch(P3&0xf0)
				{
				case 0xe0:
					P0=table[4];
					break;
				case 0xd0:
					P0=table[5];
					break;
				case 0xb0:
					P0=table[6];
					break;
				case 0x70:
					P0=table[7];
					break;
				default:
					P1=~P1;
				}
				while((P3&0xf0)!=0xf0);
			}
		}

		P3=0xf7;
		if((P3&0xf0)!=0xf0)
		{
			delay(10);
			if((P3&0xf0)!=0xf0)
			{
				switch(P3&0xf0)
				{
				case 0xe0:
					P0=table[0];
					break;
				case 0xd0:
					P0=table[1];
					break;
				case 0xb0:
					P0=table[2];
					break;
				case 0x70:
					P0=table[3];
					break;
				default:
					P1=~P1;
				}
				while((P3&0xf0)!=0xf0);
			}
		}
	}
}


void delay(unsigned int z)
{
	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);	
}
void init()
{
	wela=1;
	P0=0x00;
	wela=0;
	dula=1;
	P0=table[0];
}
