
#include "font.h"
#include "display.h"

#define ALPHABET_SPACING 3

void PrintAlphabet_H(uint32_t cur_ptr, uint32_t font_color, uint32_t font_size)
{
      Disp_sendPixels(font_color, 0, cur_ptr + ALPHABET_SPACING + 0, font_size);
      Disp_sendPixels(font_color, 0, cur_ptr + ALPHABET_SPACING + 1, font_size);

      for(uint8_t iter = ALPHABET_SPACING + 2; iter < font_size - ALPHABET_SPACING - 1; iter++)
      {
            Disp_sendPixels(font_color, (font_size/2) - 1, cur_ptr + iter, 2);
      } 

      Disp_sendPixels(font_color, 0, cur_ptr + (font_size - ALPHABET_SPACING - 1), font_size);
      Disp_sendPixels(font_color, 0, cur_ptr + (font_size - ALPHABET_SPACING), font_size);
}

void PrintAlphabet_N(uint32_t cur_ptr, uint32_t font_color, uint32_t font_size)
{
      Disp_sendPixels(font_color, 0, cur_ptr + ALPHABET_SPACING + 0, font_size);
      Disp_sendPixels(font_color, 0, cur_ptr + ALPHABET_SPACING + 1, font_size);

      for(uint8_t iter = ALPHABET_SPACING; iter < font_size - ALPHABET_SPACING - 1; iter++)
      {
            Disp_sendPixels(font_color, iter, ALPHABET_SPACING + cur_ptr + iter - 1, 2);
      } 

      Disp_sendPixels(font_color, 0, cur_ptr + (font_size - ALPHABET_SPACING - 1), font_size);
      Disp_sendPixels(font_color, 0, cur_ptr + (font_size - ALPHABET_SPACING), font_size);
}

void PrintAlphabet_I(uint32_t cur_ptr, uint32_t font_color, uint32_t font_size)
{
    uint32_t middle_point = ((cur_ptr + font_size - ALPHABET_SPACING) - (cur_ptr + ALPHABET_SPACING)) / 2;
      for(uint8_t iter = ALPHABET_SPACING + 2; iter < font_size - ALPHABET_SPACING - 1; iter++)
      {
            Disp_sendPixels(font_color, 0, cur_ptr + iter, 2);
            Disp_sendPixels(font_color, font_size - 2, cur_ptr + iter, 2);
      }
      
      Disp_sendPixels(font_color, 0, cur_ptr + ALPHABET_SPACING + middle_point, font_size);
      Disp_sendPixels(font_color, 0, cur_ptr + ALPHABET_SPACING + middle_point + 1, font_size);
}

void PrintAlphabet_T(uint32_t cur_ptr, uint32_t font_color, uint32_t font_size)
{
    uint32_t middle_point = ((cur_ptr + font_size - ALPHABET_SPACING) - (cur_ptr + ALPHABET_SPACING)) / 2;
      for(uint8_t iter = ALPHABET_SPACING + 2; iter < font_size - ALPHABET_SPACING - 1; iter++)
      {
            Disp_sendPixels(font_color, 0, cur_ptr + iter, 2);
      }
      
      Disp_sendPixels(font_color, 0, cur_ptr + ALPHABET_SPACING + middle_point, font_size);
      Disp_sendPixels(font_color, 0, cur_ptr + ALPHABET_SPACING + middle_point + 1, font_size);
}

void PrintAlphabet_A(uint32_t cur_ptr, uint32_t font_color, uint32_t font_size)
{
      for(uint8_t iter = ALPHABET_SPACING + 2; iter < font_size - ALPHABET_SPACING - 1; iter++)
      {
            Disp_sendPixels(font_color, 0, cur_ptr + iter, 2);
            Disp_sendPixels(font_color, (font_size/2) - 1, cur_ptr + iter, 2);
      }
      
      Disp_sendPixels(font_color, 0, cur_ptr + ALPHABET_SPACING + 0, font_size);
      Disp_sendPixels(font_color, 0, cur_ptr + ALPHABET_SPACING + 1, font_size);

      Disp_sendPixels(font_color, 0, cur_ptr + (font_size - ALPHABET_SPACING - 1), font_size);
      Disp_sendPixels(font_color, 0, cur_ptr + (font_size - ALPHABET_SPACING), font_size);
}

void PrintAlphabet_Y(uint32_t cur_ptr, uint32_t font_color, uint32_t font_size)
{
    uint32_t center = font_size / 2;
    
    // Left diagonal line from top-left to center
    for(uint8_t iter = 0; iter < center - ALPHABET_SPACING; iter++)
    {
        Disp_sendPixels(font_color, iter, cur_ptr + ALPHABET_SPACING + iter, 2);
    }
    
    // Right diagonal line from top-right to center
    for(uint8_t iter = 0; iter < center - ALPHABET_SPACING; iter++)
    {
        Disp_sendPixels(font_color, iter, cur_ptr + font_size - ALPHABET_SPACING - 1 - iter, 2);
    }
    
    // Center vertical line downward
    for(uint8_t iter = center - 2; iter < font_size - ALPHABET_SPACING + 1; iter++)
    {
        Disp_sendPixels(font_color, iter, cur_ptr + center - 1, 1);
        Disp_sendPixels(font_color, iter, cur_ptr + center, 1);
    }
}