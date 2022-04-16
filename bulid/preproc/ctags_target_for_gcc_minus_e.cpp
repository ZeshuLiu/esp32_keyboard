# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
# 2 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 3 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino" 2

# 5 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 6 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 7 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 8 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino" 2


void setup() {
  Serial.begin(115200);
  Serial.println("Joker setting up!");
  delay(1000);
  Wire.begin(21,22);

  //初始化输入引脚
  for (int i = 0; i < 8; i++){
    pinMode(key_pin_in[i],0x05);
  }

  //初始化输出引脚
  for (int j = 0; j < 11; j++){
    pinMode(key_pin_out[j],0x02);
    digitalWrite(key_pin_out[j],0x1);
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
# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\keyboard_self.ino"
# 2 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\keyboard_self.ino" 2
# 3 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\keyboard_self.ino" 2
# 4 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\keyboard_self.ino" 2


void keyboard_setup(){
  //初始化io扩展
  pcf8575_begin();
}

void open_keyboard_led(){
    if ((write_low&1)!=0){//高电平
      write_low = write_low&(~1);
      pcf8575_writeAll(makeWord(255,write_low));
    }
    Serial.println("LED ON");
    LED_STAT = 1;
}

void close_keyboard_led(){
    write_low = write_low|1;
    pcf8575_writeAll(makeWord(255,write_low));
    Serial.println("LED OFF");
    LED_STAT = 0;
}

void open_caps_led(){
    if ((write_low&2)!=0){//高电平
      write_low = write_low&(~2);
      pcf8575_writeAll(makeWord(255,write_low));
    }
    Serial.println("CAP ON");
    CAP_LED_STAT = 1;
}

void close_caps_led(){
    write_low = write_low|2;
    pcf8575_writeAll(makeWord(255,write_low));
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
# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\pcf8575.ino"
# 2 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\pcf8575.ino" 2

void pcf8575_begin(){
    pcf8575_writeAll(makeWord(255,255));
}

void pcf8575_writeAll(uint16_t data) {
  Wire.beginTransmission(0x20);
  Wire.write(((uint8_t) ((data) & 0xff)));
  Wire.write(((uint8_t) ((data) >> 8)));
  Wire.endTransmission();
}

void pcf8575_readAll() {
    Wire.requestFrom(0x20, 16); // Request 8 bytes from slave device number two
    // Slave may send less than requested
 byte b1 = Wire.read();
 byte b2 = Wire.read();

    if (DBG_KEYBOARD){
        Serial.println("..");
        Serial.println(b1);
     Serial.println(b2);
    }

}
# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino"
# 2 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino" 2

BleKeyboard bleKeyboard("Joker_KEY" /*设备名*/, "Liu" /*设备制造商*/, 100 /*电量*/);

void bt_test(){
  int i = 0;
    pinMode(34,0x01);
    if(DBG_KEYBOARD){
        Serial.println("Starting BLE TEST!");
    }

    bleKeyboard.begin();//Start blekeyboard service
  pinMode(2,0x02);
  //
    for(;;){

        if(bleKeyboard.isConnected()&&(!digitalRead(34))) {
            Serial.println("w");
            if(i==0){
              bleKeyboard.press(KEY_W);
              digitalWrite(2,0x1);
            }
             if(i==1){
               bleKeyboard.releaseAll();
               digitalWrite(2,0x0);
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
# 40 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino"
          i = (i+1)%2;
  }
    }
  Serial.println("Waiting 5 seconds...");
  delay(5000);
}

void bt_work(){
  if(DBG_KEYBOARD){
        Serial.println("Starting BLE work!");
  }

  bleKeyboard.begin();//Start blekeyboard service


bool start_flag = 0;
//循环扫描
for (;;){
  if (bleKeyboard.isConnected()){//连接上
    bt_stat = 1;

     //第一次先赋值

    if (!start_flag){
      Serial.println("connected!");
    }

      //扫描
      for (int ROW = 0; ROW < 11; ROW++){

        //写电平：将j列写为低，其余为高
        for (int i = 0; i < 11; i++){
          if (i!=ROW){
           digitalWrite(key_pin_out[i], 0x1);
          }
          if (i==ROW){
            digitalWrite(key_pin_out[i], 0x0);
          }
        }//写电平结束

        //读取电平
        for (int COL = 0; COL < 8; COL++){
          key_press[ROW][COL] = digitalRead(key_pin_in[COL]);

          //判断键值变化
          if (start_flag & ( (old_key_press[ROW][COL]!=key_press[ROW][COL]) ||( iw==1&&( ROW==10&&COL==0 ) ))){
            if (DBG_KEYBOARD){
              Serial.println("***["+ String(ROW) + "," + String(COL) + "]:" + String(key_press[ROW][COL])+ "means:" + String(LayOut[ROW][COL]) );
            }

            //防止iw双击
            if((ROW==0&&COL==0)&&(key_press[ROW][COL]==0)&&(!iw)){ // 进入w，防止双击
              iw = 1 ;
              if(DBG_KEYBOARD){
                Serial.println("W?");
              }
              continue;
            }

            if(iw==1&&(ROW==10&&COL==0)&&(key_press[ROW][COL]==1)){//w么有，这是i
              bleKeyboard.press(LayOut[0][0]);
              continue;
            }
            if(iw==1&&(ROW==10&&COL==0)&&(key_press[ROW][COL]==0)){//w按下
              bleKeyboard.press(LayOut[10][0]);
              continue;
            }
            if((ROW==0&&COL==0)&&key_press[ROW][COL]==1){ // 00松开
              iw = 0 ;
            }
            //防止iw双击结束

            //发送按键
            if ((LayOut[ROW][COL]!=0)){
              if (key_press[ROW][COL]==0){//如果低电平则按下
                bleKeyboard.press(LayOut[ROW][COL]);
              }
              if(key_press[ROW][COL]==1){//高电平则松开
                bleKeyboard.release(LayOut[ROW][COL]);
              }
            }//发送结束

          }//判断键值变化结束

        }//读取结束

      }//扫描结束

    //新旧赋值
    for (int i = 0; i < 11; i++){
      for (int j = 0; j < 8; j++){
        old_key_press[i][j] = key_press[i][j];
      }
    }//新旧赋值结束

    if(!start_flag){
      start_flag = 1;
    }

  } //一直尝试连接
  delay(10);

}//循环扫描不会结束

}//end bt_work
