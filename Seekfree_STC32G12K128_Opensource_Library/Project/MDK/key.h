#ifndef _KEY_H_
#define _KEY_H_

#include "headfile.h"

//���뿪��״̬����
extern uint8 sw1_status;
extern uint8 sw2_status;

//����״̬����
extern uint8 key1_status ;
extern uint8 key2_status ;
extern uint8 key3_status ;
extern uint8 key4_status ;

//��һ�ο���״̬����
extern uint8 key1_last_status;
extern uint8 key2_last_status;
extern uint8 key3_last_status;
extern uint8 key4_last_status;

//���ر�־λ
extern uint8 key1_flag;
extern uint8 key2_flag;
extern uint8 key3_flag;
extern uint8 key4_flag;

extern uint8 KeystrokeLabel;


void Keystroke_Scan(void);

#endif