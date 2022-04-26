#ifndef OLED_BUFF_H
#define OLED_BUFF_H
# include <Wire.h>
# include <SSD1306Wire.h>
# define SDA 21
# define SCL 22

# define ble_line 0
# define fn_line 1

String Line_Buff[6] = {} ;
#define buff_size 6
SSD1306Wire display(0x3c, SDA, SCL); 
bool oled_invert = 0;
void invert_disp(bool);

void LineDisp(String to_print,int line, bool if_clear=0);
void Oled_Start(void);
#endif