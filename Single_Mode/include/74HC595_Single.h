#ifndef _74HC595_Single_H_
#define _74HC595_Single_H_

#include "Handler.h"

#define LSBFIRST true
#define MSBFIRST false

#define __clock_Config_Single    DDRD
#define __Clock_Control_Single   PORTD
#define __clock_Pin_Single       0  

#define __data_Config_Single     DDRD
#define __data_Control_Single    PORTD
#define __data_Pin_Single        1  

#define __latch_Config_Single    DDRD
#define __latch_Control_Single   PORTD
#define __latch_Pin_Single       2  


void HC595_Single_Init();
void HC595_Single_ShiftOut(uint8_t value, bool Order);
void HC595_Single_ProcessCommand(char* command);
void HC595_Single_UpdateRelay();


#endif