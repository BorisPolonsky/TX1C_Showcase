/*
串口通信
大循环:接收，发送
定时器T1用作波特率发生器



BUG:只能发送有限位,中断产生位置影响程序功能
问题:T1计时器溢出与串口的关系
*/

#include <reg52.h>
unsigned int flag;//flag:接收，发送指示,1为接收
unsigned char ch;//存储接收的信息
void init();
void main()
{
	init();
	while(1)
	{
		if(flag)
		{
			while(!RI);
			RI=0;
			ch=SBUF;
			P1=0x0f;//接收后高四位灯亮
			flag=0;
		}
		else
		{
			SBUF=ch;
			while(!TI);
			TI=0;
			P1=0xf0;//发送后低四位灯亮
			flag=1;
		}
	}
}

void init()
{
	SM0=0;
	SM1=1;//-----方式1
	REN=1;//允许接收
	TR1=1;//启动定时器1
	TMOD=0x20;//设置定时器1为方式2
	TH1=0xFD;//TH存的初值自动存入TL1
	TL1=0xFD;
	EA=1;
//	ES=1;
	flag=1;
}

void fun() interrupt 4
{
	if(flag)
	{
		RI=0;
		ch=SBUF;
		P1=0x0f;
		flag=0;
	}
	else
	{
		TI=0;
		P1=0xf0;
		flag=1;
	}
}

