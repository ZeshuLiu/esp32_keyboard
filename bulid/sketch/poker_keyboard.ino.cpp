#line 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
# include "poker_keyboard.h"
# include "poker_bt.h"
# include <BleKeyboard.h>
# include <Wire.h>
# include "keyboard_self.h"
# include <Arduino.h>
# include "pcf8575.h"


#line 10 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
void setup();
#line 32 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
void loop();
#line 6 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\keyboard_self.ino"
void keyboard_setup();
#line 11 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\keyboard_self.ino"
void open_keyboard_led();
#line 20 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\keyboard_self.ino"
void close_keyboard_led();
#line 27 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\keyboard_self.ino"
void open_caps_led();
#line 36 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\keyboard_self.ino"
void close_caps_led();
#line 44 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\keyboard_self.ino"
void keyboard_device_test();
#line 3 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\pcf8575.ino"
void pcf8575_begin();
#line 7 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\pcf8575.ino"
void pcf8575_writeAll(uint16_t data);
#line 14 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\pcf8575.ino"
void pcf8575_readAll();
#line 5 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino"
void bt_test();
#line 47 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_bt.ino"
void bt_work();
#line 10 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\poker_keyboard.ino"
void setup() {
  Serial.begin(115200);
  Serial.println("Joker setting up!");
  delay(1000);
  Wire.begin(21,22);

  //初始化输入引脚
  for (int i = 0; i < number_in; i++){
    pinMode(key_pin_in[i],INPUT_PULLUP);
  }

  //初始化输出引脚
  for (int j = 0; j < number_out; j++){
    pinMode(key_pin_out[j],OUTPUT);
    digitalWrite(key_pin_out[j],HIGH);
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

#line 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\keyboard_self.ino"
# include "keyboard_self.h"
# include "poker_keyboard.h"
# include "pcf8575.h"


void keyboard_setup(){
  //初始化io扩展
  pcf8575_begin();
}

void open_keyboard_led(){
    if ((write_low&LED_PIN)!=0){//高电平
      write_low = write_low&(~LED_PIN);
      pcf8575_writeAll(word(B11111111,write_low));
    }
    Serial.println("LED ON");
    LED_STAT = 1;
}

void close_keyboard_led(){
    write_low = write_low|LED_PIN;
    pcf8575_writeAll(word(B11111111,write_low));
    Serial.println("LED OFF");
    LED_STAT = 0;
}

void open_caps_led(){
    if ((write_low&CAP_LED_PIN)!=0){//高电平
      write_low = write_low&(~CAP_LED_PIN);
      pcf8575_writeAll(word(B11111111,write_low));
    }
    Serial.println("CAP ON");
    CAP_LED_STAT = 1;
}

void close_caps_led(){
    write_low = write_low|CAP_LED_PIN;
    pcf8575_writeAll(word(B11111111,write_low));
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
#line 1 "c:\\Users\\LiuZeshu\\Desktop\\esp32_keyboard\\v0.0.0\\poker_keyboard\\pcf8575.ino"
#include "pcf8575.h"

void pcf8575_begin(){
    pcf8575_writeAll(word(B11111111,B11111111));
}

void pcf8575_writeAll(uint16_t data) {
  Wire.beginTransmission(pcf_address);
  Wire.write(lowByte(data));
  Wire.write(highByte(data));
  Wire.endTransmission();
}

void pcf8575_readAll() {
    Wire.requestFrom(pcf_address, 16);    // Request 8 bytes from slave device number two
    // Slave may send less than requested
	byte b1 = Wire.read();
	byte b2 = Wire.read();

    if (DBG_KEYBOARD){
        Serial.println("..");
        Serial.println(b1);
	    Serial.println(b2);
    }
    
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
