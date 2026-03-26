#include "ultrasonic.h"

sbit TX = P1^0;  					// 发射引脚
sbit RX = P1^1;  					// 接收引脚

void Timer0Init(void)				// 12us@12MHz16位重载
{
  AUXR &= 0x7F;						// 定时器时钟12T模式
  TMOD &= 0xF0;						// 设置定时器模式
  TL0 = 0xF4;						// 设置定时初值
  TH0 = 0xFF;						// 设置定时初值
  TF0 = 0;							// 清除TF0标志
  TR0 = 0;							// 定时器0停止
}

unsigned char Wave_Recv(void)
{
  unsigned char ucDist, ucNum = 10;

  TX = 0;               //先关闭发射引脚
  TL0 = 0xF4;						// 设置定时初值
  TH0 = 0xFF;						// 设置定时初值
  TR0 = 1;							// 定时器0计时
  // TX引脚发送40KHz方波信号驱动超声波发送探头
  while(ucNum--)
  {
    while(!TF0);//等待溢出
    TX ^= 1;
    TF0 = 0;
  }
  TR0 = 0;              //暂时关闭定时器
  TL0 = 0;							// 设置定时初值
  TH0 = 0;							// 设置定时初值
  TR0 = 1;
  while(RX && !TF0);				// 等待收到脉冲，两种情况会出循环1.RX收到回来的信号变成0 2.发生溢出
  TR0 = 0;
  if(TF0)							// 发生溢出
  {
    TF0 = 0;
    ucDist = 255;
  }
  else							    // 计算距离
    ucDist = ((TH0<<8)+TL0)*0.017;//是340m/s下的数据
  return ucDist;
}
