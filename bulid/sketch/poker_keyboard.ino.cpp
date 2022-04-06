#include <Arduino.h>
#line 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
#include "poker_keyboard.h"
#include "poker_bt.h"
#include <BleKeyboard.h>
# include <Wire.h>

#line 6 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
void setup();
#line 23 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
void loop();
#line 5 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino"
void bt_test();
#line 47 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino"
void bt_start();
#line 6 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
void setup() {
  Serial.begin(115200);
  Serial.println("Joker setting up!");
  delay(10000);

  //初始化输入引脚
  for (int i = 0; i < number_in; i++){
    pinMode(key_pin_in[i],INPUT_PULLUP);
  }

  //初始化输出引脚
  for (int j = 0; j < number_out; j++){
    pinMode(key_pin_out[j],OUTPUT);
    digitalWrite(key_pin_out[j],HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  bt_start();
  delay(1000);
}

#line 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino"
#include "poker_bt.h"

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

void bt_start(){
  if(DBG_KEYBOARD){
        Serial.println("Starting BLE work!");
  }

  bleKeyboard.begin();//Start blekeyboard service

  
bool start_flag = 0;
//循环扫描
for (;;){
  if (bleKeyboard.isConnected()){
    bt_stat = 1;
    
     //第一次先赋值

    if (!start_flag){
      Serial.println("connected!");
    }
    
      //扫描
      for (int ROW = 0; ROW < number_out; ROW++){
        
        //将j列写为低，其余为高
        for (int i = 0; i < number_out; i++){
          if (i!=ROW){
           digitalWrite(key_pin_out[i], HIGH);
          }
          if (i==ROW){
            digitalWrite(key_pin_out[i], LOW);
          }
        }//写电平结束

        //读取电平
        for (int COL = 0; COL < number_in; COL++){
          key_press[ROW][COL] = digitalRead(key_pin_in[COL]);
          
          //判断键值变化
          if (start_flag & (old_key_press[ROW][COL]!=key_press[ROW][COL]) & (LayOut[ROW][COL]!=0) ){ 
            if (DBG_KEYBOARD){
              Serial.println("***["+ String(ROW) + "," + String(COL) + "]:" + String(key_press[ROW][COL])+ "means:" + String(LayOut[ROW][COL]) );
            }

            //发送按键
            if (key_press[ROW][COL]==0){//如果低电平则按下
              bleKeyboard.press(LayOut[ROW][COL]);
            }
            if(key_press[ROW][COL]==1){//高电平则松开
              bleKeyboard.release(LayOut[ROW][COL]);
            }
            //发送结束  

          }//判断键值变化结束
        
        }//读取结束
        
      }//扫描结束

    //新旧赋值
    for (int i = 0; i < number_out; i++){
      for (int j = 0; j < number_in; j++){
        old_key_press[i][j] = key_press[i][j];
      } 
    }//新旧赋值结束
    
    if(!start_flag){
      start_flag = 1;
    }

  } //一直尝试连接
  delay(10);

}//循环扫描不会结束

}//end bt_start
