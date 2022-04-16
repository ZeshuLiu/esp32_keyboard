# include "poker_keyboard.h"
# include "poker_bt.h"
# include <BleKeyboard.h>
# include <Wire.h>
# include "keyboard_self.h"
# include <Arduino.h>
# include "pcf8575.h"


void setup() {
  Serial.begin(115200);
  Serial.println("Joker setting up!");
  delay(1000);
  Wire.begin(21,22);

  //初始化输入引脚
  for (int i = 0; i < number_in; i++){
    pinMode(key_pin_in[i],INPUT_PULLUP);
  }

  //初始化输出引脚
  for (int j = 0; j < number_out; j++){
    pinMode(key_pin_out[j],OUTPUT);
    digitalWrite(key_pin_out[j],HIGH);
  }

  //键盘硬件设置
  keyboard_setup();
  Serial.println("Joker setted up!");
}

void loop() {
  // put your main code here, to run repeatedly:
  bt_work();
  delay(1000);
}
