#include "poker_keyboard.h"
#include "poker_bt.h"
#include <BleKeyboard.h>


void setup() {
  Serial.begin(115200);
  Serial.println("Joker setting up!");
}

void loop() {
  // put your main code here, to run repeatedly:
  bt_test();
}
