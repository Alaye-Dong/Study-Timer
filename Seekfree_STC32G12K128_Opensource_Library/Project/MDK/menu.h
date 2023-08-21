#ifndef _MENU_H_
#define _MENU_H_

#include "headfile.h"

extern int Display_Codename;       //��ʾҳ�����
extern uint8 CursorRow; //��������к�



void Cursor(void);
void Menu_Next_Back(void);
int have_sub_menu(int menu_id); // �鿴�Ƿ�����Ӳ˵�

void Keystroke_Special_Value(int* parameter);
void Keystroke_int(int* parameter, int change_unit_MIN);
void Keystroke_float(float* parameter, float change_unit_MIN);

void Keystroke_Menu(void);
void Keystroke_Menu_HOME(void);

void Menu_ONE_Display(uint8 control_line);
void Keystroke_Menu_ONE(void);
void Keystroke_Menu_ONE_One(void);
void Keystroke_Menu_ONE_Two(void); 

void Menu_TWO_Display(uint8 control_line);
void Keystroke_Menu_TWO(void);
void Keystroke_Menu_TWO_One(void);
void Keystroke_Menu_TWO_Two(void);
void Keystroke_Menu_TWO_Three(void);
void Keystroke_Menu_TWO_Four(void);
void Keystroke_Menu_TWO_Five(void) ; 
void Keystroke_Menu_TWO_Six(void); 

void Keystroke_Menu_Three();

#endif