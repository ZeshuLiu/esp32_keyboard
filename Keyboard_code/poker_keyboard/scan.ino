#include "scan.h"

void scan_start()
{
  //初始化输入引脚
  for (int i = 0; i < number_in; i++)
  {
    pinMode(key_pin_in[i], INPUT_PULLUP);
  }
  //初始化输出引脚
  for (int j = 0; j < number_out; j++)
  {
    pinMode(key_pin_out[j], OUTPUT);
    digitalWrite(key_pin_out[j], HIGH);
  }
}


/*
功能：单次扫描
传参：无
返回：无
*/
void key_scan_once(){
  //扫描
  for (int ROW = 0; ROW < number_out; ROW++)
  {
    //写电平
    if (ROW == 0)
    {
      digitalWrite(key_pin_out[(number_out - 1)], HIGH); //最后一组写为高，第一组写为低
      digitalWrite(key_pin_out[ROW], LOW);
    }
    else
    {
      digitalWrite(key_pin_out[(ROW - 1)], HIGH); //其余的将前一个写为高，自己写低
      digitalWrite(key_pin_out[ROW], LOW);
    }
    delayMicroseconds(10);
    //读取电平
    for (int COL = 0; COL < number_in; COL++)
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
void key_scan(){
  int8_t scan_times = 10;
  //清零
  for (int ROW = 0; ROW < number_out; ROW++){
    for (int COL = 0; COL < number_in; COL++){
      key_press[ROW][COL] = 0;
    } 
  } 

  //扫描
  for (int i=0; i<scan_times; i++){ //扫描scan_times次
    key_scan_once();
  } //扫描结束

  //滤波
  for (int ROW = 0; ROW < number_out; ROW++){
    for (int COL = 0; COL < number_in; COL++){
      key_press[ROW][COL] =  key_press[ROW][COL]/(scan_times-1); // >= 4次才改变
    } 
  }//滤波结束
  
}