#include  "headfile.h"

#ifndef __RTC_H
#define __RTC_H


void RTC_Init(bit mod);		//RTC实时时钟初始化
void RTC_Set(uint8 Year,uint8 Month,uint8 Day,uint8 Hour,uint8 Min,uint8 Sec,uint8 Ssec);//RTC实时时钟时间设置
void RTCI_Set(bit Ifen,bit Numsen,uint8 mod);		//RTC实时时钟中断设置

#endif