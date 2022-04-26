#include "oled_buff.h"

# define HEIGHT_WORDS 9 

void Oled_Start(void){    // 开启oled显示
  display.init();
  display.flipScreenVertically();
  
}

void LineDisp(String to_print,int line, bool if_clear){
    display.clear();
    if (if_clear){
        for(int i=0; i<buff_size; i++){
        Line_Buff[i] = "";
    }
    }
    Line_Buff[line] = to_print;
    for(int i=0; i<buff_size; i++){
        display.drawString(0, HEIGHT_WORDS*i ,Line_Buff[i]);
    }
    display.display();
}

void invert_disp(bool if_invert){
    if (!if_invert){//不反向
        if (oled_invert){//是反向
            display.normalDisplay();
            oled_invert = 0;
        }
    }
    else{//反显
        if (!oled_invert){
            display.invertDisplay();
            oled_invert = 1;
        }
    }
    
}