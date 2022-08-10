#include "Seg_disp.h"

void init_seg(){
    #ifdef MasterYoda
    tm1637.init();
    tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
    tm1637.display(0, (8));
    tm1637.display(1, (8));
    tm1637.display(2, (8));
    tm1637.display(3, (8));
    tm1637.point(0);
    Serial.println("Seg ON");
    delay(200);
    #endif
}