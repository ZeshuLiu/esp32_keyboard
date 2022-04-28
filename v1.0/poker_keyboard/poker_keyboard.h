#ifndef ESP_KEYBOARD_H
#define ESP_KEYBOARD_H

bool DBG_KEYBOARD = 1;

# define DeviceName "Joker_" //设备名
# define Manufacturer "Liu"        //设备制造商
# define DevicePower 100             //电量

int DFT_BOOT_MODE = 0; //0是usb，1是蓝牙

# define number_in 8
# define number_out 8


//定义键盘输入输出引脚
int key_pin_in[8] = {25,26,32,33,34,35,36,39};
int key_pin_out[8] = {2,4,13,14,18,19,23,27};
# define number_in 8
# define number_out 8
//定义键盘读取数组
int key_press[number_out][number_in] = {};
int old_key_press[number_out][number_in] = {};


//I2C总线信息
# define kbd_SDA 21
# define kbd_SCL 22




#endif