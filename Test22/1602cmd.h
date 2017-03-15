/*1602cmd.h*/
/*For TX1C(11.0592kHz)*/
void _1602wcomf(unsigned char);
void _1602wdataf(unsigned char);
void _1602delay(unsigned char);
void _1602Cls();
void _1602SetCur(unsigned char,unsigned char);
void _1602CurHome();
void _1602EntryModeSet(unsigned char,unsigned char);
void _1602DisplayCtrl(unsigned char,unsigned char,unsigned char);
void _1602FuncSet(unsigned char,unsigned char,unsigned char);
void _1602WChar(unsigned char);
