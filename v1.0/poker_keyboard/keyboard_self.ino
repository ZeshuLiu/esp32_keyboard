# include "keyboard_self.h"
# include "poker_keyboard.h"
# include "pcf8575.h"
# include "oled_buff.h"


void keyboard_setup(){
  //初始化io扩展
  //pcf8575_begin();
  pinMode(LED_PIN,OUTPUT);
  open_inter_led();
  invert_disp(1);
  delay(1000);
  close_inter_led();
  invert_disp(0);
}

void open_inter_led(){
  digitalWrite(LED_PIN,HIGH);
  LED_STAT = 1;
}
void close_inter_led(){
  digitalWrite(LED_PIN,LOW);
  LED_STAT = 0;
}

void open_i2c_keyboard_led(){
    if ((write_low&LED_PIN)!=0){//高电平
      write_low = write_low&(~LED_PIN);
      pcf8575_writeAll(word(B11111111,write_low));
    }
    Serial.println("LED ON");
    LED_STAT = 1;
}

void close_i2c_keyboard_led(){
    write_low = write_low|LED_PIN;
    pcf8575_writeAll(word(B11111111,write_low));
    Serial.println("LED OFF");
    LED_STAT = 0;
}

void open_i2c_caps_led(){
    if ((write_low&CAP_LED_PIN)!=0){//高电平
      write_low = write_low&(~CAP_LED_PIN);
      pcf8575_writeAll(word(B11111111,write_low));
    }
    Serial.println("CAP ON");
    CAP_LED_STAT = 1;
}

void close_i2c_caps_led(){
    write_low = write_low|CAP_LED_PIN;
    pcf8575_writeAll(word(B11111111,write_low));
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
  xReturned_cnt = xTaskCreatePinnedToCore(cnt_work, "JOKER CNT WORK", CNT_TASK_STACK, NULL, CNT_TASK_PRI, &CNT_TASK_Handle, CNT_TASK_CORE) ; 
  if(xReturned_cnt == pdPASS){
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


