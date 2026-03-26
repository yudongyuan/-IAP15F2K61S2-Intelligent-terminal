#include "iic.h"
#include "intrins.h"//内嵌函数，其目的为使用如nop此类汇编内容
#define DELAY_TIME 5
sbit SDA = P2^1;
sbit SCL = P2^0;
//I2C总线内部延时函数
void IIC_Delay(unsigned char i)
{
    do{_nop_();}
    while(i--);        
}

//I2C总线启动信号
void IIC_Start(void)
{
    SDA = 1;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 0;
    IIC_Delay(DELAY_TIME);
    SCL = 0;	
}

//I2C总线停止信号
void IIC_Stop(void)
{
    SDA = 0;
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//发送应答或非应答信号
void IIC_SendAck(bit ackbit)
{
    SCL = 0;
    SDA = ackbit;  					
    IIC_Delay(DELAY_TIME);
    SCL = 1;
    IIC_Delay(DELAY_TIME);
    SCL = 0; 
    SDA = 1;
    IIC_Delay(DELAY_TIME);
}

//等待应答
bit IIC_WaitAck(void)
{
    bit ackbit;
	
    SCL  = 1;
    IIC_Delay(DELAY_TIME);
    ackbit = SDA;
    SCL = 0;
    IIC_Delay(DELAY_TIME);
    return ackbit;
}

//I2C总线发送一个字节数据
void IIC_SendByte(unsigned char byt)
{
    unsigned char i;

    for(i=0; i<8; i++)
    {
        SCL  = 0;
        IIC_Delay(DELAY_TIME);
        if(byt & 0x80) SDA  = 1;
        else SDA  = 0;
        IIC_Delay(DELAY_TIME);
        SCL = 1;
        byt <<= 1;
        IIC_Delay(DELAY_TIME);
    }
    SCL  = 0;  
}

//I2C总线接收一个字节数据
unsigned char IIC_RecByte(void)
{
    unsigned char i, da;
    for(i=0; i<8; i++)
    {   
    	SCL = 1;
	IIC_Delay(DELAY_TIME);
	da <<= 1;
	if(SDA) da |= 1;
	SCL = 0;
	IIC_Delay(DELAY_TIME);
    }
    return da;    
}


unsigned char PCF8591_Adc(void)
{
  unsigned char temp;
  IIC_Start();
	
  IIC_SendByte(0x90);
  IIC_WaitAck();

  IIC_SendByte(0x43); 				// 允许DAC，ADC通道3  此处若为0x41则为光敏电阻 若为0x43则为电位器
  IIC_WaitAck();

  IIC_Start();
  IIC_SendByte(0x91);//出现0x？1就是从该芯片读的意思
  IIC_WaitAck();

  temp = IIC_RecByte();
  IIC_SendAck(1);
	
  IIC_Stop();
  return temp;
}

void PCF8591_Dac(unsigned char dat)
{
  IIC_Start();
  IIC_SendByte(0x90);
  IIC_WaitAck();

  IIC_SendByte(0x43);				// 允许DAC，ADC通道3
  IIC_WaitAck();

  IIC_SendByte(dat);   			// dat-输出数模转换的数据
  IIC_WaitAck();
  IIC_Stop();
}




/**
* @brief 从AT24C02(add)中读出数据da
*
* @param[in] add - AT24C02存储地址
* @param[out] da - 从AT24C02相应地址中读取到的数据
* @return - da
*/
void EEPROM_Read(unsigned char* pucBuf, unsigned char addr, unsigned char num)
{
  	IIC_Start();
  	IIC_SendByte(0xa0);
  	IIC_WaitAck();

  	IIC_SendByte(addr);
  	IIC_WaitAck();

  	IIC_Start();
  	IIC_SendByte(0xa1);
  	IIC_WaitAck();

  	while(num--)
  	{
    		*pucBuf++ = IIC_RecByte();//
    		if(num) IIC_SendAck(0);
    		else IIC_SendAck(1);
  	}
  	IIC_Stop();
}
/**
* @brief 向AT24C02(add)中写入数据val
*
* @param[in] add - AT24C02存储地址
* @param[in] val - 待写入AT24C02相应地址的数据
* @return - none
*/
void EEPROM_Write(unsigned char* pucBuf, unsigned char addr, unsigned char num)
{
   	IIC_Start();
  	IIC_SendByte(0xa0);
  	IIC_WaitAck();

  	IIC_SendByte(addr);
  	IIC_WaitAck();

  	while(num--)
  	{
    		IIC_SendByte(*pucBuf++); 
    		IIC_WaitAck();
  	   	IIC_Delay(200);
}
  	IIC_Stop();
}


	
	
	
	
	
