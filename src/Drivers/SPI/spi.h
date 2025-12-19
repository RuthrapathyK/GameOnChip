#ifndef __SPI_H
#define __SPI_H

#include "common.h"

void SPI_Init(void);
void SPI_Send(uint16_t *tx_buf, uint32_t len);
void SPI_Receive(uint16_t *rx_buf, uint32_t len);
void SPI_Transaction(uint16_t *tx_buf, uint16_t *rx_buf, uint32_t len);

#endif