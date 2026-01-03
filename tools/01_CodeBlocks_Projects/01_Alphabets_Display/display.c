#include "display.h"
#include <stdio.h>
#include <stdint.h>



uint8_t pixelTable[PIXELTABLE_RESOLUTION_COULUMN][PIXELTABLE_RESOLUTION_ROW];

void PixelTable_Init(char c)
{
    for(uint32_t iter_1 = 0; iter_1 < PIXELTABLE_RESOLUTION_COULUMN; iter_1++)
    {
      for(uint32_t iter_2 = 0; iter_2 < PIXELTABLE_RESOLUTION_ROW; iter_2++)
      {
          pixelTable[iter_1][iter_2] = c;
      }
    }
}

void PixelTable_Print(void)
{
    for(uint32_t iter_1 = 0; iter_1 < PIXELTABLE_RESOLUTION_COULUMN; iter_1++)
    {
      for(uint32_t iter_2 = 0; iter_2 < PIXELTABLE_RESOLUTION_ROW; iter_2++)
      {
          printf("%c ",pixelTable[iter_1][iter_2]);
      }
      printf("\n");
    }
}

void DISP_sendPixels(uint32_t pixelVal, uint32_t col_start, uint32_t pg_start, uint32_t length)
{
    (void)pixelVal;

    for(uint32_t iter = 0; iter < length; iter++)
    {
      pixelTable[iter + col_start][pg_start] = '*';
    }
}
