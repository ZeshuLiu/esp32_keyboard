#line 1 "d:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\save.h"
# ifndef SAVE_H
# define SAVE_H
# define KEYBOARD_VER 1
int DEFAULT_BOOT_MODE = 0;
//Save
struct Config_Keyboard
{
    int BOOT_MODE = 0;        //usb 0 ble 1
    uint8_t Version_KBD = KEYBOARD_VER  ;       //版本
};
Config_Keyboard Keyboard_Config;


void load_config();
void save_config();
# endif