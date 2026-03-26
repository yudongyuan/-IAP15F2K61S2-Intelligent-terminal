#include "key.h"

unsigned char Key_Read(void)
{
  unsigned int Key_New;
	unsigned char Key_Val;
	
//	ET0=0;防止冲突
	P44=0;P42=1;P35=1;P34=1;
	Key_New= P3;
  P44=1;P42=0;
  Key_New= (Key_New<<4)|(P3&0x0f);
  P42=1;P35=0;
  Key_New= (Key_New<<4)|(P3&0x0f);
  P35=1;P34=0;
  Key_New= (Key_New<<4)|(P3&0x0f);
  P34=1;
	switch(~Key_New)//这里要取反！！！！！！！
	{
	  case 0x8000:Key_Val =4;break;
	  case 0x4000:Key_Val =5;break;
	  case 0x2000:Key_Val =6;break;
	  case 0x1000:Key_Val =7;break;
	  case 0x0800:Key_Val =8;break;
		case 0x0400:Key_Val =9;break;
		case 0x0200:Key_Val =10;break;
		case 0x0100:Key_Val =11;break;
		case 0x0080:Key_Val =12;break;
		case 0x0040:Key_Val =13;break;
		case 0x0020:Key_Val =14;break;
		case 0x0010:Key_Val =15;break;
		case 0x0008:Key_Val =16;break;
		case 0x0004:Key_Val =17;break;
		case 0x0002:Key_Val =18;break;
		case 0x0001:Key_Val =19;break;
		default :Key_Val=0;
	}
//	P3=0xff;
//	ET0=1;
return Key_Val;
}

//独立按键
//unsigned char Key_Read()
//{
//	unsigned char temp = 0;
//	if(P33 == 0) temp = 4;
//	if(P32 == 0) temp = 5;
//	if(P31 == 0) temp = 6;
//	if(P30 == 0) temp = 7;
//	return temp;
//}