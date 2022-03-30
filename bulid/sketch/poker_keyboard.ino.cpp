#include <Arduino.h>
#line 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
#include "poker_keyboard.h"
#include "poker_bt.h"
#include <BleKeyboard.h>


#line 6 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
void setup();
#line 11 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
void loop();
#line 6 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino"
void bt_test();
#line 6 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
void setup() {
  Serial.begin(115200);
  Serial.println("Joker setting up!");
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
    pinMode(39,INPUT);
    if(DBG_KEYBOARD){
        Serial.println("Starting BLE work!");
    }

    bleKeyboard.begin();//Start blekeyboard service

    for(;;){
    
        if(bleKeyboard.isConnected()&&digitalRead(39)) {
            Serial.println("Sending 'Hello world'...");
            bleKeyboard.print("Hello world");
            delay(1000);

            Serial.println("Sending Enter key...");
            bleKeyboard.write(KEY_RETURN);

            delay(1000);

            Serial.println("Sending Play/Pause media key...");

            bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

            delay(1000);
            Serial.println("Sending Ctrl+Alt+Delete...");
            bleKeyboard.press(KEY_W);
            delay(100);
            bleKeyboard.releaseAll();
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

  }
    }
  Serial.println("Waiting 5 seconds...");
  delay(5000);
}

