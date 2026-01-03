#include "../src/Drivers/PinMux/pinconfig.h"
#include "../src/Drivers/UART/uart.h"
#include "keyboard.h"

void SKEY_Init(void)
{
    /* Configure UART with Baudrate */
    UART_Init(115200);

    /* Configure the Serial Keyboard Pins */  
    Pin_Config(Port_PA, 0, PA0_U0RX);
    Pin_Config(Port_PA, 1, PA1_U0TX);  
}

uint8_t SKEY_ReceiveChar(void)
{
    return UART_receiveChar();
}
