#ifndef KEYBOARD_SELF_H
#define KEYBOARD_SELF_H

# include "poker_keyboard.h"
# include <Arduino.h>
# include "pcf8575.h"

//设备状态
bool LED_STAT = 0;
bool CAP_LED_STAT = 0;
//初始化
void keyboard_setup(void);

//LED设置
#define LED_PIN P00
#define CAP_LED_PIN P01
void open_keyboard_led(void);
void close_keyboard_led(void);
void open_caps_led(void);
void close_caps_led(void);

//测试
void keyboard_device_test(void);

//IO扩展板地址

//# define io_exp_in_cnt 1
//# define io_exp_out_cnt 3
//int io_expand_input[io_exp_in_cnt] = {P15};
//int io_expand_output[io_exp_out_cnt] = {P0,P1,P2} ; 

byte write_low = B00000000;

#endif