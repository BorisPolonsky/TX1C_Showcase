/*1602cmd.h*/
/*For TX1C(11.0592kHz)*/
#include <reg52.h>
#include "1602cmd.h"

void _1602wcomf(unsigned char com)//Write Command
{
	P0=com;
	T1=0;//RS=L
	_1602delay(5);
	T0=1;//E=1
	_1602delay(5);
	T0=0;
}

void _1602wdataf(unsigned char dat)//Write Data
{
	P0=dat;
	T1=1;//RS=H
	_1602delay(5);
	T0=1;//E=1
	_1602delay(5);
	T0=0;
}
void _1602delay(unsigned char t)
{
	unsigned char i;
	for(i=t;i;i--);

/*time table (unit:10^(-6)s)
		_1062delay(0);//9.77
		_1062delay(1);//15.19
		_1062delay(2);//21.70
		_1062delay(3);//28.22
		_1062delay(4);//34.72
		_1062delay(5);//41.23
		_1062delay(6);//47.75
		_1062delay(7);//54.26
		_1062delay(8);//60.77
*/
}

void _1602Cls()//Clear Screen
{
	_1602wcomf(0x01);
}

void _1602SetCur(unsigned char x,unsigned char y)//Set Cursor
{
	if(x<=0x27)
	{
		switch(y)
		{
			case 0:
			_1602wcomf(0x80+x);
			break;
			case 1:
			_1602wcomf(0xC0+x);
			break;
		}
	}
}

void _1602CurHome()
{
	_1602wcomf(0x02);
}

void _1602EntryModeSet(unsigned char CurShR,unsigned char DisplayShL)
//CurShR:Cursor Shift Right Automatically
//DisplayShL:Display Shift Left Automatically
{
	unsigned char com=0x04;
	if(CurShR)
		com=com|0x02;
	if(DisplayShL)
		com=com|0x01;
	_1602wcomf(com);
}

void _1602DisplayCtrl(unsigned char DisplayOn,unsigned char CursorOn,unsigned char CharBlink)
{
	unsigned char com=0x08;
	if(DisplayOn)
		com=com|0x04;
	if(CursorOn)
		com=com|0x02;
	if(CharBlink)
		com=com|0x01;
	_1602wcomf(com);	
}

void _1602FuncSet(unsigned char DataLen_8,unsigned char LineNum_2,unsigned char Font)
{
	unsigned char com=0x20;
	if(DataLen_8)
		com=com|0x10;
	if(LineNum_2)
		com=com|0x08;
	if(Font)
		com=com|0x04;
	_1602wcomf(com);
}

void _1602WChar(unsigned char Ch)
{
	_1602wdataf(Ch);
}


