#line 1 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.h"
#ifndef ESP_KEYBOARD_H
#define ESP_KEYBOARD_H
#include "Layout.h"
bool DBG_KEYBOARD = 1;

#ifdef Joker
# define DeviceName "Joker_60" //设备名
#endif

#ifdef MasterYoda
# define DeviceName "MasterYoda"
#endif

# define Manufacturer "Liu"        //设备制造商
# define DevicePower 100             //电量

int DFT_BOOT_MODE; //0是usb，1是蓝牙


//I2C总线信息
# define kbd_SDA 21
# define kbd_SCL 22




#endif