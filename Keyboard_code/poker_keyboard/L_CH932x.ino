#include "L_CH932x.h"
#include <Arduino.h>

bool L_CH9329::begin(uint8_t RX, uint8_t TX, uint16_t Buad_rate){
    Serial2.begin(Buad_rate,SERIAL_8N1,RX,TX);
    return 1;
}

void L_CH9329::muice_send(int x_mov,int y_mov,bool l_click, bool r_click, int scroll_move){
    // MOVE xy
    if(x_mov==0){
        muice_move_code[7] = 0x00;
    }
    else if (x_mov>0){
        muice_move_code[7] = x_mov%(0x80);
    }
    else{
       muice_move_code[7] = 0x100 + x_mov%(0x80);
    }

    if(y_mov==0){
        muice_move_code[8] = 0x00;
    }
    else if (y_mov>0){
        muice_move_code[8] = y_mov%(0x80);
    }
    else{
       muice_move_code[8] = 0x100 + y_mov%(0x80);
    }
    //end move xy

    // Move scroll
    if(scroll_move==0){
        muice_move_code[9] = 0x00;
    }
    else if (scroll_move>0){
        muice_move_code[9] = scroll_move%(0x80);
    }
    else{
       muice_move_code[9] = 0x100 + scroll_move%(0x80);
    }
    // end Move scroll

    //Click
    if (l_click){
      muice_move_code[6] = muice_move_code[6] | LEFT_CLICK;
    }
    else{
      muice_move_code[6] = muice_move_code[6] & (~LEFT_CLICK);
    }
    if (r_click){
      muice_move_code[6] = muice_move_code[6] | RIGHT_CLICK;
    }
    else{
      muice_move_code[6] = muice_move_code[6] & (~RIGHT_CLICK);
    }
    // end Click

    // Sum
    muice_move_code[10] = 0x00;
    for (int i = 0; i < 10; i++){
        muice_move_code[10] = (muice_move_code[10]+muice_move_code[i]);
    }
    // end Sum

    Serial2.write(muice_move_code,11);
    Serial.println(muice_move_code[6]);
    //Serial.println(muice_move_code[10]);
}

int8_t L_CH9329::muice_work(int x_enc,int y_enc,bool lc, bool rc){
  int16_t x_m=0, y_m=0;
  int16_t x_left=0, y_left=0;
  if (abs(x_enc) > dead_zone || abs(y_enc)>dead_zone){
      if (abs(x_enc)<600){
        x_m = (x_enc)/80;
        x_left = x_enc%80;
      }
      else if(x_enc>0){
        x_m = (x_enc)/30-13;
        x_left = x_enc%30;
      }
      else{
        x_m = (x_enc)/30+12;
        x_left = x_enc%30;
      }

      if (abs(y_enc)<600){
        y_m = (y_enc)/80;
        y_left = y_enc%80;
      }
      else if(y_enc>0){
        y_m = (y_enc)/30-13;
        y_left = y_enc%30;
      }
      else{
        y_m = (y_enc)/30+12;
        y_left = y_enc%30;
      }


        muice_send(x_m%127,y_m%127,lc,rc);
        //Serial.println(String(x_m));
    }
    else{
        muice_send(0,0,lc,rc);
    }
    return 1+max(abs(x_left),abs(y_left));
}

void L_CH9329::set_dead_zone(uint8_t newzone) {
    dead_zone = newzone;
}

void L_CH9329::general_keyboard_send(uint8_t key_code[8]){
    general_keyboard_code[13] = 0x00;
    
    for (int i = 0; i < 8; i++){
      general_keyboard_code[i+5] = key_code[i];
    }
    
    for (int i = 0; i < 13; i++){
        general_keyboard_code[13] = (general_keyboard_code[13]+general_keyboard_code[i]);
    }
    Serial.println(String(key_code[2]));
    Serial2.write(general_keyboard_code,14);
}

void L_CH9329::media_keyboard_change(uint8_t line, uint8_t code, bool ifpress){
    uint8_t pos = 5+line;
    if (ifpress==1){
      media_keyboard_code[pos] = media_keyboard_code[pos]|code;
    }
    else{
      media_keyboard_code[pos] = media_keyboard_code[pos]&(!code);
    }
}

void L_CH9329::media_keyboard_send(){
    media_keyboard_code[9] = 0x00;
    for (int i = 0; i < 9; i++){
        media_keyboard_code[9] = (media_keyboard_code[9]+media_keyboard_code[i]);
    }
    Serial.println(String(media_keyboard_code[2]));
    Serial2.write(media_keyboard_code,10);
}
void L_CH9329::media_keyboard_clear(){
    for (int i = 6; i < 10; i++){
      media_keyboard_code[i] = 0x00;
    }

    for (int i = 0; i < 9; i++){
        media_keyboard_code[9] = (media_keyboard_code[9]+media_keyboard_code[i]);
    }
    Serial.println("clear Media code");
    Serial2.write(media_keyboard_code,10);
}