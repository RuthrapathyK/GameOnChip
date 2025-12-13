#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "common.h"

typedef enum{
    Disp_pinLow,
    Disp_pinHigh,
    Disp_Max
}Disp_PinState_e;

typedef enum{
    Disp_enableCommand,
    Disp_enableData,
    Disp_enableMax
}Disp_cmdData_e;

void Disp_Init(void);
void Disp_Run(void);
void Disp_readReg(uint8_t cmd, uint16_t *rx_buf, uint8_t rx_bitLen);
void Disp_changeFrame_len(uint8_t frameBits);

#endif