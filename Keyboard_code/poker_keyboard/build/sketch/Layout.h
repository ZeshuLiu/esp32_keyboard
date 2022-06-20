#line 1 "d:\\Data\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\Layout.h"
#ifndef LAYOUT_H
#define LAYOUT_H

#include <BleKeyboard.h>
#include "poker_keyboard.h"
#include "USB_CODE.h"

//Select Model
///#define Joker
#define MasterYoda


//Joker Layout Start
#ifdef Joker

//定义键盘输入输出引脚
int key_pin_in[8] = {25,26,32,33,34,35,36,39};
int key_pin_out[8] = {2,4,13,14,18,19,23,27};
# define number_in 8
# define number_out 8
//定义键盘读取数组
int key_press[number_out][number_in] = {};
int old_key_press[number_out][number_in] = {};
int filter_key_press[number_out][number_in] = {};
#define KEY_FN 0
#define KEY_PN 0
//定义fn、pn键位置
# define FN_ROW 3
# define FN_COL 0
# define PN_ROW 7
# define PN_COL 4

//定义pn功能位置
# define LED_ROW 2
# define LED_COL 4
# define MODE_ROW 1
# define MODE_COL 5
# define cnt_rst_ROW 7
# define cnt_rst_COL 0
# define DOG_ROW 1
# define DOG_COL 3


//BT
uint8_t LayOut_ALL[number_out][number_in] = {
    {KEY_S,KEY_LEFT_SHIFT,KEY_5,KEY_R,KEY_9,KEY_8,KEY_BACKSPACE,KEY_RIGHT_ARROW}, //0
    {KEY_Q,KEY_LEFT_ALT,KEY_N,KEY_D,KEY_SEMICOLON,KEY_M,KEY_SUB,KEY_LBRACKET}, //1
    {KEY_X,KEY_LEFT_CTRL,KEY_T,KEY_F,KEY_L,KEY_I,0,KEY_DOWN_ARROW}, //2
    {KEY_FN,KEY_ESC,KEY_G,KEY_V,KEY_FULLSTOP,KEY_K,0,KEY_FSLASH}, //3
    {KEY_1,KEY_CAPS_LOCK,KEY_H,KEY_E,KEY_0,KEY_J,KEY_EQUAL,KEY_SQUOTES}, //4
    {KEY_W,KEY_Z,KEY_6,KEY_4,KEY_O,KEY_7,KEY_BSLASH,KEY_UP_ARROW},//5
    {KEY_2,KEY_A,KEY_Y,KEY_3,KEY_P,KEY_U,KEY_RBRACKET,KEY_RETURN},//6
    {KEY_C,KEY_TAB,KEY_B,KEY_SPACE,KEY_PN,KEY_COMMA,0,KEY_LEFT_ARROW},//7
};
uint8_t LayOut_ALL_FN[number_out][number_in] = {
    {KEY_S,KEY_LEFT_SHIFT,KEY_F5,KEY_R,KEY_F9,KEY_F8,KEY_DELETE,KEY_RIGHT_ARROW}, //0
    {KEY_Q,KEY_LEFT_GUI,KEY_N,KEY_D,KEY_SEMICOLON,KEY_M,KEY_F11,KEY_LBRACKET}, //1
    {KEY_X,KEY_LEFT_CTRL,KEY_T,KEY_F,KEY_L,KEY_I,0,KEY_DOWN_ARROW},//2
    {KEY_FN,KEY_SEPARATOR,KEY_G,KEY_V,KEY_FULLSTOP,KEY_K,0,KEY_FSLASH}, //3
    {KEY_F1,KEY_CAPS_LOCK,KEY_H,KEY_E,KEY_F10,KEY_J,KEY_F12,KEY_SQUOTES}, //4
    {KEY_W,KEY_Z,KEY_F6,KEY_F4,KEY_O,KEY_F7,KEY_BSLASH,KEY_UP_ARROW},//5
    {KEY_F2,KEY_A,KEY_Y,KEY_F3,KEY_P,KEY_U,KEY_RBRACKET,KEY_RETURN},//6
    {KEY_C,KEY_TAB,KEY_B,KEY_SPACE,KEY_PN,KEY_COMMA,0,KEY_LEFT_ARROW},//7
};
//BT END


