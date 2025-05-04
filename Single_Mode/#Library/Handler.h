#ifndef _Handler_H_
#define _Handler_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "74HC595_Single.h"

//#include "Timer0.h"
//#include "Timer1.h"
//#include "aLCD.h"
//#include "EXTinterrupt.h"
//#include "UART.h"

#define bitSet(Reg, Bit) (Reg |= (1<<Bit))
#define bitClear(Reg, Bit) (Reg &= ~(1<<Bit))
#define bitToggle(Reg, Bit) (Reg ^= 1<<Bit)
#define bitCheck(Reg, Bit) ((Reg>>Bit) & 0x01)
#define bitChange(Reg, Bit, Value) (Value == 1 ? bitSet(Reg, Bit) : bitClear(Reg, Bit))

#define delay_ms(delay_msValue) _delay_ms(delay_msValue)

#define GPIO_Config_OUTPUT(Reg, Bit) bitSet(Reg, Bit)
#define GPIO_Config_INPUT(Reg, Bit) bitClear(Reg, Bit)

#define GlobalInt_Enable   bitSet(SREG, SREG_I)
#define GlobalInt_Disable  bitClear(SREG, SREG_I)

#define intFlag_Clear(Reg, Bit) bitSet(Reg, Bit)

#define Initialize true
#define deInitialize false


#endif