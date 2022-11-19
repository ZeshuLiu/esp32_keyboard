# 1 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.ino"
# 2 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.ino" 2
# 3 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.ino" 2

# 5 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.ino" 2
# 6 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.ino" 2
# 7 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.ino" 2
# 8 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.ino" 2
# 9 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.ino" 2
# 10 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.ino" 2
# 11 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.ino" 2
# 12 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.ino" 2
# 13 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_keyboard.ino" 2







void setup() {
  // DBG 设置
  Serial.begin(115200);
  Serial.println("Joker setting up!");
  delay(100);

  //读取保存的数据
  load_config();
  DFT_BOOT_MODE = Keyboard_Config.BOOT_MODE ;
  Serial.println(String(DFT_BOOT_MODE));
  Serial.println(String(Keyboard_Config.Version_KBD));
  // I2c 设置

  Wire.begin(21,22);
  Serial.println("I2C SET!");


  //初始化扫描工作
  scan_start();
  Serial.println("SCAN SET!");

  // 9328USB输出






  // ch9329


  ch9329.begin(16,17,9600);







  delay(100);
  Serial.println("USB SET!");

  //键盘硬件设置
  keyboard_setup();
  Serial.println("Joker setted up!");
  delay(100);
  if(DFT_BOOT_MODE == 0){
    joker_usb_start();
    //joker_usb_work();
  }
  if(DFT_BOOT_MODE == 1){
    joker_bt_start();
  }
  cnt_start();
}

void loop() {
  delay(1000);// put your main code here, to run repeatedly:





}
# 1 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\L_CH932x.ino"
# 2 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\L_CH932x.ino" 2
# 3 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\L_CH932x.ino" 2

bool L_CH9329::begin(uint8_t RX, uint8_t TX, uint16_t Buad_rate){
    Serial2.begin(Buad_rate,0x800001c,RX,TX);
    return 1;
}

void L_CH9329::muice_send(int x_mov,int y_mov,bool l_click, bool r_click, int scroll_move){
    // MOVE xy
    if(x_mov==0){
        muice_move_code[7] = 0x00;
    }
    else if (x_mov>0){
        muice_move_code[7] = x_mov%(0x80);
    }
    else{
       muice_move_code[7] = 0x100 + x_mov%(0x80);
    }

    if(y_mov==0){
        muice_move_code[8] = 0x00;
    }
    else if (y_mov>0){
        muice_move_code[8] = y_mov%(0x80);
    }
    else{
       muice_move_code[8] = 0x100 + y_mov%(0x80);
    }
    //end move xy

    // Move scroll
    if(scroll_move==0){
        muice_move_code[9] = 0x00;
    }
    else if (scroll_move>0){
        muice_move_code[9] = scroll_move%(0x80);
    }
    else{
       muice_move_code[9] = 0x100 + scroll_move%(0x80);
    }
    // end Move scroll

    //Click
    if (l_click){
      muice_move_code[6] = muice_move_code[6] | LEFT_CLICK;
    }
    else{
      muice_move_code[6] = muice_move_code[6] & (~LEFT_CLICK);
    }
    if (r_click){
      muice_move_code[6] = muice_move_code[6] | RIGHT_CLICK;
    }
    else{
      muice_move_code[6] = muice_move_code[6] & (~RIGHT_CLICK);
    }
    // end Click

    // Sum
    muice_move_code[10] = 0x00;
    for (int i = 0; i < 10; i++){
        muice_move_code[10] = (muice_move_code[10]+muice_move_code[i]);
    }
    // end Sum

    Serial2.write(muice_move_code,11);
    Serial.println(muice_move_code[6]);
    //Serial.println(muice_move_code[10]);
}

