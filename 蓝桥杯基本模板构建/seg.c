#include "seg.h"

void Seg_Tran(unsigned char *Seg_Buf,unsigned char *Seg_Code)
{
  unsigned char i,j=0,temp;
	for(i=0;i<8;i++,j++)
	{
	  switch(Seg_Buf[j])//这个地方是j不是i，因为j代表字符串的位置，i是转换好的码，所以前面都是j最后是i
		{
		  case '0': temp=0xc0; break;
		  case '1': temp=0xf9; break;
		  case '2': temp=0xa4; break;
		  case '3': temp=0xb0; break;
	   	case '4': temp=0x99; break;
	  	case '5': temp=0x92; break;
			case '6': temp=0x82; break;
			case '7': temp=0xf8; break;
			case '8': temp=0x80; break;
			case '9': temp=0x90; break;
			case '-': temp=0xbf; break;
			case ' ': temp=0xff; break;
			default: temp=0xff;//注意是0xff
		}
		if(Seg_Buf[j+1]=='.')
		{
		  temp=temp&0x7f;//这里是与，但是我写错成或了
			j++;//注意是j++
		}
		Seg_Code[i]=temp;
	}
}

void Seg_Disp(unsigned char *Seg_Code,unsigned char Seg_Pos)
{
  P0=0xff;
	P2=P2&0x1f|0xe0;
  P2=P2&0x1f;
	P0=1<<Seg_Pos;
  P2=P2&0x1f|0xc0;
  P2=P2&0x1f;
  P0=Seg_Code[Seg_Pos];
	P2=P2&0x1f|0xe0;
  P2=P2&0x1f;
}





