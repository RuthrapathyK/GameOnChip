
#include "font.h"
#include "display.h"

void Draw_StarightLine(uint16_t rStart, uint16_t rEnd, uint16_t cStart, uint16_t cEnd, uint32_t color)
{
    for(uint16_t rIter = rStart; rIter < rEnd; rIter++)
    {
        for(uint16_t cIter = cStart; cIter < cEnd; cIter++)
        {
            Disp_sendPixels(color, cIter, rIter, 1);
        }
    }
}
void Draw_CrossLine(uint16_t rStart, uint16_t rEnd, uint16_t cStart, uint16_t cEnd, uint32_t color)
{
    for(uint16_t rIter = rStart, cIter = cStart; (rIter < rEnd) && (cIter < cEnd); rIter++, cIter++)
    {
        Disp_sendPixels(color, cIter, rIter, 1);
    }
}

void PrintAlphabet_H(Alphabet_PixPtr_t * p, Alphabet_FontProp_t * fontProp)
{
    uint16_t Row_Min = p->rPtr + fontProp->Font_Spacing;
    uint16_t Row_Max = p->rPtr + fontProp->Font_Size - fontProp->Font_Spacing;
    uint16_t Row_Mid = ((Row_Max - Row_Min)/2) + p->rPtr;
    uint16_t Column_Min = p->cPtr + fontProp->Font_Spacing;
    uint16_t Column_Max = p->cPtr + fontProp->Font_Size - fontProp->Font_Spacing;
    uint16_t Column_Mid = ((Column_Max - Column_Min)/2) + p->cPtr;

    /* Vertical Lines */
    Draw_StarightLine(Row_Min, Row_Min+fontProp->Font_Thickness, Column_Min, Column_Max, fontProp->Font_Color);
    Draw_StarightLine(Row_Max-fontProp->Font_Thickness, Row_Max, Column_Min, Column_Max, fontProp->Font_Color);

    /* Horizontal Line */
    Draw_StarightLine(Row_Min, Row_Max, Column_Mid, Column_Mid + fontProp->Font_Thickness, fontProp->Font_Color);

    /*Unused Variable */
    (void)Row_Mid;
}

void PrintAlphabet_N(Alphabet_PixPtr_t * p, Alphabet_FontProp_t * fontProp)
{
    uint16_t Row_Min = p->rPtr + fontProp->Font_Spacing;
    uint16_t Row_Max = p->rPtr + fontProp->Font_Size - fontProp->Font_Spacing;
    uint16_t Row_Mid = ((Row_Max - Row_Min)/2) + p->rPtr;
    uint16_t Column_Min = p->cPtr + fontProp->Font_Spacing;
    uint16_t Column_Max = p->cPtr + fontProp->Font_Size - fontProp->Font_Spacing;
    uint16_t Column_Mid = ((Column_Max - Column_Min)/2) + p->cPtr;

    /* Vertical Lines */
    Draw_StarightLine(Row_Min, Row_Min+fontProp->Font_Thickness, Column_Min, Column_Max, fontProp->Font_Color);
    Draw_StarightLine(Row_Max-fontProp->Font_Thickness, Row_Max, Column_Min, Column_Max, fontProp->Font_Color);

    /* Cross Line */
    for(uint16_t thickIter = 0; thickIter < fontProp->Font_Thickness; thickIter++)
    {
        Draw_CrossLine(Row_Min + fontProp->Font_Thickness, Row_Max, Column_Min + thickIter, Column_Max, fontProp->Font_Color);
    }

    /*Unused Variable */
    (void)Row_Mid;
}

