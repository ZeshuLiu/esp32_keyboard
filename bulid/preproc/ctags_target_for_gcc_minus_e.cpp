# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_keyboard.ino"
# 2 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 3 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_keyboard.ino" 2

# 5 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 6 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 7 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 8 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 9 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 10 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_keyboard.ino" 2
# 11 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_keyboard.ino" 2


void setup() {
  // DBG 设置
  Serial.begin(115200);
  Serial.println("Joker setting up!");
  delay(1000);

  // I2c 设置
  Wire.begin(21,22);
  Serial.println("I2C SET!");

  //初始化扫描工作
  scan_start();
  Serial.println("SCAN SET!");

  // 9328USB输出
  Serial2.begin(9600, 0x800001c, 17, 16);
  delay(1000);
  Serial.println("USB SET!");

  //键盘硬件设置
  keyboard_setup();
  Oled_Start();
  LineDisp("      Joker 60 by LiuZS      ",33);
  LineDisp("====Started!====",0);
  //LineDisp("                              1.0",4);
  delay(2000);
  LineDisp(" ",3);
  Serial.println("Joker setted up!");


  if(0 /*0是usb，1是蓝牙*/ == 0){
    joker_usb_start();
    //joker_usb_work();
  }
  if(0 /*0是usb，1是蓝牙*/ == 1){
    joker_bt_start();
  }
  cnt_start();
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(1000);
}
# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\joker_usb.ino"
# 2 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\joker_usb.ino" 2
# 3 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\joker_usb.ino" 2
# 4 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\joker_usb.ino" 2
# 5 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\joker_usb.ino" 2
# 6 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\joker_usb.ino" 2



void joker_usb_test(){
    if (key_code[2] == 0x00){
        key_code[2] = 0x04 /* a and A*/;
        Serial.println("set");
    }
    delay(100);
    Serial2.write(key_code,8);

    key_code[2] = 0x00;
    delay(1000);
    Serial2.write(key_code,8);

    Serial.println("sending");

}

