#ifndef __SERIAL_KEYBOARD_H
#define __SERIAL_KEYBOARD_H

#include "common.h"

void SKEY_Init(void);
uint8_t SKEY_ReceiveChar(void);

#endif