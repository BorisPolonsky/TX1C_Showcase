#include <reg52.h>
unsigned char a;
unsigned int b;
void main()
{
a=0x01;
while(1)
{
while(a!=0x80)
{
P1=~a;
b=50000;
//while(b--);
a=a<<1;
}
while(a!=0x01)
{
P1=~a;
b=50000;
//while(b--);
a=a>>1;
}
}

}