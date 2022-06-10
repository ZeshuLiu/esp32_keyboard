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
# include "save.h"

void setup() {
  // DBG 设置
  Serial.begin(115200);
  Serial.println("Joker setting up!");
  delay(100);

  //读取保存的数据
  load_config();
  DFT_BOOT_MODE = Keyboard_Config.BOOT_MODE ;
  Serial.println(String(DFT_BOOT_MODE));
  Serial.println(String(Keyboard_Config.Version_KBD));
  // I2c 设置
  Wire.begin(21,22);
  Serial.println("I2C SET!");

  //初始化扫描工作
  scan_start();
  Serial.println("SCAN SET!");

  // 9328USB输出
  Serial2.begin(115200, SERIAL_8N1, 17, 16); 
  delay(100);
  Serial.println("USB SET!");

  //键盘硬件设置
  keyboard_setup();
  Oled_Start();
  LineDisp("      Joker 60 by LiuZS      ",3);
  LineDisp("====Started!====",0);
  display.drawString(0,0 ,"Joker On !");
  display.display();
  //LineDisp("                              1.0",4);
  delay(200);
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
