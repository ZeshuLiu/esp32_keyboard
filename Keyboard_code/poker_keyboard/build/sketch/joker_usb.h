#line 1 "g:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.h"
# ifndef JOKER_USB_H
# define JOKER_USB_H

#include "Layout.h"
#include "poker_keyboard.h"

BaseType_t xReturned_usb;
TaskHandle_t USB_TASK_Handle = NULL;

#define USB_TASK_CORE 0
#define USB_TASK_STACK 9192
#define USB_TASK_PRI 4
#define USB_TASK_DELAY 1

uint8_t key_code[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
bool USB_to_change_mode = 0;
int USB_chang_mode_time;


void joker_usb_test();
//void joker_usb_work();
bool joker_usb_start();
void joker_usb2bt();
#endif