int8_t L_CH9329::muice_work(int x_enc,int y_enc,bool lc, bool rc){
  int16_t x_m=0, y_m=0;
  int16_t x_left=0, y_left=0;
  if (abs(x_enc) > dead_zone || abs(y_enc)>dead_zone){
      if (abs(x_enc)<600){
        x_m = (x_enc)/80;
        x_left = x_enc%80;
      }
      else if(x_enc>0){
        x_m = (x_enc)/30-13;
        x_left = x_enc%30;
      }
      else{
        x_m = (x_enc)/30+12;
        x_left = x_enc%30;
      }

      if (abs(y_enc)<600){
        y_m = (y_enc)/80;
        y_left = y_enc%80;
      }
      else if(y_enc>0){
        y_m = (y_enc)/30-13;
        y_left = y_enc%30;
      }
      else{
        y_m = (y_enc)/30+12;
        y_left = y_enc%30;
      }


        muice_send(x_m%127,y_m%127,lc,rc);
        //Serial.println(String(x_m));
    }
    else{
        muice_send(0,0,lc,rc);
    }
    return 1+max(abs(x_left),abs(y_left));
}

void L_CH9329::set_dead_zone(uint8_t newzone) {
    dead_zone = newzone;
}

void L_CH9329::general_keyboard_send(uint8_t key_code[8]){
    general_keyboard_code[13] = 0x00;

    for (int i = 0; i < 8; i++){
      general_keyboard_code[i+5] = key_code[i];
    }

    for (int i = 0; i < 13; i++){
        general_keyboard_code[13] = (general_keyboard_code[13]+general_keyboard_code[i]);
    }
    Serial.println(String(key_code[2]));
    Serial2.write(general_keyboard_code,14);
}

void L_CH9329::media_keyboard_change(uint8_t line, uint8_t code, bool ifpress){
    uint8_t pos = 5+line;
    if (ifpress==1){
      media_keyboard_code[pos] = media_keyboard_code[pos]|code;
    }
    else{
      media_keyboard_code[pos] = media_keyboard_code[pos]&(!code);
    }
}

void L_CH9329::media_keyboard_send(){
    media_keyboard_code[9] = 0x00;
    for (int i = 0; i < 9; i++){
        media_keyboard_code[9] = (media_keyboard_code[9]+media_keyboard_code[i]);
    }
    Serial.println(String(media_keyboard_code[2]));
    Serial2.write(media_keyboard_code,10);
}
void L_CH9329::media_keyboard_clear(){
    for (int i = 6; i < 10; i++){
      media_keyboard_code[i] = 0x00;
    }

    for (int i = 0; i < 9; i++){
        media_keyboard_code[9] = (media_keyboard_code[9]+media_keyboard_code[i]);
    }
    Serial.println("clear Media code");
    Serial2.write(media_keyboard_code,10);
}
# 1 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\Seg_disp.ino"
# 2 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\Seg_disp.ino" 2

