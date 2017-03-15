/*
1-Wire Bus������ϰ
��ȡDS18B20�����кţ����ɴ��ڷ���
*/
#include <reg52.h>

sbit _18B20=P2^2;
sbit fm=P2^3;
sbit wela=P2^7;
void delay(unsigned char);
void delayms(unsigned int);
void init();

void reset();
void r_presence();
void wrbit(unsigned char);
unsigned char rbit();
void wr_byte(unsigned char);
unsigned char r_byte();
unsigned char table2[8];//��FAMILY CODE�����кš�CRC

void main()
{
	unsigned char i1,i2;
	init();
	
	reset();
	r_presence();
	wr_byte(0x33);//READ ROM COMMAND
	
	for(i1=0;i1<8;i1++)
	{
		for(i2=0;i2<8;i2++)
		{
			table2[i1]=table2[i1]>>1;
			if(rbit())
				table2[i1]=table2[i1]|0x80;
		}
	}
	for(i1=0;i1<8;i1++)
	{
		SBUF=table2[i1];
		while(!TI);
		TI=0;
	}
	while(1);
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

void delayms(unsigned int t)//��ʱԼt����
{
	unsigned int x,y;
	for(x=t;x>0;x--)
		for(y=110;y>0;y--);
}


void _1602wcomf(unsigned char com)//дָ��
{
	P0=com;
	T1=0;//RS=L
	delay(5);
	T0=1;//E=1
	delay(5);
	T0=0;
}

void _1602wdataf(unsigned char dat)//д����
{
	P0=dat;
	T1=1;//RS=H
	delay(5);
	T0=1;//E=1
	delay(5);
	T0=0;
}

void init()
{
	TH1=0xFD;//TH��ĳ�ֵ�Զ�����TL1
	TL1=0xFD;
	TMOD=0x20;////���ö�ʱ��1Ϊ��ʽ2
	TR1=1;
	SM0=0;
	SM1=1;
	REN=1;
	EA=1;
}

void reset()
{
	_18B20=0;
	delay(75);//496.96΢��
	_18B20=1;
}

void r_presence()
{
	unsigned char i;
	delay(8);//60.77΢��
	for(i=100;i;i--)
	{
		if(!_18B20)
			fm=1;//����fm=0;Ϊ�յ�Ӧ������������
	}//435.11-543.62΢��
	fm=1;
}

void wrbit(unsigned char bool)
{
	if(bool)
	{
		_18B20=0;
		delay(0);
		_18B20=1;
		delay(11);
	}
	else
	{
		_18B20=0;
		delay(11);
		_18B20=1;
	}
}

unsigned char rbit()
{
	_18B20=0;	
	_18B20=1;
	delay(0);
	if(_18B20)
	{
		delay(8);
		return(1);
	}
	else
	{
		delay(8);
		return(0);
	}
}

void wr_byte(unsigned char dat)//�ӵ�λ��ʼд
{
	unsigned int i,temp;
	temp=dat;
	for (i=0;i<8;i++)
	{
		if(0x01&temp)	
			wrbit(1);
		else
			wrbit(0);
		temp=temp>>1;
	}	
}

unsigned char r_byte()//�ӵ�λ��ʼ��
{
	unsigned char byte,i;

	for(i=0;i<8;i++)
	{
		byte=byte>>1;
		if(rbit())
			byte=0x80|byte;
	}
	return byte;
}
