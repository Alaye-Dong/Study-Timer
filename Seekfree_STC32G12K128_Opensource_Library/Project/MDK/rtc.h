#include  "headfile.h"

#ifndef __RTC_H
#define __RTC_H


void RTC_Init(bit mod);		//RTCʵʱʱ�ӳ�ʼ��
void RTC_Set(uint8 Year,uint8 Month,uint8 Day,uint8 Hour,uint8 Min,uint8 Sec,uint8 Ssec);//RTCʵʱʱ��ʱ������
void RTCI_Set(bit Ifen,bit Numsen,uint8 mod);		//RTCʵʱʱ���ж�����

#endif