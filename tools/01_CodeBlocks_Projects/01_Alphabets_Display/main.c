#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "display.h"
#include "font.h"

int main()
{
    Alphabet_PixPtr_t PixPointer = {
        .rPtr = 0,
        .cPtr = 0};

    Alphabet_FontProp_t PixProperty = {
        .Font_Color = 0xFF0000,
        .Font_Size = 20,
        .Font_Thickness = 2,
        .Font_Spacing = 1};

    PixelTable_Init('.');

    PixPointer.rPtr = 0;
    PixPointer.cPtr = 0;
    PrintAlphabet_H(&PixPointer, &PixProperty);

    PixPointer.rPtr += PixProperty.Font_Size;
    PrintAlphabet_I(&PixPointer, &PixProperty);

    PixPointer.cPtr += PixProperty.Font_Size;
    PixPointer.rPtr = 0;
    PrintAlphabet_I(&PixPointer, &PixProperty);

    PixPointer.rPtr += PixProperty.Font_Size;
    PrintAlphabet_N(&PixPointer, &PixProperty);

    PixPointer.rPtr += PixProperty.Font_Size;
    PrintAlphabet_T(&PixPointer, &PixProperty);

    PixPointer.cPtr += PixProperty.Font_Size;
    PixPointer.rPtr = 0;
    PrintAlphabet_A(&PixPointer, &PixProperty);

    PixelTable_Print();
    return 0;
}
