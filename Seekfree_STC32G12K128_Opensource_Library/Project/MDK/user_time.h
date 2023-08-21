#include  "headfile.h"

#ifndef __USER_TIME_H
#define __USER_TIME_H

extern uint8 time_mod;

extern int user_hour, user_min, user_sec;
extern int target_hour, target_min, target_sec;
extern int break_hour, break_min, break_sec;

extern int timer_finish_flag;
extern int timer_start_flag;
extern int break_finish_flag;



void User_Time_Sync_RTC(uint8 mod);
void User_Time_Back_0();
void Timer_Finish();
void Time_Input_Limit(int* parameter, int time_type);


#endif