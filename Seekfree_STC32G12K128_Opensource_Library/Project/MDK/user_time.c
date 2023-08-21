#include "headfile.h"

uint8 time_mod = 0;
int user_hour = 0, user_min = 0, user_sec = 0;
int target_hour = 0, target_min = 0, target_sec = 10;
int break_hour = 0, break_min = 0, break_sec = 10;
int timer_start_flag = 0;
int timer_finish_flag = 0;
int break_finish_flag = 0;

int last_sec = 0;
void User_Time_Sync_RTC(uint8 mod)
{
    if(last_sec != SEC)
    {
        switch(mod)
        {
            case 1:
                    user_sec++;
                  
                    if(user_sec > 59)
                    {
                        user_sec = 0;
                        user_min++;
                    }                   
                    if(user_min > 59)
                    {
                        user_min = 0;
                        user_hour++;
                    }
                    if(user_hour > 23)
                    {
                        user_hour = 0;
                    }
                             
                    break;
                    
            default:
                    break;
        }        
    }

    last_sec = SEC;
}

void User_Time_Back_0()
{
    user_hour = 0; 
    user_min = 0;
    user_sec = 0;
}

void Timer_Finish()
{
    if(timer_finish_flag == 0 && user_hour == target_hour && user_min == target_min && user_sec == target_sec)
    {
        
        timer_finish_flag = 1;
        BEEP = 1;
        delay_ms(100);
        BEEP = 0;
        
        User_Time_Back_0();
    }
    
    else if(timer_finish_flag == 1 && user_hour == break_hour && user_min == break_min && user_sec == break_sec)
    {
        break_finish_flag = 1;
        BEEP = 1;
        delay_ms(100);
        BEEP = 0;
    }
}

void Time_Input_Limit(int* parameter, int time_type)
{
    switch(time_type)
    {
        case 1: //hour
                if(*parameter > 23 || *parameter < 0)
                {
                    *parameter = 0;
                }
                break;
        case 2: //min
                if(*parameter > 59 || *parameter < 0)
                {
                    *parameter = 0;
                }
                break;
        case 3: //sec
                if(*parameter > 59 || *parameter < 0)
                {
                    *parameter = 0;
                }
                break;
    }    
}
