#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "display.h"
#include "font.h"

void PrintWord(char *word, Alphabet_PixPtr_t *PixPointer, Alphabet_FontProp_t *PixProperty)
{
    while(*word)
    {
        switch(*word)
        {
        case 'N':
            PrintAlphabet_N(PixPointer, PixProperty);
            break;
        case 'I':
            PrintAlphabet_I(PixPointer, PixProperty);
            break;
        case 'T':
            PrintAlphabet_T(PixPointer, PixProperty);
            break;
        case 'H':
            PrintAlphabet_H(PixPointer, PixProperty);
            break;
        case 'A':
            PrintAlphabet_A(PixPointer, PixProperty);
            break;
        case 'Y':
            PrintAlphabet_Y(PixPointer, PixProperty);
            break;
        case ' ':
            /* Don't print anything - Increment the Row Pointer */
            break;
        case '\n':
            /* Exceed the Maximum Row resolution Intentionally */
            PixPointer->rPtr = PIXELTABLE_RESOLUTION_ROW;
            break;
        default:
            while(1);
        }
        /* Increment the Row Pointer */
        PixPointer->rPtr += PixProperty->Font_Size;

        /* If Row Pointer Exceeds the Resolution then Wrap up to Next Column */
        if(PixPointer->rPtr > PIXELTABLE_RESOLUTION_ROW - PixProperty->Font_Size)
        {
            PixPointer->rPtr = 0;
            PixPointer->cPtr += PixProperty->Font_Size;
        }

        /* If Column Pointer also Exceeded the pause the Execution */
        if(PixPointer->cPtr > PIXELTABLE_RESOLUTION_COULUMN - PixProperty->Font_Size)
        {
            while(1);
        }

        word++;
    }
}

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

    PrintWord("NITHYA\n NITHYA", &PixPointer, &PixProperty);

    PixelTable_Print();
    return 0;
}

