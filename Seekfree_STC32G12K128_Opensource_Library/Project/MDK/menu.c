/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2023,Alaye_Dong
 * All rights reserved
 *
 * �����������ݰ�Ȩ����Alaye_Dong���У�δ������������ ��ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣��Alaye_Dong�İ�Ȩ������
 *
 * @file       		menu
 * @author     		Alaye_Dong(QQ2971731849)
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @date       		2023-7-28
 * @note            Ϊ�۲���Ļ�����޸���_SEEKFREE_FONT_h��WHITE�ĺ궨�壬ʵ��Ϊ��ɫ
 *********************************************************************************************************************/

#include "menu.h"

//���尴������
#define KeystrokeONE 1
#define KeystrokeTWO 2
#define KeystrokeTHREE 3
#define KeystrokeFOUR 4

#define RowsMax 7 //�������Ļ�Ͽ��ƶ������������
#define RowsMin 1 //�������Ļ�Ͽ��ƶ�������С����
#define CenterColumn 10*8   //������
#define EEPROM_MODE 1 //eeporm��д������Ϊ1

int Display_Codename = 0;    //��ʾҳ�����
uint8 KeystrokeLabel = 0;   //��ѹ״̬
uint8 CursorRow= 0; //��������к�
uint8 MenuNextFlag = 0; //�����ָ�˵������־λ
float change_unit = 0;  //�����޸ĵĵ�λֵ

//��Ҫ���޸ĵĲ���ʾ��


//���в˵�ҳ��Ĵ�������������У���ֹ�ɼ�ͷ�����к����������벻���ڵĲ˵�
int menu_have_sub[] =  {
                            0,
                            1,
                            2, 21 ,22, 23, 24, 25, 26,
                            3
                       };

//�˵���ͷ��ʶ                       
void Cursor(void)
{		
    uint8 i;
    MenuNextFlag = 0;

    Keystroke_Scan();

    switch(KeystrokeLabel)
    {
        case 1:
                CursorRow--;
                break;                   
        case 2:
                CursorRow++;
                break;                    
        case 3:
                MenuNextFlag = 1;
                break;
        case 4:
                MenuNextFlag = -1;
                break;                    
    }
    //��ͷ��λ
    if (CursorRow < RowsMin)
    {
        CursorRow= RowsMin;
    }
    else if (CursorRow > RowsMax)
    {
        CursorRow= RowsMin;
    } 
    //��ͷ��ӡ
    for (i = 0; i <= 7; i++)
    {
        if(i == CursorRow)
        {
            lcd_showstr(0, CursorRow, ">");
        }
        else
        {
            lcd_showstr(0, i, " ");
        }
    }

}

//�˵����¼���ת
void Menu_Next_Back()
{
    switch(MenuNextFlag)
    {
        case 0: 
                break;
        
        case -1:    //������һ��
                Display_Codename = Display_Codename / 10;
                //CursorRow = 0;
                lcd_clear(WHITE);
                break;
        case 1:     //������һ��
                if(have_sub_menu(Display_Codename*10 + CursorRow))
                {
                    Display_Codename = Display_Codename*10 + CursorRow;
                    //CursorRow = 0;
                    lcd_clear(WHITE);
                }
                break;
    }
    
    MenuNextFlag = 0;   //�л���ҳ�棬��־λ��0
}

// ��鱾���Ƿ�����Ӳ˵�
int have_sub_menu(int menu_id) 
{   
    int i = 0;
    int len = sizeof(menu_have_sub) / sizeof(menu_have_sub [0]);
    for (i = 0; i <= len; i++)
    {
        if (menu_have_sub[i] == menu_id)
        {
            return 1;
        }
    }
    return 0;
}

