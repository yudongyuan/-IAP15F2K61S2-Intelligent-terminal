/*
  程序说明: DS1302驱动程序
  软件环境: Keil uVision 4.10 
  硬件环境: CT107单片机综合实训平台 8051，12MHz
  日    期: 2011-8-9
*/

#include "ds1302.h"
#include "intrins.h"
sbit SCK=P1^7;//时序		
sbit SDA=P2^3;//数据线
sbit RST = P1^3;//控制数据时间信号输入的开始与结束										

void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
	SCK=0;	_nop_();
	SDA=0;	_nop_();
	return (temp);			
}
// 设置时钟
//unsigned char code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};分别为秒，分，时，日，月，星期，年。
//unsigned char code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};分别为秒，分，时，日，月，星期，年。
void Set_RTC(unsigned char* pucRtc)
{
  unsigned char temp;

  Write_Ds1302_Byte(0x8E, 0); 							// WP=0：允许写操作
  temp = ((pucRtc[0]/10)<<4)+pucRtc[0]%10;
  Write_Ds1302_Byte(0x84, temp);						// 设置时
  temp = ((pucRtc[1]/10)<<4)+pucRtc[1]%10;
  Write_Ds1302_Byte(0x82, temp);						// 设置分
  temp = ((pucRtc[2]/10)<<4)+pucRtc[2]%10;
  Write_Ds1302_Byte(0x80, temp);						// 设置秒
  Write_Ds1302_Byte(0x8E, 0x80);  						// WP=1：禁止写操作
}
// 读取时钟
void Read_RTC(unsigned char* pucRtc)
{
  unsigned char temp;

  temp = Read_Ds1302_Byte(0x85);						// 读取时
  pucRtc[0] = (temp>>4)*10+(temp&0xf);//0xf就是0x0f前面的0可以省后面的不行
  temp = Read_Ds1302_Byte(0x83);						// 读取分
  pucRtc[1] = (temp>>4)*10+(temp&0xf);
  temp = Read_Ds1302_Byte(0x81);						// 读取秒
  pucRtc[2] = (temp>>4)*10+(temp&0xf);
}