void init_seg(){
# 15 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\Seg_disp.ino"
}
# 1 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino"
# 2 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino" 2
# 3 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino" 2
# 4 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino" 2
# 5 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino" 2
# 6 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino" 2
# 7 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino" 2
# 8 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino" 2
# 9 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino" 2
# 10 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino" 2
# 11 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino" 2

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
    bool media_send = 0;
    for (int i = 0; i < 8; i++)
    {
        key_code[i] = 0x00;
    }


        //draw_dog();
        delay(200);
        oled_mode = 0;
        LineDisp("<MODE>===========USB", 0,1);
        LineDisp("<FN>----------------------------OFF", 1);
        //display.drawString(0, ble_line*8 ,"<MODE>===========USB");
        //display.display();


    int start_time = micros();
    vTaskDelay(100);

    for (;;){


        key_scan();

        //PN位置

        //PN按下
        if(pn_stat){//pn被按下

            //LED 控制
            if ((key_press[7][0]==0)&&(old_key_press[7][0]==1)){
                if(!LED_STAT){
                    open_inter_led();
                    //draw_dog();
                }
                else{
                    close_inter_led();
                }
            }//LED 控制

            //画dog
            if ((key_press[5][5]==0)&&(old_key_press[5][5]==1)){
                if(oled_mode!=1){
                    oled_mode = 1;
                    draw_dog();
                }
                else{
                    oled_mode = 0;
                }
            }
            //dog结束

            //MODE 控制
            if((key_press[6][1]==0)&&(old_key_press[6][1]==1)){ // 第一次按下
                USB_to_change_mode = 1;
                USB_chang_mode_time = millis();
                LineDisp("<MODE>===========CHG", 0);
            }
            if ((key_press[6][1]==0)&&USB_to_change_mode&&((millis()-USB_chang_mode_time)>3000)){//连续按压了三秒以上
                USB_to_change_mode = 0;
                joker_usb2bt();
                LineDisp("<MODE>===========BTS", 0);
            }
            if(USB_to_change_mode&&(key_press[6][1]==1)){//三秒内放开
                USB_to_change_mode = 0;
                LineDisp("<MODE>===========USB", 0);
            }
            //MODE 控制

            //重置倒计时
            if ((key_press[6][5]==0)&&(old_key_press[6][5]==1)){
                rst_cnt_time = 1;
            }
            //重置倒计时

            //媒体键

            //循环赋值
                for (int ROW = 0; ROW < 8; ROW++){//循环赋值
                    for (int COL = 0; COL < 8; COL++){
                        if (start_flag && (old_key_press[ROW][COL]!=key_press[ROW][COL]) && (if_Media_code[ROW][COL] != 0) ){//键值变化 并且连续两次按下的一样 并且是媒体键
                                Serial.println("Media:"+String(ROW)+","+String(COL)+":"+String(key_press[ROW][COL]));
                                media_send = 1;
                                if(key_press[ROW][COL] == 0){//按下
                                    ch9329.media_keyboard_change(if_Media_code[ROW][COL], Media_code[ROW][COL], 1);
                                }
                                else{//松开
                                    ch9329.media_keyboard_change(if_Media_code[ROW][COL], Media_code[ROW][COL], 0);
                                }
                        }//键值变化结束
                    }//列结束   
                }//行结束
                if(media_send){
                    media_send = 0;
                    ch9329.media_keyboard_send();
                }

            //媒体键

        }
        //PN第一次按下
        if(start_flag&&(pn_stat==0)&&(key_press[0][1] == 0)){//PN第一次按下
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
        if(start_flag&&(pn_stat==1)&&(key_press[0][1] == 1)){//PN第一次松开
            if (DBG_KEYBOARD){
                Serial.println("PN OFF!");
            }
            pn_stat = 0;
            USB_to_change_mode = 0;
            ch9329.media_keyboard_clear();
        }//pn第一次松开


        // FN 第一次被按下
        if (start_flag&&(key_press[0][4]==0)&&(fn_stat==0)){
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
        if (start_flag&&(key_press[0][4]==1)&&(fn_stat==1)){
            if (DBG_KEYBOARD){
                Serial.println("FN IS OFF !");
            }

            LineDisp("<FN>----------------------------OFF", 1);

            fn_stat = 0;

            // 松开fn后将所有键值清零
            usb_send = 1;
            for (int i = 0; i < 8; i++){
                key_code[i] = 0x00;
            }

        }//fn第一次松开结束


        //循环赋值
        for (int ROW = 0; ROW < 8; ROW++){//循环赋值
            for (int COL = 0; COL < 8; COL++){
                if (start_flag && (old_key_press[ROW][COL]!=key_press[ROW][COL]) &&(!pn_stat)){//键值变化且pn没有按下 并且连续两次按下的一样
                        Serial.println(String(ROW)+","+String(COL));
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

       if(!start_flag){
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    old_key_press[i][j] = key_press[i][j]; //如果通过了消抖则赋值
                }
            }//新旧赋值结束
            start_flag = 1;
        }

        //新旧赋值
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                 old_key_press[i][j] = key_press[i][j]; //赋值
            }
        }//新旧赋值结束


        //发送按键
        if (usb_send){






            ch9329.general_keyboard_send(key_code);



            usb_send = 0; //发送后设置为0

            if (DBG_KEYBOARD){
                Serial.println("sending:" + String(key_code[2]));
                Serial.println("Time:" + String(micros()-start_time));

            }
        }
        start_time = micros();




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
    disableCore0WDT();
    xReturned_usb = xTaskCreatePinnedToCore(joker_usb_work, "JOKER USB WORK", 9192, 
# 305 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino" 3 4
                                                                                             __null
# 305 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino"
                                                                                                 , 4, &USB_TASK_Handle, 0) ;
    if(xReturned_usb == ( ( ( BaseType_t ) 1 ) )){
        Serial.println("Usb Started!");
        return 1;
    }
    return 0;
}

/*

void joker_usb2bt(){

    Serial.println("CHANGING MODE!");

    joker_bt_start();

    if(USB_TASK_Handle!=NULL){

        USB_TASK_Handle = NULL;

        Serial.println("USB TASK DELETE");

        vTaskDelete(USB_TASK_Handle);

    }

}

*/
# 325 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\joker_usb.ino"
void joker_usb2bt(){
    Keyboard_Config.BOOT_MODE = 1;
    save_config();
    ESP.restart();
}
# 1 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\keyboard_self.ino"
# 2 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\keyboard_self.ino" 2
# 3 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\keyboard_self.ino" 2
# 4 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\keyboard_self.ino" 2
# 5 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\keyboard_self.ino" 2
# 6 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\keyboard_self.ino" 2


void keyboard_setup(){
  //Joker SETUP

    //Flash LED
    pinMode(15,0x02);
    open_inter_led();
    delay(100);
    close_inter_led();

    //OLED Display
    Oled_Start();
    invert_disp(1);
    LineDisp("      Joker 60 by LiuZS      ",3);
    LineDisp("====Started!====",0);
    //LineDisp("                              1.0",4);
    invert_disp(0);
    delay(100);
    LineDisp(" ",3,1);
    delay(100);


  //Master Yoda SETUP




}

void open_inter_led(){




  digitalWrite(15,0x0);

  LED_STAT = 1;
}
void close_inter_led(){




  digitalWrite(15,0x1);

  LED_STAT = 0;
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
# 85 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\keyboard_self.ino" 3 4
                                                                                     __null
# 85 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\keyboard_self.ino"
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
# 1 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\oled_buff.ino"
# 2 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\oled_buff.ino" 2

# 4 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\oled_buff.ino" 2
# 5 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\oled_buff.ino" 2


void Oled_Start(void){ // 开启oled显示
  display.init();
  display.flipScreenVertically();
  display.setBrightness(127);
  Serial.println("Oled Up!");
  display.clear();
  delay(150);
}

void LineDisp(String to_print,int line, bool if_clear){

    if (if_clear){
        display.clear();
        for(int i=0; i<6; i++){
            Line_Buff[i] = "";
        }
    }
    Line_Buff[line] = to_print;

    if(oled_mode == 0){
        display.clear();

        for(int i=0; i<6; i++){
            display.drawString(0, 9*i ,Line_Buff[i]);
        }
        display.display();
    }

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

void draw_dog(){

    if (oled_mode==1){
        display.clear(); //for Clearing the display
        display.drawXbm(0, 0, 128, 64, dog_bmp);
        display.display();
    }

}
# 1 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\pcf8575.ino"
# 2 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\pcf8575.ino" 2

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
# 1 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_bt.ino"
# 2 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_bt.ino" 2
# 3 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_bt.ino" 2
# 4 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_bt.ino" 2
# 5 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_bt.ino" 2
# 6 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_bt.ino" 2

BleKeyboard bleKeyboard("Joker_60" /*设备名*/, "Liu" /*设备制造商*/, 100 /*电量*/);

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
# 44 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_bt.ino"
          i = (i+1)%2;
  }
    }
  Serial.println("Waiting 5 seconds...");
  delay(5000);
}

