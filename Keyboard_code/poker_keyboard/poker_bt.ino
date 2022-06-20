#include "poker_bt.h"
#include "oled_buff.h"
#include "keyboard_self.h"
#include "joker_usb.h"
#include "save.h"

BleKeyboard bleKeyboard(DeviceName, Manufacturer, DevicePower);

void bt_test(){
  int i = 0;
    pinMode(34,INPUT);
    if(DBG_KEYBOARD){
        Serial.println("Starting BLE TEST!");
    }

    bleKeyboard.begin();//Start blekeyboard service
  pinMode(2,OUTPUT);
  //
    for(;;){
    
        if(bleKeyboard.isConnected()&&(!digitalRead(34))) {
            Serial.println("w");
            if(i==0){
              bleKeyboard.press(KEY_W);
              digitalWrite(2,HIGH);
            }
             if(i==1){
               bleKeyboard.releaseAll();
               digitalWrite(2,LOW);
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
          i = (i+1)%2;
  }
    }
  Serial.println("Waiting 5 seconds...");
  delay(5000);
}

/*
蓝牙工作模式
*/
void bt_work(void *pvParameters){
  if(DBG_KEYBOARD){
        Serial.println("Starting BLE work!");
  }
  #ifdef Joker
  LineDisp("-------BLE------", ble_line);
  #endif
  vTaskDelay(1000);
  bleKeyboard.begin();//Start blekeyboard service
  Keyboard_Config.BOOT_MODE = 0;
  save_config();
  #ifdef Joker
  LineDisp("Waiting for BLE", ble_line);
  display.drawString(0, ble_line*8 ,"Waiting for BLE");
  #endif
  bool start_flag = 0;
  
//循环扫描
for (;;){
  if (bleKeyboard.isConnected()){//连接上
    
    bt_stat = 1;

     //第一次先赋值

    if (!start_flag){
      Serial.println("connected!");
      #ifdef Joker
      display.drawString(0, ble_line*8 ,"<MODE>===========BLE");
      display.display();
      //LineDisp(">========BLE========<", ble_line);
      LineDisp("<MODE>===========BLE", ble_line);
      LineDisp("<FN>-------------------------OFF", fn_line);
      #endif
      Keyboard_Config.BOOT_MODE = 1;
      save_config();
    }
    
    //扫描
    key_scan();

    //PN位置
    #ifdef Joker
    //PN按下
    if(pn_stat){//pn被按下
      if ((key_press[LED_ROW][LED_COL]==0)&&(old_key_press[LED_ROW][LED_COL]==1)){ //LED 控制
        if(!LED_STAT){
          open_inter_led();
        }
        else{
          close_inter_led();
        }
      }//LED 控制
      
      //MODE 控制
      if((key_press[MODE_ROW][MODE_COL]==0)&&(old_key_press[MODE_ROW][MODE_COL]==1)){ // 第一次按下
        bt_to_change_mode = 1; 
        bt_chang_mode_time = millis();
        LineDisp("<MODE>===========CHG", ble_line);
      }
      if ((key_press[MODE_ROW][MODE_COL]==0)&&bt_to_change_mode&&((millis()-bt_chang_mode_time)>3000)){//连续按压了三秒以上
        bt_to_change_mode = 0;
        joker_bt2usb();
        LineDisp("<MODE>===========LIS", ble_line);
      }
      if(bt_to_change_mode&&(key_press[MODE_ROW][MODE_COL]==1)){//三秒内放开
        bt_to_change_mode = 0;
        LineDisp("<MODE>===========BLE", ble_line);
      }
      //MODE 控制

      //重置倒计时
      if ((key_press[cnt_rst_ROW][cnt_rst_COL]==0)&&(old_key_press[cnt_rst_ROW][cnt_rst_COL]==1)){ 
        rst_cnt_time = 1;
      }
      //重置倒计时
    }
    //PN第一次按下
    if(start_flag&&(pn_stat==0)&&(key_press[PN_ROW][PN_COL] == 0)){//PN第一次按下
      if (DBG_KEYBOARD){
        Serial.println("PN ON!");
      }
      for (int i = 0; i < 8; i++){
        bleKeyboard.releaseAll();
      }

      pn_stat = 1;
    }//pn第一次按下
    //PN第一次松开
    if(start_flag&&(pn_stat==1)&&(key_press[PN_ROW][PN_COL] == 1)){//PN第一次松开
      if (DBG_KEYBOARD){
        Serial.println("PN OFF!");
      }
      pn_stat = 0;
    }//pn第一次松开
    #endif

    // FN 第一次被按下
    if (start_flag&&(key_press[FN_ROW][FN_COL]==0)&&(fn_stat==0)){ 
      if (DBG_KEYBOARD){
        Serial.println("FN IS ON !");
      }
      #ifdef Joker
      LineDisp("<FN>--------------------------ON", fn_line);
      #endif
      fn_stat = 1;

      for (int ROW = 0; ROW < number_out; ROW++){//行循环判断
        for (int COL = 0; COL < number_in; COL++){//列循环
          if((old_key_press[ROW][COL]==0)&&(key_press[ROW][COL]==0)&&(LayOut_ALL[ROW][COL]!=LayOut_ALL_FN[ROW][COL])){//键被按下，且此键的键值在fn按下后发生了变化
            bleKeyboard.release(LayOut_ALL[ROW][COL]);
            bleKeyboard.press(LayOut_ALL_FN[ROW][COL]);
          }
        }
      }
    }//fn第一次按下结束

    if (start_flag&&(key_press[FN_ROW][FN_COL]==1)&&(fn_stat==1)){ // FN 第一次被松开
      if (DBG_KEYBOARD){
        Serial.println("FN IS OFF !");
      }
      #ifdef Joker
      LineDisp("<FN>-------------------------OFF", fn_line);
      #endif
      fn_stat = 0;

      for (int ROW = 0; ROW < number_out; ROW++){//行循环判断
        for (int COL = 0; COL < number_in; COL++){//列循环
          if((old_key_press[ROW][COL]==0)&&(key_press[ROW][COL]==0)&&(LayOut_ALL[ROW][COL]!=LayOut_ALL_FN[ROW][COL])){//键被按下，且此键的键值在fn按下后发生了变化
            bleKeyboard.release(LayOut_ALL_FN[ROW][COL]);
            bleKeyboard.press(LayOut_ALL[ROW][COL]);
          }
        }
      }
    }//fn第一次松开结束
    
    for (int ROW = 0; ROW < number_out; ROW++){//行循环判断
      for (int COL = 0; COL < number_in; COL++){//列循环
          
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
        for (int i = 0; i < number_out; i++){
            for (int j = 0; j < number_in; j++){
                if (old_key_press[i][j]==key_press[i][j]){
                     old_key_press[i][j] = key_press[i][j]; //如果通过了消抖则赋值
                }
                old_key_press[i][j] = key_press[i][j]; //无论是否消抖都和前一样赋值
            } 
        }//新旧赋值结束

        
      if (!start_flag){
      start_flag = 1;
      for (int i = 0; i < number_out; i++){
            for (int j = 0; j < number_in; j++){
                old_key_press[i][j] = key_press[i][j]; //如果通过了消抖则赋值
                old_key_press[i][j] = key_press[i][j]; //无论是否消抖都和前一样赋值
            } 
        }//新旧赋值结束
    }

  } //连接上
  else{
    delay(10);//没连接上就等着
  }
  #ifdef BT_TASK_DELAY
        vTaskDelay(BT_TASK_DELAY);
        #endif

}//循环扫描不会结束

}//end bt_work

bool joker_bt_start(){
    Serial.println("bt starting!");
    xReturned_bt = xTaskCreatePinnedToCore(bt_work, "JOKER BT WORK", BT_TASK_STACK, NULL, BT_TASK_PRI, &BT_TASK_Handle, BT_TASK_CORE) ; 
    if(xReturned_bt == pdPASS){
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

void joker_bt2usb(){
    Serial.println("CHANGING MODE!");
    Keyboard_Config.BOOT_MODE = 0; 
    save_config();
    ESP.restart();
}
