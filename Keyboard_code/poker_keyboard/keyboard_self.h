#ifndef KEYBOARD_SELF_H
#define KEYBOARD_SELF_H

# include "poker_keyboard.h"
# include <Arduino.h>
# include "pcf8575.h"
# include "Layout.h"


//设备状态
bool LED_STAT = 0;
bool CAP_LED_STAT = 0;

//倒计时
BaseType_t xReturned_cnt;
TaskHandle_t CNT_TASK_Handle = NULL;
#define CNT_TASK_CORE 1
#define CNT_TASK_STACK 2048
#define CNT_TASK_PRI 10
int CNT_TIME = 1800000 ;
//int CNT_TIME = 60000;
bool rst_cnt_time = 0;
# define cnt_line 5
bool cnt_start();

//初始化
void keyboard_setup(void);

//LED设置
//Joker60
# ifndef Ver2
# define LED_PIN 12
# define CAP_LED_PIN P01
# endif
//Joker 60v2
# ifdef Ver2
# define LED_PIN 15
# define CAP_LED_PIN P01
#endif

void open_i2c_keyboard_led(void);
void close_i2c_keyboard_led(void);
void open_i2c_caps_led(void);
void close_i2c_caps_led(void);
void open_inter_led();
void close_inter_led();


//测试
void keyboard_device_test(void);

//IO扩展板地址
//# define io_exp_in_cnt 1
//# define io_exp_out_cnt 3
//int io_expand_input[io_exp_in_cnt] = {P15};
//int io_expand_output[io_exp_out_cnt] = {P0,P1,P2} ; 

byte write_low = B00000000;

#endif