#ifndef POKER_BT_H
#define POKER_BT_H
#include "poker_keyboard.h"
#include "scan.h"

#include "Layout.h"

BaseType_t xReturned_bt;
TaskHandle_t BT_TASK_Handle = NULL;
#define BT_TASK_CORE 0
#define BT_TASK_STACK 9192
#define BT_TASK_PRI 4
#define BT_TASK_DELAY 4

void bt_test();
//void bt_work();
bool joker_bt_start();

bool bt_stat = 0;
bool iw[2] = {0,0};
bool bt_to_change_mode = 0;
int bt_chang_mode_time;


# endif
