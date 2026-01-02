#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <stdint.h>

#define PIXELTABLE_RESOLUTION_COULUMN 50
#define PIXELTABLE_RESOLUTION_ROW 50

void Disp_sendPixels(uint32_t pixelVal, uint32_t col_start, uint32_t pg_start, uint32_t length);
void PixelTable_Init(char c);
void PixelTable_Print(void);

#endif // __DISPLAY_H
