/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"


/*
 * ϵͳƵ�ʣ��ɲ鿴board.h�е� FOSC �궨���޸ġ�
 * board.h�ļ���FOSC��ֵ����Ϊ0,������Զ�����ϵͳƵ��Ϊ33.1776MHZ
 * ��board_init��,�Ѿ���P54��������Ϊ��λ
 * �����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */


void main()
{
	board_init();			// ��ʼ���Ĵ���,��ɾ���˾���롣
	
	// �˴���д�û�����(���磺�����ʼ�������)
    
	gpio_mode(P6_7, GPO_PP); //������
    //pwm_init(PWM1, 17000, 0)
    BEEP = 0;
    lcd_init();
    
    BEEP = 1;
    delay_ms(10);
    BEEP = 0;
    
    eeprom_init();
    
    RTC_Init(0);	//RTCʵʱʱ�ӳ�ʼ��
	RTC_Set(0,0,0,0,0,0,0);    //����ʱ��
    
    //RTCI_Set(1,1,3);
    pit_timer_ms(TIM_4, 5);
    
    while(1)
	{
		 // �˴���д��Ҫѭ��ִ�еĴ���
        Keystroke_Scan();
        Keystroke_Menu();        	
        //��ȡʱ��YEAR�� MONTH�� DAY�� HOURʱ MIN�� SEC�� SSEC(1/128��)

    }
}

