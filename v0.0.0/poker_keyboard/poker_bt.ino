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
