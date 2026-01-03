#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "common.h"

typedef struct{
    uint16_t Pixel_Blue;
    uint16_t Pixel_Green;
    uint16_t Pixel_Red;
}DISP_Pixel_type;

#define DISP_RESOLUTION_COLUMN 240
#define DISP_RESOLUTION_ROW 320

void DISP_Init(void);
void DISP_setPixel_Pointer(uint16_t cur_col_addr, uint16_t cur_pg_addr, uint16_t max_col_addr, uint16_t max_pg_addr);
void DISP_sendPixels(uint32_t pixelVal, uint32_t col_start, uint32_t pg_start, uint32_t length);

#endif