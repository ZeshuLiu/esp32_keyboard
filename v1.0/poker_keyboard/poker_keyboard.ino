# include "poker_keyboard.h"
# include "poker_bt.h"
# include <BleKeyboard.h>
# include <Wire.h>
# include "keyboard_self.h"
# include <Arduino.h>
# include "pcf8575.h"
# include "scan.h"
# include "joker_usb.h"
# include "oled_buff.h"


void setup() {
  // DBG 设置
  Serial.begin(115200);
  Serial.println("Joker setting up!");
  delay(1000);

  // I2c 设置
  Wire.begin(21,22);
  Serial.println("I2C SET!");

  //初始化扫描工作
  scan_start();
  Serial.println("SCAN SET!");

  // 9328USB输出
  Serial2.begin(9600, SERIAL_8N1, 17, 16); 
  delay(1000);
  Serial.println("USB SET!");

  //键盘硬件设置
  keyboard_setup();
  Oled_Start();
  LineDisp("      Joker 60 by LiuZS      ",33);
  LineDisp("====Started!====",0);
  //LineDisp("                              1.0",4);
  delay(2000);
  LineDisp(" ",3);
  Serial.println("Joker setted up!");


  if(DFT_BOOT_MODE == 0){
    joker_usb_start();
    //joker_usb_work();
  }
  if(DFT_BOOT_MODE == 1){
    joker_bt_start();
  }
  cnt_start();
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(1000);
}