//���Ͳ����޸�
void Keystroke_int(int* parameter, int change_unit_MIN)
{
    change_unit = change_unit_MIN;  //�޸ĵ�λֵ = ��С�޸ĵ�λֵ
    Keystroke_Scan();
    
    //ͨ���������뿪�����л��޸ĵ�λֵ
    if (sw1_status == 0)
    {
        change_unit = change_unit_MIN * 10; 
        if (sw2_status == 0)
        {
            change_unit = change_unit_MIN * 100; 
        }        
    }
    
    switch(KeystrokeLabel)
    {
        case 0 :
                break;
                    
        case KeystrokeONE :
                *parameter += change_unit;	
                break;
        case KeystrokeTWO :
                *parameter -= change_unit;			
                break;
                    
        case KeystrokeTHREE :
                Display_Codename /= 10; //������һҳ
                lcd_clear(WHITE);
                break;
        case KeystrokeFOUR :
                Display_Codename = 0;	//���ص�0ҳ
                lcd_clear(WHITE);
                break;
    }

}

//�����Ͳ����޸�
void Keystroke_float(float* parameter, float change_unit_MIN)
{
    change_unit = change_unit_MIN;  //�޸ĵ�λֵ = ��С�޸ĵ�λֵ
    Keystroke_Scan();
    
    //ͨ���������뿪�����л��޸ĵĵ�λֵ
    if (sw1_status == 0)
    {
        change_unit = change_unit_MIN * 10; 
        if (sw2_status == 0)
        {
            change_unit = change_unit_MIN * 100; 
        }        
    }
    
    switch(KeystrokeLabel)
    {
        case 0 :
                break;
                    
        case KeystrokeONE :
                *parameter += change_unit;	
                break;
        case KeystrokeTWO :
                *parameter -= change_unit;			
                break;
                    
        case KeystrokeTHREE :
                Display_Codename /= 10; //������һҳ
                lcd_clear(WHITE);
                break;
        case KeystrokeFOUR :
                Display_Codename = 0;	//���ص�0ҳ
                lcd_clear(WHITE);
                break;
    }

}


