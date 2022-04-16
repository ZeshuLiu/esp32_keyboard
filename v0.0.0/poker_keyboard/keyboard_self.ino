# include "keyboard_self.h"
# include "poker_keyboard.h"
# include "pcf8575.h"


void keyboard_setup(){
  //初始化io扩展
  pcf8575_begin();
}

void open_keyboard_led(){
    if ((write_low&LED_PIN)!=0){//高电平
      write_low = write_low&(~LED_PIN);
      pcf8575_writeAll(word(B11111111,write_low));
    }
    Serial.println("LED ON");
    LED_STAT = 1;
}

void close_keyboard_led(){
    write_low = write_low|LED_PIN;
    pcf8575_writeAll(word(B11111111,write_low));
    Serial.println("LED OFF");
    LED_STAT = 0;
}

void open_caps_led(){
    if ((write_low&CAP_LED_PIN)!=0){//高电平
      write_low = write_low&(~CAP_LED_PIN);
      pcf8575_writeAll(word(B11111111,write_low));
    }
    Serial.println("CAP ON");
    CAP_LED_STAT = 1;
}

void close_caps_led(){
    write_low = write_low|CAP_LED_PIN;
    pcf8575_writeAll(word(B11111111,write_low));
    Serial.println("CAP OFF");
    CAP_LED_STAT = 0;
}


void keyboard_device_test(){
    open_keyboard_led();
    delay(100);
    close_caps_led();
    delay(5000);
    close_keyboard_led();
    delay(100);
    open_caps_led();

}