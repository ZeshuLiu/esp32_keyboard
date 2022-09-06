#line 1 "d:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\oled_buff.h"
#ifndef OLED_BUFF_H
#define OLED_BUFF_H
# include <Wire.h>
# include <SSD1306Wire.h>
# include "Layout.h"

# ifdef Joker
# define SDA 21
# define SCL 22
# define OLED_BRIGHT 127


# define ble_line 0
# define fn_line 1
int oled_mode = 0; // 0-字符 1-图片

String Line_Buff[6] = {} ;
#define buff_size 6
SSD1306Wire display(0x3c, SDA, SCL); 
bool oled_invert = 0;
void invert_disp(bool);

void LineDisp(String to_print,int line, bool if_clear=0);
void Oled_Start(void);
void draw_dog();

#endif
#endif