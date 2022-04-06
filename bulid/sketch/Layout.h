#line 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\Layout.h"
#ifndef LAYOUT_H
#define LAYOUT_H

#include <BleKeyboard.h>
#include "poker_keyboard.h"

#define KEY_FN 0

uint8_t LayOut[number_out][number_in] = {
    {0,0,0,0,0,0,0,0}, //0
    {0,0,0,0,0,0,0,0}, //1
    {0,0,0,0,0,0,0,0}, //2
    {0,0,0,0,KEY_R,KEY_4,KEY_V,KEY_F}, //3
    {0,0,0,0,KEY_Q,KEY_1,KEY_Z,KEY_A}, //4
    {0,0,0,0,KEY_E,KEY_3,KEY_C,KEY_D},//5
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,KEY_FN,KEY_RIGHT_SHIFT},//8
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,KEY_W,KEY_2,KEY_X,KEY_S},//10
};

#endif