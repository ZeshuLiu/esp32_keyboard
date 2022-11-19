#ifndef L_CH9329_H
#define L_CH9329_H
#include <Arduino.h>
//#include "poker_keyboard.h"
//#include "L_CH932x.cpp"
#define BUAD_RATE 9600



class L_CH9329{

private:
    uint8_t muice_move_code[11] = {0x57,0xAB,0x00,0x05,0x05, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t general_keyboard_code[14] = {0x57, 0xAB, 0x00, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t media_keyboard_code[10] = {0x57, 0xAB, 0x00, 0x03, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t LEFT_CLICK = 0x01;
    uint8_t RIGHT_CLICK = 2;

public:
    uint8_t dead_zone;
    void L_CH9329_(void){
        dead_zone = 15; 
        //muice_move_code = {0x57,0xAB,0x00,0x05,0x05, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00};
    }
    bool begin(uint8_t RX, uint8_t TX, uint16_t Buad_rate = BUAD_RATE);
    void muice_send(int x_mov,int y_mov,bool l_click = 0, bool r_click = 0, int scroll_move = 0);
    int8_t muice_work(int x_enc,int y_enc,bool lc, bool rc);
    void set_dead_zone(uint8_t newzone);
    void general_keyboard_send(uint8_t key_code[8]);
    void media_keyboard_change(uint8_t line, uint8_t code, bool ifpress);
    void media_keyboard_send();
    void media_keyboard_clear();
    //L_CH932x();
};


#endif
