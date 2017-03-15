/*
IIC×ÜÏßÍ¨Ñ¶Á·Ï°
EEPROMµÄÊ¹ÓÃ
*/
#include <reg52.h>
sbit sda=P2^0;
sbit scl=P2^1;
sbit fm=P2^3;
void delay(unsigned int);
void init();
void start();
void stop();
unsigned char response();
void wcomf(unsigned char);
unsigned char rdataf();
unsigned char rdtaf();
void main()
{
	init();
	start();
	wcomf(0xA0);//Ñ°Ö·£¬Ð´
	response();
	wcomf(23);//Ð´´æ´¢µØÖ·
	response();
	wcomf(0x0f);//Ð´´æ´¢Êý¾Ý
	response();
	stop();

	start();
	wcomf(0xA0);//Ñ°Ö·£¬"Ð´"
	response();
	wcomf(23);//Ð´´æ´¢µØÖ·
	response();
	start();
	wcomf(0xA1);//Ñ°Ö·£¬¶Á
	response();
	P1=rdataf();
	sda=0;
	response();
	sda=1;
	stop();
	while(1);
}

void delay(unsigned int t)
{
	unsigned int x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}

void init()
{
	sda=1;
	scl=1;
}

void start()
{
	if(scl==1)
	{
		scl=0;
		delay(1);
	}
	sda=1;
	delay(1);
	while(!sda);
	scl=1;
	delay(1);
	while(!scl);
	sda=0;
	delay(1);
}

void stop()
{
/*	if(scl==1)
	{
		scl=0;
		delay(1);
	}*/
	sda=0;
	delay(1);
	scl=1;
	while(!scl);
	delay(1);
	sda=1;
	delay(1);
	while(!sda);
}

unsigned char response()
{
	unsigned char flag;
	delay(1);
	scl=1;
	delay(1);
	if(!sda)
	{
		fm=~fm;
		delay(10);//Ó¦´ð·¢Éù
		fm=~fm;
		flag=1;
	}
	else
	{
		flag=0;
	}
	scl=0;
	delay(1);
	return (flag);
}

void wcomf(unsigned char com)
{
	unsigned int i;
	unsigned char temp;
	temp=com;
	delay(1);
	for(i=0;i<8;i++)
	{
		scl=0;
		delay(1);
		if(0x80&temp)
		{
			sda=1;
		}
		else
		{
			sda=0;
		}
		temp=temp<<1;
		scl=1;
		delay(1);
	}
	scl=0;
	delay(1);
	sda=1;
	delay(1);
}

unsigned char rdataf()
{
	unsigned char dta;
	unsigned int i;
	scl=0;//???
	delay(1);
	dta=0x00;
	sda=1;
	delay(1);
	for(i=0;i<8;i++)
	{
		dta=dta<<1;
		scl=1;
		delay(1);
		if(sda)
			dta++;
		scl=0;
		delay(1);
	}
	return dta;
}
