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