/*

蓝牙工作模式

*/
# 54 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_bt.ino"
void bt_work(void *pvParameters){
  if(DBG_KEYBOARD){
        Serial.println("Starting BLE work!");
  }

  LineDisp("-------BLE------", 0);

  vTaskDelay(1000);
  bleKeyboard.begin();//Start blekeyboard service
  Keyboard_Config.BOOT_MODE = 0;
  save_config();

  LineDisp("Waiting for BLE", 0);
  //display.drawString(0, ble_line*8 ,"Waiting for BLE");

  bool start_flag = 0;

//循环扫描
for (;;){
  if (bleKeyboard.isConnected()){//连接上

    bt_stat = 1;

     //第一次先赋值

    if (!start_flag){
      Serial.println("connected!");

      //display.drawString(0, ble_line*8 ,"<MODE>===========BLE");
      //display.display();
      //LineDisp(">========BLE========<", ble_line);
      LineDisp("<MODE>===========BLE", 0);
      LineDisp("<FN>-------------------------OFF", 1);

      Keyboard_Config.BOOT_MODE = 1;
      save_config();
    }

    //扫描
    key_scan();

    //PN位置

    //PN按下
    if(pn_stat){//pn被按下
      if ((key_press[7][0]==0)&&(old_key_press[7][0]==1)){ //LED 控制
        if(!LED_STAT){
          open_inter_led();
        }
        else{
          close_inter_led();
        }
      }//LED 控制

      //MODE 控制
      if((key_press[6][1]==0)&&(old_key_press[6][1]==1)){ // 第一次按下
        bt_to_change_mode = 1;
        bt_chang_mode_time = millis();
        LineDisp("<MODE>===========CHG", 0);
      }
      if ((key_press[6][1]==0)&&bt_to_change_mode&&((millis()-bt_chang_mode_time)>3000)){//连续按压了三秒以上
        bt_to_change_mode = 0;
        joker_bt2usb();
        LineDisp("<MODE>===========LIS", 0);
      }
      if(bt_to_change_mode&&(key_press[6][1]==1)){//三秒内放开
        bt_to_change_mode = 0;
        LineDisp("<MODE>===========BLE", 0);
      }
      //MODE 控制

      //重置倒计时
      if ((key_press[6][5]==0)&&(old_key_press[6][5]==1)){
        rst_cnt_time = 1;
      }
      //重置倒计时
    }
    //PN第一次按下
    if(start_flag&&(pn_stat==0)&&(key_press[0][1] == 0)){//PN第一次按下
      if (DBG_KEYBOARD){
        Serial.println("PN ON!");
      }
      for (int i = 0; i < 8; i++){
        bleKeyboard.releaseAll();
      }

      pn_stat = 1;
    }//pn第一次按下
    //PN第一次松开
    if(start_flag&&(pn_stat==1)&&(key_press[0][1] == 1)){//PN第一次松开
      if (DBG_KEYBOARD){
        Serial.println("PN OFF!");
      }
      pn_stat = 0;
    }//pn第一次松开


    // FN 第一次被按下
    if (start_flag&&(key_press[0][4]==0)&&(fn_stat==0)){
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

    if (start_flag&&(key_press[0][4]==1)&&(fn_stat==1)){ // FN 第一次被松开
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
                if (old_key_press[i][j]==key_press[i][j]){
                     old_key_press[i][j] = key_press[i][j]; //如果通过了消抖则赋值
                }
                old_key_press[i][j] = key_press[i][j]; //无论是否消抖都和前一样赋值
            }
        }//新旧赋值结束


      if (!start_flag){
      start_flag = 1;
      for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                old_key_press[i][j] = key_press[i][j]; //如果通过了消抖则赋值
                old_key_press[i][j] = key_press[i][j]; //无论是否消抖都和前一样赋值
            }
        }//新旧赋值结束
    }

  } //连接上
  else{
    vTaskDelay(4);//没连接上就等着
  }

        vTaskDelay(4);


}//循环扫描不会结束

}//end bt_work

