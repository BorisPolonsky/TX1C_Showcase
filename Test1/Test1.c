#include <reg52.h>
#include <intrins.h>
sbit L1=P1^0;
sbit L2=P1^1;
sbit L3=P1^2;
sbit L4=P1^3;
sbit L5=P1^4;
sbit L6=P1^5;
sbit L7=P1^6;
sbit L8=P1^7;
int a;
void main()
{
while(1)
{
L8=1;
L1=0;
a=50000;
while(a--);
L1=1;
L2=0;
a=50000;
while(a--);
L2=1;
L3=0;
a=50000;
while(a--);
L3=1;
L4=0;
a=50000;
while(a--);
L4=1;
L5=0;
a=50000;
while(a--);
L5=1;
L6=0;
a=50000;
while(a--);
L6=1;
L7=0;
a=50000;
while(a--);
L7=1;
L8=0;
a=50000;
while(a--);
}
}