//USB
uint8_t USB_LayOut_ALL[number_out][number_in] = {
    {KEY_USB_S,KEY_USB_LEFT_SHIFT,KEY_USB_5,KEY_USB_R,KEY_USB_9,KEY_USB_8,KEY_USB_BACKSPACE,KEY_USB_RIGHT_ARROW}, //0
    {KEY_USB_Q,KEY_USB_LEFT_ALT,KEY_USB_N,KEY_USB_D,KEY_USB_SEMICOLON,KEY_USB_M,KEY_USB_SUB,KEY_USB_LBRACKET}, //1
    {KEY_USB_X,KEY_USB_LEFT_CTRL,KEY_USB_T,KEY_USB_F,KEY_USB_L,KEY_USB_I,0,KEY_USB_DOWN_ARROW}, //2
    {KEY_FN,KEY_USB_ESC,KEY_USB_G,KEY_USB_V,KEY_USB_FSTOP,KEY_USB_K,0,KEY_USB_FSLASH}, //3
    {KEY_USB_1,KEY_USB_CAPS_LOCK,KEY_USB_H,KEY_USB_E,KEY_USB_0,KEY_USB_J,KEY_USB_EQUAL,KEY_USB_SQUOTES}, //4
    {KEY_USB_W,KEY_USB_Z,KEY_USB_6,KEY_USB_4,KEY_USB_O,KEY_USB_7,KEY_USB_BSLASH,KEY_USB_UP_ARROW},//5
    {KEY_USB_2,KEY_USB_A,KEY_USB_Y,KEY_USB_3,KEY_USB_P,KEY_USB_U,KEY_USB_RBRACKET,KEY_USB_RETURN},//6
    {KEY_USB_C,KEY_USB_TAB,KEY_USB_B,KEY_USB_SPACE,KEY_PN,KEY_USB_COMMA,0,KEY_USB_LEFT_ARROW},//7
};
uint8_t USB_LayOut_words[number_out][number_in] = {
    {KEY_USB_S,0,KEY_USB_5,KEY_USB_R,KEY_USB_9,KEY_USB_8,KEY_USB_BACKSPACE,KEY_USB_RIGHT_ARROW}, //0
    {KEY_USB_Q,0,KEY_USB_N,KEY_USB_D,KEY_USB_SEMICOLON,KEY_USB_M,KEY_USB_SUB,KEY_USB_LBRACKET}, //1
    {KEY_USB_X,0,KEY_USB_T,KEY_USB_F,KEY_USB_L,KEY_USB_I,0,KEY_USB_DOWN_ARROW}, //2
    {KEY_FN,KEY_USB_ESC,KEY_USB_G,KEY_USB_V,KEY_USB_FSTOP,KEY_USB_K,0,KEY_USB_FSLASH}, //3
    {KEY_USB_1,KEY_USB_CAPS_LOCK,KEY_USB_H,KEY_USB_E,KEY_USB_0,KEY_USB_J,KEY_USB_EQUAL,KEY_USB_SQUOTES}, //4
    {KEY_USB_W,KEY_USB_Z,KEY_USB_6,KEY_USB_4,KEY_USB_O,KEY_USB_7,KEY_USB_BSLASH,KEY_USB_UP_ARROW},//5
    {KEY_USB_2,KEY_USB_A,KEY_USB_Y,KEY_USB_3,KEY_USB_P,KEY_USB_U,KEY_USB_RBRACKET,KEY_USB_RETURN},//6
    {KEY_USB_C,KEY_USB_TAB,KEY_USB_B,KEY_USB_SPACE,KEY_PN,KEY_USB_COMMA,0,KEY_USB_LEFT_ARROW},//7
};

