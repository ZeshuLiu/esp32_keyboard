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
      for (int ROW = 0; ROW < number_out; ROW++){
        
        //写电平：将j列写为低，其余为高
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

}//end bt_work