#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "common.h"

typedef struct{
    uint16_t Pixel_Blue;
    uint16_t Pixel_Green;
    uint16_t Pixel_Red;
}Disp_Pixel_type;

void Disp_Init(void);
void Disp_Run(void);
void Disp_setPixel_Pointer(uint16_t cur_col_addr, uint16_t cur_pg_addr, uint16_t max_col_addr, uint16_t max_pg_addr);

#endif