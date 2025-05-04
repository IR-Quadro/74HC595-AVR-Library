#include "Handler.h"

// Status of each relay (0: OFF, 1: ON)
uint8_t relayStatus_Single[8] = {0};


/* =============================================================================
 *                              74HC595 - Single Mode
 * =============================================================================
 */

/**
 * @brief Initialize 74HC595 shift register pins in single mode.
 */
void HC595_Single_Init(void)
{
    GPIO_Config_OUTPUT(__clock_Config_Single, __clock_Pin_Single);   
    GPIO_Config_OUTPUT(__latch_Config_Single, __latch_Pin_Single);
    GPIO_Config_OUTPUT(__data_Config_Single, __data_Pin_Single);
}


/**
 * @brief Shift out 8-bit data to 74HC595.
 * 
 * @param value  8-bit data to send.
 * @param order  Bit order: MSBFIRST or LSBFIRST.
 */
void HC595_Single_ShiftOut(uint8_t value, bool order)
{
    for (int i = 0; i < 8; i++)
    {
        // Clear data pin
        __data_Control_Single &= ~(1 << __data_Pin_Single);

        // Write data bit based on bit order
        if (order == LSBFIRST)
        {
            __data_Control_Single |= ((value & 1) << __data_Pin_Single);
            value >>= 1;
        }
        else
        {
            __data_Control_Single |= (((value & 0x80) >> 7) << __data_Pin_Single);
            value <<= 1;
        }

        // Clock pulse
        bitSet(__Clock_Control_Single, __clock_Pin_Single);
        _delay_us(50);
        bitClear(__Clock_Control_Single, __clock_Pin_Single);
    }

    // Latch the shifted data
    bitClear(__latch_Control_Single, __latch_Pin_Single);
    bitSet(__latch_Control_Single, __latch_Pin_Single);
}


/**
 * @brief Update all relay outputs based on current relayStatus_Single values.
 */
void HC595_Single_UpdateRelay(void)
{
    uint8_t output = 0;

    for (int i = 0; i < 8; i++)
    {
        output |= (relayStatus_Single[i] << i);
    }

    HC595_Single_ShiftOut(output, MSBFIRST);
}


/**
 * @brief Process incoming command to turn a relay ON or OFF.
 * 
 * @param command Example: "RELAY1 ON", "RELAY3 OFF"
 */
void HC595_Single_ProcessCommand(char* command)
{
    int relayNumber = command[5] - '1';  // Convert '1' to index 0

    if (command[7] == 'O' && command[8] == 'N')
    {
        relayStatus_Single[relayNumber] = 1;
    }
    else if (command[7] == 'O' && command[8] == 'F' && command[9] == 'F')
    {
        relayStatus_Single[relayNumber] = 0;
    }

    HC595_Single_UpdateRelay();
}