void joker_usb_work(void *pvParameters){
    bool start_flag = 0;
    bool usb_send = 0;
    for (int i = 0; i < 8; i++)
    {
        key_code[i] = 0x00;
    }
    LineDisp("<MODE>===========USB", 0);
    LineDisp("<FN>----------------------------OFF", 1);

    for (;;){
        int start_time = micros();

        key_scan();

        //PN按下
        if(pn_stat){//pn被按下
            if ((key_press[2][4]==0)&&(old_key_press[2][4]==1)){ //LED 控制
                if(!LED_STAT){
                    open_inter_led();
                }
                else{
                    close_inter_led();
                }
            }//LED 控制

            //MODE 控制
            if((key_press[1][5]==0)&&(old_key_press[1][5]==1)){ // 第一次按下
                USB_to_change_mode = 1;
                USB_chang_mode_time = millis();
                LineDisp("<MODE>===========CHG", 0);
            }
            if ((key_press[1][5]==0)&&USB_to_change_mode&&((millis()-USB_chang_mode_time)>3000)){//连续按压了三秒以上
                USB_to_change_mode = 0;
                joker_usb2bt();
                LineDisp("<MODE>===========BTS", 0);
            }
            if(USB_to_change_mode&&(key_press[1][5]==1)){//三秒内放开
                USB_to_change_mode = 0;
                LineDisp("<MODE>===========USB", 0);
            }
            //MODE 控制

            //重置倒计时
            if ((key_press[7][0]==0)&&(old_key_press[7][0]==1)){
                rst_cnt_time = 1;
            }
            //重置倒计时


        }
        //PN第一次按下
        if(start_flag&&(pn_stat==0)&&(key_press[2][7] == 0)){//PN第一次按下
            if (DBG_KEYBOARD){
                Serial.println("PN ON!");
            }
            for (int i = 0; i < 8; i++){
                key_code[i] = 0x00;
            }
            usb_send = 1;

            pn_stat = 1;
        }//pn第一次按下
        //PN第一次松开
        if(start_flag&&(pn_stat==1)&&(key_press[2][7] == 1)){//PN第一次松开
            if (DBG_KEYBOARD){
                Serial.println("PN OFF!");
            }
            pn_stat = 0;
            USB_to_change_mode = 0;
        }//pn第一次松开

        // FN 第一次被按下
        if (start_flag&&(key_press[7][7]==0)&&(fn_stat==0)){
            if (DBG_KEYBOARD){
            Serial.println("FN IS ON !");
            }
            LineDisp("<FN>-----------------------------ON", 1);
            fn_stat = 1;
            for (int ROW = 0; ROW < 8; ROW++){//行循环判断
                for (int COL = 0; COL < 8; COL++){//列循环
                    if((old_key_press[ROW][COL]==0)&&(key_press[ROW][COL]==0)&&(USB_LayOut_ALL[ROW][COL]!=USB_LayOut_ALL_FN[ROW][COL])){//键被按下，且此键的键值在fn按下后发生了变化
                        usb_send = 1;
                        if(USB_LayOut_ALL[ROW][COL]!=USB_LayOut_words[ROW][COL]){//是第一位的键值
                                key_code[0] = key_code[0]|USB_LayOut_ALL[ROW][COL];
                        }//是第一位的键值

                        else{//是正常的键值
                            words_change(USB_LayOut_ALL[ROW][COL],1); //松开不是fn的键值
                            words_change(USB_LayOut_words_FN[ROW][COL],0); //按下fn对应的键值
                        }//是正常的键值
                    }// 按下fn后改变键值结束
                }//列循环
            }//行循环判断
        }//fn第一次按下结束
        // FN 第一次被松开
        if (start_flag&&(key_press[7][7]==1)&&(fn_stat==1)){
            if (DBG_KEYBOARD){
                Serial.println("FN IS OFF !");
            }
            LineDisp("<FN>----------------------------OFF", 1);
            fn_stat = 0;

            for (int ROW = 0; ROW < 8; ROW++){//行循环判断
                for (int COL = 0; COL < 8; COL++){//列循环
                    if((old_key_press[ROW][COL]==0)&&(key_press[ROW][COL]==0)&&(USB_LayOut_ALL[ROW][COL]!=USB_LayOut_ALL_FN[ROW][COL])){//键被按下，且此键的键值在fn按下后发生了变化
                        usb_send = 1;
                        if(USB_LayOut_ALL[ROW][COL]!=USB_LayOut_words[ROW][COL]){//是第一位的键值
                                key_code[0] = key_code[0]&(!USB_LayOut_ALL[ROW][COL]);
                        }//是第一位的键值

                        else{//是正常的键值
                            words_change(USB_LayOut_words_FN[ROW][COL],1); //松开是fn的键值
                            words_change(USB_LayOut_words[ROW][COL],0); //按下fn对应的键值
                        }//是正常的键值
                    }//松开fn改变键值结束
                }
            }
        }//fn第一次松开结束

        //循环赋值
        for (int ROW = 0; ROW < 8; ROW++){//循环赋值
            for (int COL = 0; COL < 8; COL++){
                if (start_flag && (old_key_press[ROW][COL]!=key_press[ROW][COL]) &&(!pn_stat)){//键值变化且pn没有按下
                        usb_send = 1;
                    if(USB_LayOut_ALL[ROW][COL]!=USB_LayOut_words[ROW][COL]){//是第一位的键值
                        if(key_press[ROW][COL]==0){//按下
                            if(fn_stat){
                                key_code[0] = key_code[0]|USB_LayOut_ALL_FN[ROW][COL];
                            }
                            else{
                                key_code[0] = key_code[0]|USB_LayOut_ALL[ROW][COL];
                            }
                        }
                        if(key_press[ROW][COL]==1){//松开
                            if(fn_stat){
                                key_code[0] = key_code[0]&(!USB_LayOut_ALL_FN[ROW][COL]);
                            }
                            else{
                                key_code[0] = key_code[0]&(!USB_LayOut_ALL[ROW][COL]);
                            }
                        }
                    }//是第一位的键值

                    else{//是正常的键值
                        if(fn_stat){
                                words_change(USB_LayOut_ALL_FN[ROW][COL],key_press[ROW][COL]);
                            }
                            else{
                                words_change(USB_LayOut_ALL[ROW][COL],key_press[ROW][COL]);
                            }
                    }//是正常的键值

                }//键值变化结束

            }//列结束   
        }//行结束

        //新旧赋值
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                old_key_press[i][j] = key_press[i][j];
            }
        }//新旧赋值结束

        if(!start_flag){
            start_flag = 1;
        }
        //发送按键
        if (usb_send){
            Serial2.write(key_code,8);
            usb_send = 0; //发送后设置为0

            if (DBG_KEYBOARD){
                Serial.println("sending:" + String(key_code[0]));
                Serial.println("Time:" + String(micros()-start_time));
            }
        }

        vTaskDelay(4);


    }//循环扫描不会停止

}

