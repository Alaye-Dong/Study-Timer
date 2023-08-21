#include "headfile.h"

uint8 date_buff[100]; //eeprom数据数组
uint8 eeprom_init_time = 0;
void eeprom_init()
{
    iap_init();									//初始化EEPROM;

    iap_read_bytes(0x00, date_buff, 100);		//从EEPROM中读取数据

/****不用eeprom直接赋值****/

	
/****用eeprom赋值****/
    
    //刷写程序后初次启动,填充eeprom
    eeprom_init_time = read_int(0);	
    if(eeprom_init_time != 1)
    {
        save_int(1,0);
        
        save_int(target_hour,1);
        save_int(target_min,2);
        save_int(target_sec,3);
        save_int(break_hour,4);
        save_int(break_min,5);
        save_int(break_sec,6);              
    }
    
    //eeprom读取
    target_hour = read_int(1);
    target_min = read_int(2);
    target_sec = read_int(3);
    break_hour = read_int(4);
    break_min = read_int(5);
    break_sec = read_int(6);    
}

void eeprom_flash()
{
    //需要保存的参数
    save_int(target_hour,1);
    save_int(target_min,2);
    save_int(target_sec,3);
}

void save_int(int32 input, uint8 value_bit)
{
    uint8 i;
    uint8 begin = value_bit * 4;
    uint8* p = (uint8*)&input;
    for(i = 0; i < 4; i++)
    {
        date_buff[begin++] = *(p + i);
    }
    extern_iap_write_bytes(0x00, date_buff, 100);
}

int32 read_int(uint8 value_bit)
{
    uint8 i;
    uint8 begin = value_bit * 4;
    int32 output;
    uint8* p = (uint8*)&output;;
    for(i = 0; i < 4; i++)
    {
        *(p + i) = date_buff[begin++];
    }
    return output;
}

void save_float(float input, uint8 value_bit)
{
    uint8 i;
    uint8 begin = value_bit * 4;
    uint8* p = (uint8*)&input;
    for(i = 0; i < 4; i++)
    {
        date_buff[begin++] = *(p + i);
    }
    extern_iap_write_bytes(0x00, date_buff, 100);
}
float read_float(uint8 value_bit)
{
    uint8 i;
    uint8 begin = value_bit * 4;
    float output;
    uint8* p = (uint8*)&output;;
    for(i = 0; i < 4; i++)
    {
        *(p + i) = date_buff[begin++];
    }
    return output;
}