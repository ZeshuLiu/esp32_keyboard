#include "joker_usb.h"
#include "scan.h"
#include "oled_buff.h"
#include "keyboard_self.h"
#include "poker_bt.h"
#include "save.h"
#include "esp32-hal.h"
#include "Layout.h"


void joker_usb_test(){
    if (key_code[2] == 0x00){
        key_code[2] = KEY_USB_A;
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

    #ifdef Joker
        //draw_dog();
        delay(200);
        oled_mode = 0;
        LineDisp("<MODE>===========USB", ble_line,1);
        LineDisp("<FN>----------------------------OFF", fn_line);
        //display.drawString(0, ble_line*8 ,"<MODE>===========USB");
        //display.display();
    #endif

    int start_time = micros();
    vTaskDelay(100);
    
    for (;;){
        

        key_scan();

        //PN位置
        #ifdef Joker
        //PN按下
        if(pn_stat){//pn被按下
            if ((key_press[LED_ROW][LED_COL]==0)&&(old_key_press[LED_ROW][LED_COL]==1)){ //LED 控制
                if(!LED_STAT){
                    open_inter_led();
                    //draw_dog();
                }
                else{
                    close_inter_led();
                }
            }//LED 控制

            //画dog
            if ((key_press[DOG_ROW][DOG_COL]==0)&&(old_key_press[DOG_ROW][DOG_COL]==1)){ 
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
            if((key_press[MODE_ROW][MODE_COL]==0)&&(old_key_press[MODE_ROW][MODE_COL]==1)){ // 第一次按下
                USB_to_change_mode = 1; 
                USB_chang_mode_time = millis();
                LineDisp("<MODE>===========CHG", ble_line);
            }
            if ((key_press[MODE_ROW][MODE_COL]==0)&&USB_to_change_mode&&((millis()-USB_chang_mode_time)>3000)){//连续按压了三秒以上
                USB_to_change_mode = 0;
                joker_usb2bt();
                LineDisp("<MODE>===========BTS", ble_line);
            }
            if(USB_to_change_mode&&(key_press[MODE_ROW][MODE_COL]==1)){//三秒内放开
                USB_to_change_mode = 0;
                LineDisp("<MODE>===========USB", ble_line);
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
                key_code[i] = 0x00;
            }
            usb_send = 1;

            pn_stat = 1;
        }//pn第一次按下
        //PN第一次松开
        if(start_flag&&(pn_stat==1)&&(key_press[PN_ROW][PN_COL] == 1)){//PN第一次松开
            if (DBG_KEYBOARD){
                Serial.println("PN OFF!");
            }
            pn_stat = 0;
            USB_to_change_mode = 0;
        }//pn第一次松开
        #endif

        // FN 第一次被按下
        if (start_flag&&(key_press[FN_ROW][FN_COL]==0)&&(fn_stat==0)){ 
            if (DBG_KEYBOARD){
            Serial.println("FN IS ON !");
            }
            #ifdef Joker
            LineDisp("<FN>-----------------------------ON", fn_line);
            #endif
            fn_stat = 1;
            for (int ROW = 0; ROW < number_out; ROW++){//行循环判断
                for (int COL = 0; COL < number_in; COL++){//列循环
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
        if (start_flag&&(key_press[FN_ROW][FN_COL]==1)&&(fn_stat==1)){ 
            if (DBG_KEYBOARD){
                Serial.println("FN IS OFF !");
            }
            #ifdef Joker
            LineDisp("<FN>----------------------------OFF", fn_line);
            #endif
            fn_stat = 0;

            /*
            for (int ROW = 0; ROW < number_out; ROW++){//行循环判断
                for (int COL = 0; COL < number_in; COL++){//列循环
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
            */

            /*for (int ROW = 0; ROW < number_out; ROW++){//行循环判断
                for (int COL = 0; COL < number_in; COL++){//列循环
                    if((old_key_press[ROW][COL]==0)&&(key_press[ROW][COL]==0)&&(USB_LayOut_ALL[ROW][COL]!=USB_LayOut_ALL_FN[ROW][COL])){//键被按下，且此键的键值在fn按下后发生了变化
                        usb_send = 1;
                        if(USB_LayOut_ALL[ROW][COL]!=USB_LayOut_words[ROW][COL]){//是第一位的键值
                                key_code[0] = key_code[0]&(!USB_LayOut_ALL[ROW][COL]);
                        }//是第一位的键值

                        else{//是正常的键值
                            words_change(USB_LayOut_words_FN[ROW][COL],1); //松开是fn的键值
                        }//是正常的键值
                    }//松开fn改变键值结束
                }
            }//行循环判断
            */
           
            // 松开fn后将所有键值清零
            usb_send = 1;
            for (int i = 0; i < 8; i++){
                key_code[i] = 0x00;
            }

        }//fn第一次松开结束
        

        //循环赋值
        for (int ROW = 0; ROW < number_out; ROW++){//循环赋值
            for (int COL = 0; COL < number_in; COL++){
                if (start_flag && (old_key_press[ROW][COL]!=key_press[ROW][COL]) &&(!pn_stat)){//键值变化且pn没有按下 并且连续两次按下的一样
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
            for (int i = 0; i < number_out; i++){
                for (int j = 0; j < number_in; j++){
                    old_key_press[i][j] = key_press[i][j]; //如果通过了消抖则赋值
                } 
            }//新旧赋值结束
            start_flag = 1;
        }
        
        //新旧赋值
        for (int i = 0; i < number_out; i++){
            for (int j = 0; j < number_in; j++){
                 old_key_press[i][j] = key_press[i][j]; //赋值
            } 
        }//新旧赋值结束

        
        //发送按键
        if (usb_send){
            Serial2.write(key_code,8);
            usb_send = 0; //发送后设置为0

            if (DBG_KEYBOARD){
                Serial.println("sending:" + String(key_code[0]));
                Serial.println("Time:" + String(micros()-start_time));
                
            } 
        }
        start_time = micros();
        #ifdef USB_TASK_DELAY
        vTaskDelay(USB_TASK_DELAY);
        #endif
        
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
    xReturned_usb = xTaskCreatePinnedToCore(joker_usb_work, "JOKER USB WORK", USB_TASK_STACK, NULL, USB_TASK_PRI, &USB_TASK_Handle, USB_TASK_CORE) ; 
    if(xReturned_usb == pdPASS){
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

void joker_usb2bt(){
    Keyboard_Config.BOOT_MODE = 1;
    save_config();
    ESP.restart();
}
