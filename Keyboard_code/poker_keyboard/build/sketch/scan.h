#line 1 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\scan.h"
#ifndef SCAN_H
#define SCAN_H

#include "poker_keyboard.h"
#include <Arduino.h>
#include "Layout.h"
//定义键盘输入输出引脚
/*
int key_pin_in[8] = {25,26,32,33,34,35,36,39};
int key_pin_out[11] = {2,4,5,12,13,14,15,18,19,23,27};
# define number_in 8
# define number_out 11
//定义键盘读取数组
int key_press[number_out][number_in] = {};
int old_key_press[number_out][number_in] = {};
//定义fn、pn键位置
# define FN_ROW 8
# define FN_COL 6
*/

bool fn_stat = 0;
bool pn_stat = 0;
void scan_start();
void key_scan();
void key_scan_once();
#endif