uint8_t USB_LayOut_ALL_FN[number_out][number_in] = {
    {KEY_USB_DOWN_ARROW,KEY_USB_LEFT_SHIFT,KEY_USB_F5,KEY_USB_R,KEY_USB_F9,KEY_USB_F8,KEY_USB_DELETE,KEY_USB_RIGHT_ARROW}, //0
    {KEY_USB_Q,KEY_USB_LEFT_GUI,KEY_USB_N,KEY_USB_RIGHT_ARROW,KEY_USB_SEMICOLON,KEY_USB_M,KEY_USB_F11,KEY_USB_LBRACKET}, //1
    {KEY_USB_X,KEY_USB_LEFT_CTRL,KEY_USB_T,KEY_USB_F,KEY_USB_L,KEY_USB_I,0,KEY_USB_DOWN_ARROW},//2
    {KEY_FN,KEY_USB_SEPARATOR,KEY_USB_G,KEY_USB_V,KEY_USB_FSTOP,KEY_USB_K,0,KEY_USB_FSLASH}, //3
    {KEY_USB_F1,KEY_USB_CAPS_LOCK,KEY_USB_H,KEY_USB_E,KEY_USB_F10,KEY_USB_J,KEY_USB_F12,KEY_USB_SQUOTES}, //4
    {KEY_USB_UP_ARROW,KEY_USB_Z,KEY_USB_F6,KEY_USB_F4,KEY_USB_O,KEY_USB_F7,KEY_USB_BSLASH,KEY_USB_UP_ARROW},//5
    {KEY_USB_F2,KEY_USB_LEFT_ARROW,KEY_USB_Y,KEY_USB_F3,KEY_USB_P,KEY_USB_U,KEY_USB_RBRACKET,KEY_USB_RETURN},//6
    {KEY_USB_C,KEY_USB_TAB,KEY_USB_B,KEY_USB_SPACE,KEY_PN,KEY_USB_COMMA,0,KEY_USB_LEFT_ARROW},//7
};
uint8_t USB_LayOut_words_FN[number_out][number_in] = {
    {0,0,KEY_USB_F5,KEY_USB_R,KEY_USB_F9,KEY_USB_F8,KEY_USB_DELETE,KEY_USB_RIGHT_ARROW}, //0
    {KEY_USB_Q,0,KEY_USB_N,0,KEY_USB_SEMICOLON,KEY_USB_M,KEY_USB_F11,KEY_USB_LBRACKET}, //1
    {KEY_USB_X,0,KEY_USB_T,KEY_USB_F,KEY_USB_L,KEY_USB_I,0,KEY_USB_DOWN_ARROW},//2
    {KEY_FN, KEY_USB_SEPARATOR,KEY_USB_G,KEY_USB_V,KEY_USB_FSTOP,KEY_USB_K,0,KEY_USB_FSLASH}, //3
    {KEY_USB_F1,KEY_USB_CAPS_LOCK,KEY_USB_H,KEY_USB_E,KEY_USB_F10,KEY_USB_J,KEY_USB_F12,KEY_USB_SQUOTES}, //4
    {0,KEY_USB_Z,KEY_USB_F6,KEY_USB_F4,KEY_USB_O,KEY_USB_F7,KEY_USB_BSLASH,KEY_USB_UP_ARROW},//5
    {KEY_USB_F2,0,KEY_USB_Y,KEY_USB_F3,KEY_USB_P,KEY_USB_U,KEY_USB_RBRACKET,KEY_USB_RETURN},//6
    {KEY_USB_C,KEY_USB_TAB,KEY_USB_B,KEY_USB_SPACE,KEY_PN,KEY_USB_COMMA,0,KEY_USB_LEFT_ARROW},//7
};
#endif
// Joker Layout End



//MasterYoda Layout Start
#ifdef MasterYoda

//定义键盘输入输出引脚
int key_pin_in[5] = {36,39,34,35,32};
int key_pin_out[4] = {23,19,18,4};
# define number_in 5
# define number_out 4
//定义键盘读取数组
int key_press[number_out][number_in] = {};
int old_key_press[number_out][number_in] = {};
int filter_key_press[number_out][number_in] = {};
#define KEY_FN 0
#define KEY_PN 0


