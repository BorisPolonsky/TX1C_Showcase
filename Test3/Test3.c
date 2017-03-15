#include <reg52.h>
sbit dula=P2^6;
sbit wela=P2^7;
int a;
void main()
{
while(1)
{

dula=1;
P0=0x5B;
dula=0;
P0=0xFF;

wela=1;
P0=0xFE;
wela=0;
a=100;
while(a--);
dula=1;
P0=0x4F;
dula=0;
P0=0xFF;
wela=1;
P0=0x01;
wela=0;
a=100;
while(a--);
}
}