void words_change(uint8_t word_name, bool stat){
    if(stat==0){//按下
        for (int i = 2; i < 8; i++){//找地方放
            if (key_code[i]==0x00){
                key_code[i]=word_name;
                    break;
            }
        }
    }
    if(stat==1){//松开
        for (int i = 2; i < 8; i++){//找地方放
            if (key_code[i]==word_name){
                key_code[i]=0x00;
                break;
            }
        }
    }
}


bool joker_usb_start(){
    xReturned_usb = xTaskCreatePinnedToCore(joker_usb_work, "JOKER USB WORK", 9192, 
# 232 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\joker_usb.ino" 3 4
                                                                                             __null
# 232 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\joker_usb.ino"
                                                                                                 , 4, &USB_TASK_Handle, 0) ;
    if(xReturned_usb == ( ( ( BaseType_t ) 1 ) )){
        return 1;
    }
    return 0;
}

void joker_usb2bt(){
    Serial.println("CHANGING MODE!");
    if(USB_TASK_Handle!=
# 241 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\joker_usb.ino" 3 4
                       __null
# 241 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\joker_usb.ino"
                           ){
        vTaskDelete(USB_TASK_Handle);
        USB_TASK_Handle = 
# 243 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\joker_usb.ino" 3 4
                         __null
# 243 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\joker_usb.ino"
                             ;
        Serial.println("USB TASK DELETE");
    }

    delay(1000);
    joker_bt_start();
}
# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\keyboard_self.ino"
# 2 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\keyboard_self.ino" 2
# 3 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\keyboard_self.ino" 2
# 4 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\keyboard_self.ino" 2
# 5 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\keyboard_self.ino" 2


void keyboard_setup(){
  //初始化io扩展
  //pcf8575_begin();
  pinMode(12,0x02);
  open_inter_led();
  invert_disp(1);
  delay(1000);
  close_inter_led();
  invert_disp(0);
}

void open_inter_led(){
  digitalWrite(12,0x1);
  LED_STAT = 1;
}
void close_inter_led(){
  digitalWrite(12,0x0);
  LED_STAT = 0;
}

void open_i2c_keyboard_led(){
    if ((write_low&12)!=0){//高电平
      write_low = write_low&(~12);
      pcf8575_writeAll(makeWord(255,write_low));
    }
    Serial.println("LED ON");
    LED_STAT = 1;
}

void close_i2c_keyboard_led(){
    write_low = write_low|12;
    pcf8575_writeAll(makeWord(255,write_low));
    Serial.println("LED OFF");
    LED_STAT = 0;
}

void open_i2c_caps_led(){
    if ((write_low&2)!=0){//高电平
      write_low = write_low&(~2);
      pcf8575_writeAll(makeWord(255,write_low));
    }
    Serial.println("CAP ON");
    CAP_LED_STAT = 1;
}

void close_i2c_caps_led(){
    write_low = write_low|2;
    pcf8575_writeAll(makeWord(255,write_low));
    Serial.println("CAP OFF");
    CAP_LED_STAT = 0;
}

void cnt_work(void *pvParameters){
  int start_time = millis();
  int time_pass;
  int cnt_down;
  for (;;){
    if(rst_cnt_time){
      start_time = millis();
      rst_cnt_time = 0;
      vTaskDelay(1000);
    }
    time_pass = millis() - start_time;
    cnt_down = CNT_TIME - time_pass;
    //LineDisp("<COUNT DOWN>---------" + String(cnt_down/60000),5);
    if (cnt_down<=0){
      LineDisp("<Need Rest in>---------NOW!",5);
      invert_disp(1);
    }
    else{
      LineDisp("<Need Rest in>---------" + String(cnt_down/60000),5);
      invert_disp(0);
    }
    vTaskDelay(1000);
  }
}

