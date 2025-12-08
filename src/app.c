#include "spi.h"
#include "gpio.h"
#include "pinconfig.h"

uint16_t tx_buffer[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
uint16_t rx_buffer[sizeof(tx_buffer) / sizeof(tx_buffer[0])];

void Task_A(void)
{
  SPI_Init();

  while(1)
  {
    SPI_Transaction(tx_buffer, rx_buffer, sizeof(tx_buffer) / sizeof(tx_buffer[0]));
  }
}
