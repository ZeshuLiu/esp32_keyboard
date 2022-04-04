#include "poker_keyboard.h"
#include "poker_bt.h"
#include <BleKeyboard.h>


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