bool cnt_start(){
  xReturned_cnt = xTaskCreatePinnedToCore(cnt_work, "JOKER CNT WORK", 2048, 
# 85 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\keyboard_self.ino" 3 4
                                                                                     __null
# 85 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\keyboard_self.ino"
                                                                                         , 10, &CNT_TASK_Handle, 1) ;
  if(xReturned_cnt == ( ( ( BaseType_t ) 1 ) )){
    return 1;
  }
  return 0;
}


void keyboard_device_test(){
    open_i2c_keyboard_led();
    delay(100);
    close_i2c_caps_led();
    delay(5000);
    close_i2c_keyboard_led();
    delay(100);
    open_i2c_caps_led();
}
# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\oled_buff.ino"
# 2 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\oled_buff.ino" 2



void Oled_Start(void){ // 开启oled显示
  display.init();
  display.flipScreenVertically();

}

void LineDisp(String to_print,int line, bool if_clear){
    display.clear();
    if (if_clear){
        for(int i=0; i<6; i++){
        Line_Buff[i] = "";
    }
    }
    Line_Buff[line] = to_print;
    for(int i=0; i<6; i++){
        display.drawString(0, 9*i ,Line_Buff[i]);
    }
    display.display();
}

void invert_disp(bool if_invert){
    if (!if_invert){//不反向
        if (oled_invert){//是反向
            display.normalDisplay();
            oled_invert = 0;
        }
    }
    else{//反显
        if (!oled_invert){
            display.invertDisplay();
            oled_invert = 1;
        }
    }

}
# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\pcf8575.ino"
# 2 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\pcf8575.ino" 2

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
# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_bt.ino"
# 2 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_bt.ino" 2
# 3 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_bt.ino" 2
# 4 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_bt.ino" 2
# 5 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_bt.ino" 2

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
# 43 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_bt.ino"
          i = (i+1)%2;
  }
    }
  Serial.println("Waiting 5 seconds...");
  delay(5000);
}

