/*
1-Wire Bus������ϰ
ͨ����������Ψһ����DS18B20����Һ�����������ǰ�¶�
*/
#include <reg52.h>

sbit _18B20=P2^2;
sbit fm=P2^3;
sbit wela=P2^7;
void delay(unsigned char);
void delayms(unsigned int);
void _1602init();
void _1602wcomf(unsigned char);
void _1602wdataf(unsigned char);

void reset();
void r_presence();
void wrbit(unsigned char);
unsigned char rbit();
void wr_byte(unsigned char);
unsigned char r_byte();
unsigned char code table1[]="Temperature";
unsigned char table2[3];//������ASCII��

void main()
{
	unsigned char lsb,msb;
	unsigned int tp,i;//t�¶�
	_1602init();
	while(1)
	{
		reset();
		r_presence();
		wr_byte(0xcc);//SKIP ROM COMMAND
		wr_byte(0x44);//ת���¶�
		delay(1000);//ת�����ٻ�750ms
		reset();
		r_presence();
		wr_byte(0xcc);//SKIP ROM COMMAND
		wr_byte(0xbe);//read scratchpad
		lsb=r_byte();
		msb=r_byte();
		reset();
		r_presence();
		tp=msb;
		tp=tp<<8;
		tp=tp+lsb;
//		tp=tp>>4;
		table2[0]=((tp>>4)%10)+'0';
		table2[1]=(((tp>>4)/10)%10)+'0';
		table2[2]=(((tp>>4)/100)%10)+'0';
	
		_1602wcomf(0x80);
		for(i=0;i<11;i++)
			_1602wdataf(table1[i]);
		
		_1602wcomf(0x80+0x40);
		_1602wdataf(table2[2]);
		_1602wdataf(table2[1]);
		_1602wdataf(table2[0]);
		tp=tp&0x000F;//��С������
		_1602wdataf('.');
		_1602wdataf(((tp*625/1000)%10)+'0');
		_1602wdataf(((tp*625/100)%10)+'0');
		_1602wdataf(((tp*625/10)%10)+'0');
		_1602wdataf((tp*625%10)+'0');
		_1602wdataf('d');
		_1602wdataf('C');
		delayms(500);
	}
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

void _1602init()
{
	P0=0xFF;
	wela=0;
	_1602wcomf(0x38);
	_1602wcomf(0x0c);
	_1602wcomf(0x06);
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
