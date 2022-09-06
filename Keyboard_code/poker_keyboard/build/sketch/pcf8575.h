#line 1 "d:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\pcf8575.h"
#ifndef PCF8575_H
#define PCF8575_H

#include <Wire.h>
#include "poker_keyboard.h"
# include <Arduino.h>

#define pcf_address 0x20
void pcf8575_readAll();
void pcf8575_writeAll(uint16_t data);
void pcf8575_begin();

#define P00 B00000001
#define P01 B00000010
#define P02 B00000100
#define P03 B00001000
#define P04 B00010000
#define P05 B00100000
#define P06 B01000000
#define P07 B10000000
//#define P00 B00000001

#endif