/*

蓝牙工作模式

*/
# 53 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_bt.ino"
void bt_work(void *pvParameters){
  if(DBG_KEYBOARD){
        Serial.println("Starting BLE work!");
  }

  bleKeyboard.begin();//Start blekeyboard service
  LineDisp("Waiting for BLE", 0);

bool start_flag = 0;
//循环扫描
for (;;){
  if (bleKeyboard.isConnected()){//连接上
    bt_stat = 1;

     //第一次先赋值

    if (!start_flag){
      Serial.println("connected!");
      //LineDisp(">========BLE========<", ble_line);
      LineDisp("<MODE>===========BLE", 0);
      LineDisp("<FN>-------------------------OFF", 1);
    }

    //扫描
    key_scan();

    //PN按下
    if(pn_stat){//pn被按下
      if ((key_press[2][4]==0)&&(old_key_press[2][4]==1)){ //LED 控制
        if(!LED_STAT){
          open_inter_led();
        }
        else{
          close_inter_led();
        }
      }//LED 控制

    }
    //PN第一次按下
    if(start_flag&&(pn_stat==0)&&(key_press[2][7] == 0)){//PN第一次按下
      if (DBG_KEYBOARD){
        Serial.println("PN ON!");
      }
      for (int i = 0; i < 8; i++){
        bleKeyboard.releaseAll();
      }

      pn_stat = 1;
    }//pn第一次按下
    //PN第一次松开
    if(start_flag&&(pn_stat==1)&&(key_press[2][7] == 1)){//PN第一次松开
      if (DBG_KEYBOARD){
        Serial.println("PN OFF!");
      }
      pn_stat = 0;
    }//pn第一次松开

    if (start_flag&&(key_press[7][7]==0)&&(fn_stat==0)){ // FN 第一次被按下
      if (DBG_KEYBOARD){
        Serial.println("FN IS ON !");
      }
      LineDisp("<FN>--------------------------ON", 1);
      fn_stat = 1;

      for (int ROW = 0; ROW < 8; ROW++){//行循环判断
        for (int COL = 0; COL < 8; COL++){//列循环
          if((old_key_press[ROW][COL]==0)&&(key_press[ROW][COL]==0)&&(LayOut_ALL[ROW][COL]!=LayOut_ALL_FN[ROW][COL])){//键被按下，且此键的键值在fn按下后发生了变化
            bleKeyboard.release(LayOut_ALL[ROW][COL]);
            bleKeyboard.press(LayOut_ALL_FN[ROW][COL]);
          }
        }
      }
    }//fn第一次按下结束

    if (start_flag&&(key_press[7][7]==1)&&(fn_stat==1)){ // FN 第一次被松开
      if (DBG_KEYBOARD){
        Serial.println("FN IS OFF !");
      }
      LineDisp("<FN>-------------------------OFF", 1);
      fn_stat = 0;

      for (int ROW = 0; ROW < 8; ROW++){//行循环判断
        for (int COL = 0; COL < 8; COL++){//列循环
          if((old_key_press[ROW][COL]==0)&&(key_press[ROW][COL]==0)&&(LayOut_ALL[ROW][COL]!=LayOut_ALL_FN[ROW][COL])){//键被按下，且此键的键值在fn按下后发生了变化
            bleKeyboard.release(LayOut_ALL_FN[ROW][COL]);
            bleKeyboard.press(LayOut_ALL[ROW][COL]);
          }
        }
      }
    }//fn第一次松开结束

    for (int ROW = 0; ROW < 8; ROW++){//行循环判断
      for (int COL = 0; COL < 8; COL++){//列循环

        //判断键值变化
        if ((!pn_stat)&&start_flag && ( (old_key_press[ROW][COL]!=key_press[ROW][COL]))){
          if (DBG_KEYBOARD){
            Serial.println("***["+ String(ROW) + "," + String(COL) + "]:" + String(key_press[ROW][COL])+ "means:" + String(LayOut_ALL[ROW][COL]) );
          }

          //发送按键
          if (LayOut_ALL[ROW][COL]!=0){
            if (key_press[ROW][COL]==0){//如果低电平则按下
              if (fn_stat){
                bleKeyboard.press(LayOut_ALL_FN[ROW][COL]);
              }
              else{
                bleKeyboard.press(LayOut_ALL[ROW][COL]);
              }
            }
            if(key_press[ROW][COL]==1){//高电平则松开
              if (fn_stat){
                bleKeyboard.release(LayOut_ALL_FN[ROW][COL]);
              }
              else{
                bleKeyboard.release(LayOut_ALL[ROW][COL]);
              }
            }

          }//发送结束

        }//判断键值变化结束

      }//列循环
    }//行循环   
      //新旧赋值
      for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
          old_key_press[i][j] = key_press[i][j];
        }
      }//新旧赋值结束

      if(!start_flag){
        start_flag = 1;
      }



  } //连接上
  else{
    delay(10);//没连接上就等着
  }

        vTaskDelay(4);


}//循环扫描不会结束

}//end bt_work

bool joker_bt_start(){
    Serial.println("bt starting!");
    xReturned_bt = xTaskCreatePinnedToCore(bt_work, "JOKER BT WORK", 9192, 
# 205 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_bt.ino" 3 4
                                                                                   __null
# 205 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\poker_bt.ino"
                                                                                       , 4, &BT_TASK_Handle, 0) ;
    if(xReturned_bt == ( ( ( BaseType_t ) 1 ) )){
        return 1;
    }
    return 0;
}
# 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\scan.ino"
# 2 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v1.0.0\\poker_keyboard\\scan.ino" 2

void scan_start(){
  //初始化输入引脚
  for (int i = 0; i < 8; i++){
    pinMode(key_pin_in[i],0x05);
  }
  //初始化输出引脚
  for (int j = 0; j < 8; j++){
    pinMode(key_pin_out[j],0x02);
    digitalWrite(key_pin_out[j],0x1);
  }
}

void key_scan(){
//扫描
  for (int ROW = 0; ROW < 8; ROW++){
    //写电平
    if (ROW==0){
      digitalWrite(key_pin_out[(8 -1)],0x1); //最后一组写为高，第一组写为低
      digitalWrite(key_pin_out[ROW],0x0);
    }
    else{
      digitalWrite(key_pin_out[(ROW-1)],0x1); //其余的将前一个写为高，自己写低
      digitalWrite(key_pin_out[ROW],0x0);
    }
    delayMicroseconds(10);
    //读取电平
    for (int COL = 0; COL < 8; COL++){
      key_press[ROW][COL] = digitalRead(key_pin_in[COL]);
    }//读取电平结束

  }//扫描结束
}
