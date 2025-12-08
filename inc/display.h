#ifndef __DISPLAY_H
#define __DISPLAY_H

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

#endif