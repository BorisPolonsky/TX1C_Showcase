/*
串口通信实验
以4800bps从计算机发送任一字节数据，当单片机收到该数据后，在此数据前加上一序号(16进制)然后连同此数据一起发送至计算机，当序号超过255时归零。
*/
#include <reg52.h>
unsigned int num;//序号
unsigned char ch;//用于存储收到的一字节数据
void init();
void main()
{
	init();
	while(1)
	{
		while(!RI);
		RI=0;
		ch=SBUF;
		SBUF=num++;
		while(!TI);
		TI=0;
		SBUF=ch;
		while(!TI);
		TI=0;
	}
}

void init()
{
	TMOD=0x20;
	TL1=0xFA;
	TH1=0xFA;
	TR1=1;

	SM0=0;
	SM1=1;
	REN=1;
	EA=1;
}
