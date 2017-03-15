/*
AD转换

WR由0变1开始转换？

不能完成实时转换
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
			WR=1;//--------开始转换
			wela=1;//
			P0=0xFF;
			wela=0;//-----CS=1；
			delay(50);//正在转换
			wela=1;//
			P0=0x7F;
			wela=0;//-----CS=0；
			RD=0;//可读
			delay(20);
			RD=1;//关闭可读
			wela=1;//
			P0=0xFF;
			wela=0;//-----CS=1；
		}
}

void init()
{
	wela=1;//
	P0=0xFF;
	wela=0;//-----CS=1；
	WR=1;
	RD=1;
}

void delay(unsigned int t)				
{
	unsigned int i,j;
	for(i=t;i>0;i--)		      //i=xms即延时约xms毫秒,Freq=11.0592MHz
		for(j=110;j>0;j--);
}
