#include "headfile.h"


/**
  *����ʱ��INIYEAR(INI+xxxx)(�ο��·�)
  *��ȡʱ��YEAR�� MONTH�� DAY�� HOURʱ MIN�� SEC�� SSEC(1/128��)
 */
//RTCʵʱʱ�ӳ�ʼ��
//����mod:	���ã� 0.�Ȳ�32K   1.�ⲿ32K
void RTC_Init(bit mod)
{
	if(mod)
	{
		//ѡ���ⲿ32K
		X32KCR = 0xc0;				//�����ⲿ32K����
		while (!(X32KCR&0x01));		//�ȴ�ʱ���ȶ�
		RTCCFG &=~0x02;				//ѡ���ⲿ32K��ΪRTCʱ��Դ
	}
	else
	{
		//ѡ��Ȳ�32K
		IRC32KCR=0x80;				//�����ڲ�32K����
		while(!(IRC32KCR&0x01));	//�ȴ�ʱ���ȶ�
		RTCCFG|=0x02;				//ѡ���ڲ�32K��ΪRTCʱ��Դ
	}
	RTCIF=0x00;		//���жϱ�־
	RTCCR=0x01;		//RTCʹ��
}
 
//RTCʵʱʱ��ʱ������
/*����
 Year(��):	��Χ��0~δ֪��20+ֵ��
 Month(��):	��Χ��1~12
 Day(��):	��Χ��1~31
 Hour(Сʱ):	��Χ��00~23
 Min(����):	��Χ��00~59
 Sec(��)��	��Χ��00~59
 Ssec(1/128��): ��Χ��00~127
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
	RTCCFG|=0x01;		//����RCT�Ĵ�����ʼ��
	while(RTCCFG&0x01);	//�ȴ�
}
 
//RTCʵʱʱ���ж�����
/*����
Ifen:���ж�			��Χ��0���رգ�/1��������
Numsen:Ŀ���ж�		��Χ��0���رգ�/1��������
mod:Ŀ��				��Χ��0��1/32�룩1��1/8�룩2��1/2�룩3��1�룩4��1���ӣ�5��1Сʱ��6��1�գ�24Сʱ����
*/
void RTCI_Set(bit Ifen,bit Numsen,uint8 mod)
{
	if(Ifen){RTCIEN|=0x80;}else{RTCIEN&=(~0x80);}
	if(Numsen){RTCIEN|=(0x01<<mod);}else{RTCIEN&=~(0x01<<mod);}
}
 
//RTCʵʱʱ���ж��¼�
void RTC_Isr()	interrupt 13
{
	//RTCʵʱʱ���ж�
	if(RTCIF&0x80)				//�����ж�
	{
		
		RTCIF&=~0x80;
	}
	else if(RTCIF&(0x80>>1))	//1���ж�
	{
		
		RTCIF&=(0x80>>1);
	}
	else if(RTCIF&(0x80>>2))	//1Сʱ�ж�
	{
		
		RTCIF&=(0x80>>2);
	}
	else if(RTCIF&(0x80>>3))	//1�����ж�
	{
		
		RTCIF&=(0x80>>3);
	}
	else if(RTCIF&(0x80>>4))	//1���ж�
	{
        User_Time_Sync_RTC(1);
		RTCIF&=(0x80>>4);
	}
	else if(RTCIF&(0x80>>5))	//1/2���ж�
	{
		
		RTCIF&=(0x80>>5);
	}
	else if(RTCIF&(0x80>>6))	//1/8���ж�
	{
		
		RTCIF&=(0x80>>6);
	}
	else if(RTCIF&(0x80>>7))	//1/32���ж�
	{
		
		RTCIF&=(0x80>>7);
	}
	
}