void PrintAlphabet_I(Alphabet_PixPtr_t * p, Alphabet_FontProp_t * fontProp)
{
    uint16_t Row_Min = p->rPtr + fontProp->Font_Spacing;
    uint16_t Row_Max = p->rPtr + fontProp->Font_Size - fontProp->Font_Spacing;
    uint16_t Row_Mid = ((Row_Max - Row_Min)/2) + p->rPtr;
    uint16_t Column_Min = p->cPtr + fontProp->Font_Spacing;
    uint16_t Column_Max = p->cPtr + fontProp->Font_Size - fontProp->Font_Spacing;
    uint16_t Column_Mid = ((Column_Max - Column_Min)/2) + p->cPtr;

    /* Horizontal Line */
    Draw_StarightLine(Row_Min, Row_Max, Column_Min, Column_Min+fontProp->Font_Thickness, fontProp->Font_Color);
    Draw_StarightLine(Row_Min, Row_Max, Column_Max-fontProp->Font_Thickness, Column_Max, fontProp->Font_Color);

    /* Vertical Line */
    Draw_StarightLine(Row_Mid, Row_Mid+fontProp->Font_Thickness, Column_Min, Column_Max, fontProp->Font_Color);

    /*Unused Variable */
    (void)Column_Mid;
}

void PrintAlphabet_T(Alphabet_PixPtr_t * p, Alphabet_FontProp_t * fontProp)
{
    uint16_t Row_Min = p->rPtr + fontProp->Font_Spacing;
    uint16_t Row_Max = p->rPtr + fontProp->Font_Size - fontProp->Font_Spacing;
    uint16_t Row_Mid = ((Row_Max - Row_Min)/2) + p->rPtr;
    uint16_t Column_Min = p->cPtr + fontProp->Font_Spacing;
    uint16_t Column_Max = p->cPtr + fontProp->Font_Size - fontProp->Font_Spacing;
    uint16_t Column_Mid = ((Column_Max - Column_Min)/2) + p->cPtr;

    /* Horizontal Line */
    Draw_StarightLine(Row_Min, Row_Max, Column_Min, Column_Min+fontProp->Font_Thickness, fontProp->Font_Color);

    /* Vertical Line */
    Draw_StarightLine(Row_Mid, Row_Mid+fontProp->Font_Thickness, Column_Min, Column_Max, fontProp->Font_Color);

    /*Unused Variable */
    (void)Column_Mid;
}
//
//void PrintAlphabet_A(uint32_t cur_ptr, uint32_t font_color, uint32_t font_size)
//{
//      for(uint8_t iter = ALPHABET_SPACING + 2; iter < font_size - ALPHABET_SPACING - 1; iter++)
//      {
//            Disp_sendPixels(font_color, 0, cur_ptr + iter, 2);
//            Disp_sendPixels(font_color, (font_size/2) - 1, cur_ptr + iter, 2);
//      }
//
//      Disp_sendPixels(font_color, 0, cur_ptr + ALPHABET_SPACING + 0, font_size);
//      Disp_sendPixels(font_color, 0, cur_ptr + ALPHABET_SPACING + 1, font_size);
//
//      Disp_sendPixels(font_color, 0, cur_ptr + (font_size - ALPHABET_SPACING - 2), font_size);
//      Disp_sendPixels(font_color, 0, cur_ptr + (font_size - ALPHABET_SPACING - 1), font_size);
//}
//
//void PrintAlphabet_Y(uint32_t cur_ptr, uint32_t font_color, uint32_t font_size)
//{
//    uint32_t center = font_size / 2;
//
//    // Left diagonal line from top-left to center
//    for(uint8_t iter = 0; iter < center - ALPHABET_SPACING; iter++)
//    {
//        Disp_sendPixels(font_color, iter, cur_ptr + ALPHABET_SPACING + iter, 2);
//    }
//
//    // Right diagonal line from top-right to center
//    for(uint8_t iter = 0; iter < center - ALPHABET_SPACING; iter++)
//    {
//        Disp_sendPixels(font_color, iter, cur_ptr + font_size - ALPHABET_SPACING - 1 - iter, 2);
//    }
//
//    // Center vertical line downward
//    for(uint8_t iter = center - 2; iter < font_size - ALPHABET_SPACING - 1; iter++)
//    {
//        Disp_sendPixels(font_color, iter, cur_ptr + center - 1, 3);
//        Disp_sendPixels(font_color, iter, cur_ptr + center, 3);
//    }
//}
