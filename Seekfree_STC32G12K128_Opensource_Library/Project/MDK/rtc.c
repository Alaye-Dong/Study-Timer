#include "headfile.h"


/**
  *设置时：INIYEAR(INI+xxxx)(参考下方)
  *读取时：YEAR年 MONTH月 DAY日 HOUR时 MIN分 SEC秒 SSEC(1/128秒)
 */
//RTC实时时钟初始化
//参数mod:	作用： 0.內部32K   1.外部32K
void RTC_Init(bit mod)
{
	if(mod)
	{
		//选择外部32K
		X32KCR = 0xc0;				//启动外部32K晶振
		while (!(X32KCR&0x01));		//等待时钟稳定
		RTCCFG &=~0x02;				//选择外部32K作为RTC时钟源
	}
	else
	{
		//选择內部32K
		IRC32KCR=0x80;				//启动内部32K晶振
		while(!(IRC32KCR&0x01));	//等待时钟稳定
		RTCCFG|=0x02;				//选择内部32K作为RTC时钟源
	}
	RTCIF=0x00;		//清中断标志
	RTCCR=0x01;		//RTC使能
}
 
//RTC实时时钟时间设置
/*参数
 Year(年):	范围：0~未知（20+值）
 Month(月):	范围：1~12
 Day(日):	范围：1~31
 Hour(小时):	范围：00~23
 Min(分钟):	范围：00~59
 Sec(秒)：	范围：00~59
 Ssec(1/128秒): 范围：00~127
*/
 
 
void RTC_Set(uint8 Year,uint8 Month,uint8 Day,uint8 Hour,uint8 Min,uint8 Sec,uint8 Ssec)
{
	INIYEAR = Year;
	INIMONTH = Month;
	INIDAY = Day;
	INIHOUR = Hour;
	INIMIN = Min;
	INISEC = Sec;
	INISSEC=Ssec;
	RTCCFG|=0x01;		//触发RCT寄存器初始化
	while(RTCCFG&0x01);	//等待
}
 
//RTC实时时钟中断设置
/*参数
Ifen:总中断			范围：0（关闭）/1（开启）
Numsen:目标中断		范围：0（关闭）/1（开启）
mod:目标				范围：0（1/32秒）1（1/8秒）2（1/2秒）3（1秒）4（1分钟）5（1小时）6（1日（24小时））
*/
void RTCI_Set(bit Ifen,bit Numsen,uint8 mod)
{
	if(Ifen){RTCIEN|=0x80;}else{RTCIEN&=(~0x80);}
	if(Numsen){RTCIEN|=(0x01<<mod);}else{RTCIEN&=~(0x01<<mod);}
}
 
//RTC实时时钟中断事件
void RTC_Isr()	interrupt 13
{
	//RTC实时时钟中断
	if(RTCIF&0x80)				//闹钟中断
	{
		
		RTCIF&=~0x80;
	}
	else if(RTCIF&(0x80>>1))	//1日中断
	{
		
		RTCIF&=(0x80>>1);
	}
	else if(RTCIF&(0x80>>2))	//1小时中断
	{
		
		RTCIF&=(0x80>>2);
	}
	else if(RTCIF&(0x80>>3))	//1分钟中断
	{
		
		RTCIF&=(0x80>>3);
	}
	else if(RTCIF&(0x80>>4))	//1秒中断
	{
        User_Time_Sync_RTC(1);
		RTCIF&=(0x80>>4);
	}
	else if(RTCIF&(0x80>>5))	//1/2秒中断
	{
		
		RTCIF&=(0x80>>5);
	}
	else if(RTCIF&(0x80>>6))	//1/8秒中断
	{
		
		RTCIF&=(0x80>>6);
	}
	else if(RTCIF&(0x80>>7))	//1/32秒中断
	{
		
		RTCIF&=(0x80>>7);
	}
	
}