bool joker_bt_start(){
    Serial.println("bt starting!");
    disableCore0WDT();
    xReturned_bt = xTaskCreatePinnedToCore(bt_work, "JOKER BT WORK", 9192, 
# 261 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_bt.ino" 3 4
                                                                                   __null
# 261 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_bt.ino"
                                                                                       , 4, &BT_TASK_Handle, 0) ;
    if(xReturned_bt == ( ( ( BaseType_t ) 1 ) )){
        return 1;
    }
    return 0;
}

/*

void joker_bt2usb(){

    Serial.println("CHANGING MODE!");

    bleKeyboard.end();

    joker_usb_start();

    if(BT_TASK_Handle!=NULL){

        BT_TASK_Handle = NULL;

        Serial.println("BT TASK DELETE");

        vTaskDelete(BT_TASK_Handle);

    }

}

*/
# 281 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\poker_bt.ino"
void joker_bt2usb(){
    Serial.println("CHANGING MODE!");
    Keyboard_Config.BOOT_MODE = 0;
    save_config();
    ESP.restart();
}
# 1 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\save.ino"
# 2 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\save.ino" 2
# 3 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\save.ino" 2

void save_config()
{
    EEPROM.begin(1024);
    uint8_t *p = (uint8_t *)(&Keyboard_Config);
    for (int i = 0; i < sizeof(Keyboard_Config); i++)
    {
        EEPROM.write(i, *(p + i));
    }
    EEPROM.end();
}

