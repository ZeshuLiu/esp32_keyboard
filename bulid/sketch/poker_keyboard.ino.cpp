#include <Arduino.h>
#line 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
#include "poker_keyboard.h"
#include "poker_bt.h"
#include <BleKeyboard.h>


#line 6 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
void setup();
#line 14 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
void loop();
#line 6 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino"
void bt_test();
#line 6 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
void setup() {
  Serial.begin(115200);
  Serial.println("Joker setting up!");
  delay(10000);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  bt_test();
}

#line 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino"
#include <BleKeyboard.h>
#include "poker_bt.h"

BleKeyboard bleKeyboard(DeviceName, Manufacturer, DevicePower);

void bt_test(){
  int i = 0;
    pinMode(39,INPUT);
    if(DBG_KEYBOARD){
        Serial.println("Starting BLE work!");
    }

    bleKeyboard.begin();//Start blekeyboard service

    for(;;){
    
        if(bleKeyboard.isConnected()&&digitalRead(39)) {
            Serial.println("w");
            if(i==0){
              bleKeyboard.press(KEY_W);
            }
             if(i==1){
               bleKeyboard.releaseAll();
             }

            //bleKeyboard.releaseAll();
            //
            // Below is an example of pressing multiple keyboard modifiers 
            // which by default is commented out. 
            // 
            /* Serial.println("Sending Ctrl+Alt+Delete...");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.press(KEY_LEFT_ALT);
            bleKeyboard.press(KEY_DELETE);
            delay(100);
            bleKeyboard.releaseAll();
            */
          i = (i+1)%2;
  }
    }
  Serial.println("Waiting 5 seconds...");
  delay(5000);
}

