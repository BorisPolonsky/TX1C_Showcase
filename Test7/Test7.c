/*
ADת��

WR��0��1��ʼת����

�������ʵʱת��
*/

#include <reg52.h>
sbit wela=P2^7;
void init();
void delay(unsigned int);

void main()
{
	init();
	while(1)
		{
			WR=0;//
			delay(20);
			WR=1;//--------��ʼת��
			wela=1;//
			P0=0xFF;
			wela=0;//-----CS=1��
			delay(50);//����ת��
			wela=1;//
			P0=0x7F;
			wela=0;//-----CS=0��
			RD=0;//�ɶ�
			delay(20);
			RD=1;//�رտɶ�
			wela=1;//
			P0=0xFF;
			wela=0;//-----CS=1��
		}
}

void init()
{
	wela=1;//
	P0=0xFF;
	wela=0;//-----CS=1��
	WR=1;
	RD=1;
}

void delay(unsigned int t)				
{
	unsigned int i,j;
	for(i=t;i>0;i--)		      //i=xms����ʱԼxms����,Freq=11.0592MHz
		for(j=110;j>0;j--);
}
