# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
# 2 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 3 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 4 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino" 2


void setup() {
  Serial.begin(115200);
  Serial.println("Joker setting up!");
  delay(10000);
  pinMode(2,0x02);
  digitalWrite(2,0x1);
}

void loop() {
  // put your main code here, to run repeatedly:
  bt_test();
}
# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino"

# 3 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino" 2

BleKeyboard bleKeyboard("Joker" /*设备名*/, "Liu" /*设备制造商*/, 100 /*电量*/);

void bt_test(){
  int i = 0;
    pinMode(39,0x01);
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
# 38 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino"
          i = (i+1)%2;
  }
    }
  Serial.println("Waiting 5 seconds...");
  delay(5000);
}
