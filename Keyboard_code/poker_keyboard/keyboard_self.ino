# include "keyboard_self.h"
# include "poker_keyboard.h"
# include "oled_buff.h"
# include "Layout.h"
# include "Seg_disp.h"


void keyboard_setup(){
  //Joker SETUP
  #ifdef Joker
  //Flash LED
  pinMode(LED_PIN,OUTPUT);
  open_inter_led();
  delay(100);
  close_inter_led();
  
  //OLED Display
  Oled_Start();
  invert_disp(1);
  LineDisp("      Joker 60 by LiuZS      ",3);
  LineDisp("====Started!====",0);
  //LineDisp("                              1.0",4);
  delay(200);
  invert_disp(0);
  LineDisp(" ",3);
  #endif

  //Master Yoda SETUP
  #ifdef MasterYoda
  //INIT DISP
  init_seg();
  #endif
}

void open_inter_led(){
  digitalWrite(LED_PIN,HIGH);
  LED_STAT = 1;
}
void close_inter_led(){
  digitalWrite(LED_PIN,LOW);
  LED_STAT = 0;
}

void cnt_work(void *pvParameters){
  #ifdef Joker
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
  #endif
}

bool cnt_start(){
  #ifdef Joker
  xReturned_cnt = xTaskCreatePinnedToCore(cnt_work, "JOKER CNT WORK", CNT_TASK_STACK, NULL, CNT_TASK_PRI, &CNT_TASK_Handle, CNT_TASK_CORE) ; 
  if(xReturned_cnt == pdPASS){
    return 1;
  }
  return 0;
  #endif
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


