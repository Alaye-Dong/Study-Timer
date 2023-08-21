#include "key.h"

//���尴������
#define KEY1_PIN    P71
#define KEY2_PIN    P70	
#define KEY3_PIN    P72
#define KEY4_PIN    P73
//���岦�뿪������
#define SW1_PIN     P76
#define SW2_PIN     P75

//���尴������
#define KeystrokeONE 1
#define KeystrokeTWO 2
#define KeystrokeTHREE 3
#define KeystrokeFOUR 4

//���뿪��״̬���� ONΪ0
uint8 sw1_status;
uint8 sw2_status;

//����״̬����
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;

//��һ�ο���״̬����
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;

//���ر�־λ
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;

void Keystroke_Scan(void)
{

    //��ȡ���뿪��״̬
    sw1_status = SW1_PIN;
    sw2_status = SW2_PIN;

    //ʹ�ô˷����ŵ����ڣ�����Ҫʹ��while(1) �ȴ������⴦������Դ�˷�
    //���水��״̬
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;
    key4_last_status = key4_status;
    //��ȡ��ǰ����״̬
    key1_status = KEY1_PIN;
    key2_status = KEY2_PIN;
    key3_status = KEY3_PIN;
    key4_status = KEY4_PIN;


    //��⵽��������֮��  ���ſ���λ��־λ
    if(key1_status && !key1_last_status)    key1_flag = 1;
    if(key2_status && !key2_last_status)    key2_flag = 1;
    if(key3_status && !key3_last_status)    key3_flag = 1;
    if(key4_status && !key4_last_status)    key4_flag = 1;

    //��־λ��λ֮�󣬿���ʹ�ñ�־λִ���Լ���Ҫ�����¼�
    KeystrokeLabel = 0;        

    if(key1_flag)   
    {
        key1_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
        KeystrokeLabel = 1;
        BEEP = 1;
        delay_ms(5);
        BEEP = 0;
    }

    if(key2_flag)   
    {
        key2_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
        KeystrokeLabel = 2;
        BEEP = 1;
        delay_ms(5);
        BEEP = 0;
    }

    if(key3_flag)   
    {
        key3_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
        KeystrokeLabel = 3;
        BEEP = 1;
        delay_ms(5);
        BEEP = 0;        
    }

    if(key4_flag)   
    {
        key4_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
        KeystrokeLabel = 4;
        BEEP = 1;
        delay_ms(5);
        BEEP = 0;        
    }

}