# include "oled_buff.h"
# include "Pic.h"
# define HEIGHT_WORDS 9 

void Oled_Start(void){    // 开启oled显示
  display.init();
  display.flipScreenVertically();
  display.setBrightness(OLED_BRIGHT);
}

void LineDisp(String to_print,int line, bool if_clear){
    if (if_clear){
        for(int i=0; i<buff_size; i++){
            Line_Buff[i] = "";
        }
    }
    Line_Buff[line] = to_print;

    if(oled_mode == 0){
        display.clear();

        for(int i=0; i<buff_size; i++){
            display.drawString(0, HEIGHT_WORDS*i ,Line_Buff[i]);
        }
        display.display();
    }
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

void draw_dog(){
    if (oled_mode==1){
        display.clear(); //for Clearing the display
        display.drawXbm(0, 0, 128, 64, dog_bmp);
        display.display();
    }
}
