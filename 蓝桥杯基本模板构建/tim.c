#include "tim.h"

void Cls_p(void)
{
  P0=0xff;
	P2=P2&0x1f|0x80;
  P2=P2&0x1f;
	P0=0;
  P2=P2&0x1f|0xA0;
	P2=P2&0x1f;
}

void Led_Disp(unsigned char Led_v)
{
  P0=~Led_v;
  P2=P2&0x1f|0x80;
	P2=P2&0x1f;
}

void Timer1Init(void)		//@12.000MHz 16位自动重载 12T 1ms 定时器T1
{
	AUXR &= 0xBF;		
	TMOD &= 0x0F;	
	TL1 = 0x18;		
	TH1 = 0xFC;		
	TF1 = 0;		
	TR1 = 1;	
	ET1 = 1;
	EA  = 1;
}
//void PCA_Init(void)//溢出
//{
//	CMOD = 0x01;
//	CCON = 0x00;//CR = 0 CF = 0;
//	
//	CH = 0xFC;
//	CL = 0x18;
////	CCAP0L = 0xE8;
////	CCAP0H = 0x03;
////	CCAPM0 = 0x49; 
//	CR = 1;
//	EA = 1;
//}