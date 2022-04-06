#line 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.h"
#ifndef ESP_KEYBOARD_H
#define ESP_KEYBOARD_H



bool DBG_KEYBOARD = 1;


#define DeviceName "Joker_KEY" //设备名
#define Manufacturer "Liu"        //设备制造商
#define DevicePower 100             //电量

//定义输入输出引脚
int key_pin_in[8] = {25,26,32,33,34,35,36,39};
int key_pin_out[11] = {2,4,5,12,13,14,15,18,19,23,27};
#define number_in 8
#define number_out 11
//定义读取数组
int key_press[number_out][number_in] = {};
int old_key_press[number_out][number_in] = {};

#define FN_ROW 8
#define FN_COL 6

#endif