void load_config()
{
    EEPROM.begin(1024);
    uint8_t *p = (uint8_t *)(&Keyboard_Config);
    for (int i = 0; i < sizeof(Keyboard_Config); i++)
    {
        *(p + i) = EEPROM.read(i);
    }
    EEPROM.end();

    if (Keyboard_Config.Version_KBD != 1)
    {
        Serial.println("initing");
        Keyboard_Config.BOOT_MODE = DEFAULT_BOOT_MODE ;
        Keyboard_Config.Version_KBD = 1;
        save_config();
    }
}
# 1 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\scan.ino"
# 2 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\scan.ino" 2

void scan_start()
{
  //初始化输入引脚
  for (int i = 0; i < 8; i++)
  {
    pinMode(key_pin_in[i], 0x05);
  }
  //初始化输出引脚
  for (int j = 0; j < 8; j++)
  {
    pinMode(key_pin_out[j], 0x02);
    digitalWrite(key_pin_out[j], 0x1);
  }
}


/*

功能：单次扫描

传参：无

返回：无

*/
# 24 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\scan.ino"
void key_scan_once(){
  //扫描
  for (int ROW = 0; ROW < 8; ROW++)
  {
    //写电平
    if (ROW == 0)
    {
      digitalWrite(key_pin_out[(8 - 1)], 0x1); //最后一组写为高，第一组写为低
      digitalWrite(key_pin_out[ROW], 0x0);
    }
    else
    {
      digitalWrite(key_pin_out[(ROW - 1)], 0x1); //其余的将前一个写为高，自己写低
      digitalWrite(key_pin_out[ROW], 0x0);
    }
    delayMicroseconds(10);
    //读取电平
    for (int COL = 0; COL < 8; COL++)
    {
      key_press[ROW][COL] += digitalRead(key_pin_in[COL]);
    } //读取电平结束

  } //扫描结束
}

/*

功能：应用于键盘时的扫描，带有多次扫描后平均功能

传参：无

返回：无

*/
# 54 "f:\\Data\\开发\\esp32_keyboard\\Keyboard_code\\poker_keyboard\\scan.ino"
void key_scan(){
  int8_t scan_times = 10;
  //清零
  for (int ROW = 0; ROW < 8; ROW++){
    for (int COL = 0; COL < 8; COL++){
      key_press[ROW][COL] = 0;
    }
  }

  //扫描
  for (int i=0; i<scan_times; i++){ //扫描scan_times次
    key_scan_once();
  } //扫描结束

  //滤波
  for (int ROW = 0; ROW < 8; ROW++){
    for (int COL = 0; COL < 8; COL++){
      key_press[ROW][COL] = key_press[ROW][COL]/(scan_times-1); // >= 4次才改变
    }
  }//滤波结束

}
