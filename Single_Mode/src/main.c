#include "Handler.h"

int main()
{
  HC595_Single_Init();

  HC595_Single_ShiftOut(0b00110011, MSBFIRST);

  while (1)
  {

    delay_ms(2500);

    HC595_Single_ProcessCommand("RELAY8 ON");

    delay_ms(2500);

    HC595_Single_ProcessCommand("RELAY5 ON");
      
  }
}