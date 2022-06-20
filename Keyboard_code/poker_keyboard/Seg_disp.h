#ifndef SEG_DISP_H
#define SEG_DISP_H
#include "TM1637.h"
#include "Layout.h"

#ifdef MasterYoda
#define CLK 22
#define DIO 21
TM1637 tm1637(CLK, DIO); 
void init_seg();

#endif
#endif