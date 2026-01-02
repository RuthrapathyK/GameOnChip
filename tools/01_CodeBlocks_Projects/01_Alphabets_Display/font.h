
#ifndef __FONT_H
#define __FONT_H

#include "display.h"

typedef struct{
    uint16_t rPtr;
    uint16_t cPtr;
}Alphabet_PixPtr_t;

typedef struct{
    uint32_t Font_Color;
    uint8_t Font_Size;
    uint8_t Font_Thickness;
    uint8_t Font_Spacing;
}Alphabet_FontProp_t;

void PrintAlphabet_H(Alphabet_PixPtr_t * p, Alphabet_FontProp_t * fontProp);
void PrintAlphabet_N(Alphabet_PixPtr_t * p, Alphabet_FontProp_t * fontProp);
void PrintAlphabet_I(Alphabet_PixPtr_t * p, Alphabet_FontProp_t * fontProp);
void PrintAlphabet_T(Alphabet_PixPtr_t * p, Alphabet_FontProp_t * fontProp);
void PrintAlphabet_A(Alphabet_PixPtr_t * p, Alphabet_FontProp_t * fontProp);
void PrintAlphabet_Y(Alphabet_PixPtr_t * p, Alphabet_FontProp_t * fontProp);
void PrintWord(char *word, Alphabet_PixPtr_t *PixPointer, Alphabet_FontProp_t *PixProperty);

#endif
