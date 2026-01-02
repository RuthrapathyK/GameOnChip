
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
    if((int32_t)rEnd - (int32_t)rStart > 0)
    {
        if((int32_t)cEnd - (int32_t)cStart > 0)
        {
            /* Draw the Increasing Row and Increasing Column Line */
            for(uint16_t rIter = rStart, cIter = cStart; (rIter < rEnd) && (cIter < cEnd); rIter++, cIter++)
            {
                Disp_sendPixels(color, cIter, rIter, 1);
            }
        }
        else if((int32_t)cEnd - (int32_t)cStart < 0)
        {
            /* Draw the Increasing Row and Decreasing Column Line */
            for(uint16_t rIter = rStart, cIter = cStart; (rIter < rEnd) && (cIter > cEnd); rIter++, cIter--)
            {
                Disp_sendPixels(color, cIter, rIter, 1);
            }
        }
        else
        {
            //ASSERT(0);
        }
    }
    else if((int32_t)rEnd - (int32_t)rStart < 0)
    {
        if((int32_t)cEnd - (int32_t)cStart > 0)
        {
            /* Draw the Decreasing Row and Increasing Column Line */
            for(uint16_t rIter = rStart, cIter = cStart; (rIter > rEnd) && (cIter < cEnd); rIter--, cIter++)
            {
                Disp_sendPixels(color, cIter, rIter, 1);
            }
        }
        else if((int32_t)cEnd - (int32_t)cStart < 0)
        {
            /* Draw the Decreasing Row and Decreasing Column Line */
            for(uint16_t rIter = rStart, cIter = cStart; (rIter > rEnd) && (cIter > cEnd); rIter--, cIter--)
            {
                Disp_sendPixels(color, cIter, rIter, 1);
            }
        }
        else
        {
            while(1);
        }
    }
    else
    {
        while(1);
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
        Draw_CrossLine(Row_Min + (fontProp->Font_Thickness - 1), Row_Max, Column_Min + thickIter, Column_Max, fontProp->Font_Color);
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

void PrintAlphabet_A(Alphabet_PixPtr_t * p, Alphabet_FontProp_t * fontProp)
{
    uint16_t Row_Min = p->rPtr + fontProp->Font_Spacing;
    uint16_t Row_Max = p->rPtr + fontProp->Font_Size - fontProp->Font_Spacing;
    uint16_t Row_Mid = ((Row_Max - Row_Min)/2) + p->rPtr;
    uint16_t Column_Min = p->cPtr + fontProp->Font_Spacing;
    uint16_t Column_Max = p->cPtr + fontProp->Font_Size - fontProp->Font_Spacing;
    uint16_t Column_Mid = ((Column_Max - Column_Min)/2) + p->cPtr;

    /* Cross Line */
    for(uint16_t thickIter = 0; thickIter < fontProp->Font_Thickness; thickIter++)
    {
        Draw_CrossLine(Row_Mid + thickIter, Row_Min, Column_Min, Column_Mid, fontProp->Font_Color);
        Draw_CrossLine(Row_Mid + thickIter, Row_Max, Column_Min, Column_Mid, fontProp->Font_Color);
    }

    /* Vertical Lines */
    Draw_StarightLine(Row_Min, Row_Min+fontProp->Font_Thickness, Column_Mid, Column_Max, fontProp->Font_Color);
    Draw_StarightLine(Row_Max-fontProp->Font_Thickness, Row_Max, Column_Mid, Column_Max, fontProp->Font_Color);

    /* Horizontal Line */
    Draw_StarightLine(Row_Min, Row_Max, Column_Mid, Column_Mid+fontProp->Font_Thickness, fontProp->Font_Color);
}

void PrintAlphabet_Y(Alphabet_PixPtr_t * p, Alphabet_FontProp_t * fontProp)
{
    uint16_t Row_Min = p->rPtr + fontProp->Font_Spacing;
    uint16_t Row_Max = p->rPtr + fontProp->Font_Size - fontProp->Font_Spacing;
    uint16_t Row_Mid = ((Row_Max - Row_Min)/2) + p->rPtr;
    uint16_t Column_Min = p->cPtr + fontProp->Font_Spacing;
    uint16_t Column_Max = p->cPtr + fontProp->Font_Size - fontProp->Font_Spacing;
    uint16_t Column_Mid = ((Column_Max - Column_Min)/2) + p->cPtr;

    /* Cross Line */
    for(uint16_t thickIter = 0; thickIter <= fontProp->Font_Thickness; thickIter++)
    {
        Draw_CrossLine(Row_Min + thickIter, Row_Mid +2, Column_Min, Column_Mid +2, fontProp->Font_Color);
        Draw_CrossLine(Row_Max - thickIter, Row_Mid, Column_Min, Column_Mid +2, fontProp->Font_Color);
    }

    /* Vertical Line */
    if(fontProp->Font_Thickness % 2 == 0)
        Draw_StarightLine(Row_Mid, Row_Mid+fontProp->Font_Thickness, Column_Mid, Column_Max, fontProp->Font_Color);
    else
        Draw_StarightLine(Row_Mid, Row_Mid+fontProp->Font_Thickness+1, Column_Mid, Column_Max, fontProp->Font_Color);

}
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
            PixPointer->rPtr = 320;
            break;
        default:
            while(1);
        }
        /* Increment the Row Pointer */
        PixPointer->rPtr += PixProperty->Font_Size;

        /* If Row Pointer Exceeds the Resolution then Wrap up to Next Column */
        if(PixPointer->rPtr > 320 - PixProperty->Font_Size)
        {
            PixPointer->rPtr = 0;
            PixPointer->cPtr += PixProperty->Font_Size;
        }

        /* If Column Pointer also Exceeded the pause the Execution */
        if(PixPointer->cPtr > 240 - PixProperty->Font_Size)
        {
            while(1);
        }

        word++;
    }
}