//定义fn、pn键位置
# define FN_ROW 3
# define FN_COL 2


# define PN_ROW 7
# define PN_COL 7

/*
//定义pn功能位置
# define LED_ROW 2
# define LED_COL 4
# define MODE_ROW 1
# define MODE_COL 5
# define cnt_rst_ROW 7
# define cnt_rst_COL 0
# define DOG_ROW 1
# define DOG_COL 3
*/


//BT
uint8_t LayOut_ALL[number_out][number_in] = {
    {0,KEY_1,KEY_2,KEY_3,KEY_4}, //0
    {KEY_TAB,KEY_Q,KEY_W,KEY_E,KEY_R}, //1
    {KEY_LEFT_CTRL,KEY_A,KEY_S,KEY_D,KEY_F}, //2
    {KEY_ESC,KEY_LEFT_SHIFT,KEY_FN,0,KEY_SPACE}, //3
};
uint8_t LayOut_ALL_FN[number_out][number_in] = {
    {KEY_S,KEY_LEFT_SHIFT,KEY_5,KEY_R,KEY_9}, //0
    {KEY_Q,KEY_LEFT_ALT,KEY_N,KEY_D,KEY_SEMICOLON}, //1
    {KEY_X,KEY_LEFT_CTRL,KEY_T,KEY_F,KEY_L}, //2
    {KEY_FN,KEY_ESC,KEY_G,KEY_V,KEY_FULLSTOP}, //3
};
//BT END


//USB
uint8_t USB_LayOut_ALL[number_out][number_in] = {
    {0,KEY_USB_1,KEY_USB_2,KEY_USB_3,KEY_USB_4}, //0
    {KEY_USB_TAB,KEY_USB_Q,KEY_USB_W,KEY_USB_E,KEY_USB_R}, //1
    {KEY_USB_LEFT_CTRL,KEY_USB_A,KEY_USB_S,KEY_USB_D,KEY_USB_F}, //2
    {KEY_USB_ESC,KEY_USB_LEFT_SHIFT,KEY_FN,0,KEY_USB_SPACE}, //3
};
uint8_t USB_LayOut_words[number_out][number_in] = {
    {0,KEY_USB_1,KEY_USB_2,KEY_USB_3,KEY_USB_4}, //0
    {KEY_USB_TAB,KEY_USB_Q,KEY_USB_W,KEY_USB_E,KEY_USB_R}, //1
    {0,KEY_USB_A,KEY_USB_S,KEY_USB_D,KEY_USB_F}, //2
    {KEY_USB_ESC,0,KEY_FN,0,KEY_USB_SPACE}, //3
};

uint8_t USB_LayOut_ALL_FN[number_out][number_in] = {
    {0,KEY_USB_1,KEY_USB_2,KEY_USB_3,KEY_USB_4}, //0
    {KEY_USB_TAB,KEY_USB_Q,KEY_USB_W,KEY_USB_E,KEY_USB_R}, //1
    {KEY_USB_LEFT_CTRL,KEY_USB_A,KEY_USB_S,KEY_USB_D,KEY_USB_F}, //2
    {KEY_USB_ESC,KEY_USB_LEFT_SHIFT,KEY_FN,0,KEY_USB_SPACE}, //3
};
uint8_t USB_LayOut_words_FN[number_out][number_in] = {
    {0,KEY_USB_1,KEY_USB_2,KEY_USB_3,KEY_USB_4}, //0
    {KEY_USB_TAB,KEY_USB_Q,KEY_USB_W,KEY_USB_E,KEY_USB_R}, //1
    {KEY_USB_LEFT_CTRL,KEY_USB_A,KEY_USB_S,KEY_USB_D,KEY_USB_F}, //2
    {KEY_USB_ESC,KEY_USB_LEFT_SHIFT,KEY_FN,0,KEY_USB_SPACE}, //3
};
#endif
// MasterYoda Layout End

#endif