//������ֵ�޸ģ�-1��1
void Keystroke_Special_Value(int* parameter)
{
    Keystroke_Scan();
    switch(KeystrokeLabel)
    {                
        case KeystrokeONE :
                *parameter = -1;	
                break;
        case KeystrokeTWO :
                *parameter = 1;	
                break;
                
        case KeystrokeTHREE :
                Display_Codename /= 10; //������һҳ
                lcd_clear(WHITE);
                break;
        case KeystrokeFOUR :
                Display_Codename = 0;	//���ص�0ҳ
                lcd_clear(WHITE);
                break;
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      �˵�Ŀ¼
//  @param
//  @return     void
//  @note       ����while����ʾĿ��ҳ��  ��ÿ��ҳ�水�������󶼻�ı䵽��Ӧҳ�棬�˺������ڸ�����Ļ��ʾ        
//             ��ɾҳ��ͬʱ��ǵ�ͬ���޸�menu_have_sub[]�����ֵ
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu(void)
{
    switch(Display_Codename)
    {
        case 0:
                Keystroke_Menu_HOME();
                break;
            
        case 1:
                Keystroke_Menu_ONE(); 
                break;
        case 11:
                Keystroke_Menu_ONE_One();
                break;
        case 12:
                Keystroke_Menu_ONE_Two();
                break;
            
        case 2:
                Keystroke_Menu_TWO();
                break;
        case 21:
                Keystroke_Menu_TWO_One();
                break;
        case 22:
                Keystroke_Menu_TWO_Two();
                break;
        case 23:
                Keystroke_Menu_TWO_Three();
                break;
        case 24:
                Keystroke_Menu_TWO_Four();
                break;
        case 25:
                Keystroke_Menu_TWO_Five();
                break;
        case 26:
                Keystroke_Menu_TWO_Six();
                break;

        case 3:
                Keystroke_Menu_Three();
                break;
            
        default :
            break;
    
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���˵�Ŀ¼
//  @param
//  @return     void
//  @note       ��ҳ��Ϊ���Ϊ0
//-------------------------------------------------------------------------------------------------------------------
void Keystroke_Menu_HOME(void)    //0
{
    time_mod = 0;   //ֹͣ��ʱ
    while(MenuNextFlag == 0)
    {
        lcd_showstr(CenterColumn - 2*8,0,"MENU");
        if(timer_start_flag == 0)
        {
           lcd_showstr(1*8,1,"Quick Start!");
        }
        else
        {
            lcd_showstr(1*8,1,"Continue!");
        }

        lcd_showstr(1*8,2,"Settings");
        lcd_showstr(1*8,3,"Restart");

        Cursor(); 
    }
    
    if(MenuNextFlag == 1 && have_sub_menu(CursorRow))   //������һ���˵�
    {
        Display_Codename = CursorRow;
        CursorRow = 0;
        lcd_clear(WHITE);
    }
    
    else if(MenuNextFlag == -1 && EEPROM_MODE == 1) //�����˵�ʱ���»��˼�������4��������eepromȷ��ˢд
    {
        eeprom_flash();
        
        //ˢд�����ʾ
        lcd_clear(WHITE);
        lcd_showstr(1*8,1,"EEPROM_SAVED");
        lcd_showstr(1*8,4,"@author Alaye_Dong");    //���˾ͱ�ɾ.doge������

        delay_ms(400);
        BEEP = 1;
        delay_ms(100);
        BEEP = 0;
        lcd_clear(WHITE);
    }
    
    MenuNextFlag = 0;   //�л���ҳ�棬��־λ��0
}
/*///////////////////////////////////////
    Start
*////////////////////////////////////////
void Menu_ONE_Display(uint8 control_line)
{
    lcd_showstr(1*8,0,"Started! ^_^");
    lcd_showstr(1*8,1,"Enjoy learning...");
    lcd_showstr(1*8,2,"Target is:");
    lcd_showint32(1*8,3,target_hour,2);
    lcd_showstr(4*8,3,"H");
    lcd_showint32(5*8,3,target_min,2);
    lcd_showstr(8*8,3,"M");
    lcd_showint32(9*8,3,target_sec,2);
    lcd_showstr(12*8,3,"S");
    
    lcd_showstr(1*8,4,"You've learned for:");
    lcd_showint32(1*8,5,user_hour,2);
    lcd_showstr(4*8,5,"H");
    lcd_showint32(5*8,5,user_min,2);
    lcd_showstr(8*8,5,"M");
    lcd_showint32(9*8,5,user_sec,2);
    lcd_showstr(12*8,5,"S");
    lcd_showstr(1*8,7,"PressAnyKeyTo Pause"); 

    lcd_showstr(0,control_line,"&"); //&��־��ʾ

}

void Keystroke_Menu_ONE(void) //1
{	
    time_mod = 1;   //������ʱ
    timer_start_flag = 1;

    while(MenuNextFlag == 0)
    {
        Menu_ONE_Display(-1);
        //Cursor();                        
        Keystroke_Scan();
        if(KeystrokeLabel != 0)
        {
            MenuNextFlag = -1;                  
        }
        
        if(timer_finish_flag == 1)
        {
            time_mod = 0;
            //User_Time_Back_0();
            Display_Codename = 11;
            lcd_clear(WHITE);
            return;
        }
    }
    Menu_Next_Back();
}

void Keystroke_Menu_ONE_One(void)  //11
{	
    time_mod = 1;   //������ʱ    
    while(MenuNextFlag == 0)
    {
        lcd_showstr(1*8,4,"You've rested for:");
        lcd_showint32(1*8,5,user_hour,2);
        lcd_showstr(4*8,5,"H");
        lcd_showint32(5*8,5,user_min,2);
        lcd_showstr(8*8,5,"M");
        lcd_showint32(9*8,5,user_sec,2);
        lcd_showstr(12*8,5,"S");
        
        if(break_finish_flag == 0)
        {
            lcd_showstr(1*8,0,"Good! ^0^");
            lcd_showstr(1*8,1,"You've finished");
            lcd_showstr(1*8,2,"Have a rest for:");
            lcd_showint32(1*8,3,break_hour,2);
            lcd_showstr(4*8,3,"H");
            lcd_showint32(5*8,3,break_min,2);
            lcd_showstr(8*8,3,"M");
            lcd_showint32(9*8,3,break_sec,2);
            lcd_showstr(12*8,3,"S");
            
            lcd_showstr(1*8,7,"PressAnyKeyTo Back"); 
            Keystroke_Scan();
            if(KeystrokeLabel != 0)
            {
                MenuNextFlag = -1;
            }            
        }              
        //Cursor();
        else if(break_finish_flag == 1)
        {
            time_mod = 0;   //ֹͣ��ʱ
            lcd_showstr(1*8,0,"Hey! >_<");
            lcd_showstr(1*8,1,"Time over");
            lcd_showstr(1*8,7,"BackTo Learn!"); 
            lcd_clear(WHITE); 
            Keystroke_Scan();
            if(KeystrokeLabel != 0)
            {
                MenuNextFlag = -1;
            }
        }
    }
    Menu_Next_Back();
    
    User_Time_Back_0();
    break_finish_flag = 0;    
    timer_start_flag = 0;
    timer_finish_flag = 0;
    CursorRow = 0;
    lcd_clear(WHITE); 
}

void Keystroke_Menu_ONE_Two(void)  //12
{		

}

/*////////////////////////////////////
    PD
*////////////////////////////////////
void Menu_TWO_Display(uint8 control_line)
{
    lcd_showstr(CenterColumn - 4*8,0,"Settings");
    lcd_showstr(1*8,1,"target_hour");
    lcd_showstr(1*8,2,"target_min");
    lcd_showstr(1*8,3,"target_sec");
    lcd_showstr(1*8,4,"break_hour");
    lcd_showstr(1*8,5,"break_min");
    lcd_showstr(1*8,6,"break_sec");    
    lcd_showint32(14*8,1,target_hour,2);
    lcd_showint32(14*8,2,target_min,2);
    lcd_showint32(14*8,3,target_sec,2);
    lcd_showint32(14*8,4,break_hour,2);
    lcd_showint32(14*8,5,break_min,2);
    lcd_showint32(14*8,6,break_sec,2);
    
    lcd_showstr(0,control_line,"&"); //&��־��ʾ
}

void Keystroke_Menu_TWO(void) //2
{	
    while(MenuNextFlag == 0)
    {
        Menu_TWO_Display(-1);
        Cursor();
    }
    eeprom_flash();
    Menu_Next_Back();
}

void Keystroke_Menu_TWO_One(void) //21
{
    Menu_TWO_Display(1);
    Keystroke_int(&target_hour, 1);
    Time_Input_Limit(&target_hour, 1);
}
void Keystroke_Menu_TWO_Two(void)  //22
{
    Menu_TWO_Display(2);
    Keystroke_int(&target_min, 1);
    Time_Input_Limit(&target_min, 2);
}
void Keystroke_Menu_TWO_Three(void)  //23
{
    Menu_TWO_Display(3);
    Keystroke_int(&target_sec,1);
    Time_Input_Limit(&target_sec, 3);
}
void Keystroke_Menu_TWO_Four(void)  //24
{
    Menu_TWO_Display(4);
    Keystroke_int(&break_hour,1);
    Time_Input_Limit(&break_hour, 1);
}
void Keystroke_Menu_TWO_Five(void)  //25
{
    Menu_TWO_Display(5);
    Keystroke_int(&break_min,1);
    Time_Input_Limit(&break_min, 2);
}
void Keystroke_Menu_TWO_Six(void)  //26
{
    Menu_TWO_Display(6);
    Keystroke_int(&break_sec,1);
    Time_Input_Limit(&break_sec, 3);
}

void Keystroke_Menu_Three()
{
    lcd_showstr(1*8,3,"RESTARTED");
    User_Time_Back_0();
    timer_start_flag = 0;
    timer_finish_flag = 0;
    Display_Codename = 0;
    CursorRow = 0;
    delay_ms(400);
    BEEP = 1;
    delay_ms(100);
    BEEP = 0;
    lcd_clear(WHITE);
}