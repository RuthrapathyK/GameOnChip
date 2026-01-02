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
        .Font_Thickness = 4,
        .Font_Spacing = 1};

    PixelTable_Init('.');

    PrintWord("NITY", &PixPointer, &PixProperty);

    PixelTable_Print();
    return 0;
}

