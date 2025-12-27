#include "../Drivers/SPI/spi.h"
#include "../Drivers/GPIO/gpio.h"
#include "../Drivers/PinMux/pinconfig.h"
#include "../BSP/TouchDisplay/display.h"
#include "../BSP/TouchDisplay/font.h"
#include "../OS/scheduler.h"
#include "app.h"

#define ALPHABET_FONT_SIZE 30

void App_MultiColour_Display(void);

uint32_t App_TaskStack[APP_TASK_STACK_SIZE]={0};
Disp_Pixel_type Diplay_Pixel = {0};


void App_Task(void)
{
  uint32_t cur_ptr = 0;

  Disp_Init();
  /* Write Black in Complete Screen */
  Disp_sendPixels(0x000000, 0, 0, 240 * 320);

  while(1)
  {
      PrintAlphabet_N(cur_ptr, 0xFF0000, ALPHABET_FONT_SIZE);
      cur_ptr += ALPHABET_FONT_SIZE;

      PrintAlphabet_I(cur_ptr, 0x00FF00, ALPHABET_FONT_SIZE);
      cur_ptr += ALPHABET_FONT_SIZE;

      PrintAlphabet_T(cur_ptr, 0x0000FF, ALPHABET_FONT_SIZE);
      cur_ptr += ALPHABET_FONT_SIZE;

      PrintAlphabet_H(cur_ptr, 0xFF0000, ALPHABET_FONT_SIZE);
      cur_ptr += ALPHABET_FONT_SIZE;

      PrintAlphabet_Y(cur_ptr, 0x00FF00, ALPHABET_FONT_SIZE);
      cur_ptr += ALPHABET_FONT_SIZE;

      PrintAlphabet_A(cur_ptr, 0x0000FF, ALPHABET_FONT_SIZE);
      cur_ptr = 0;
  }
}

void App_MultiColour_Display(void)
{
    static uint8_t count = 0;
    
    count %= 5;

     switch(count)
     {
      case 0:
            Disp_sendPixels(0xFF0000, 0, 0, 240 * 160);
            break;
      case 1:
            Disp_sendPixels(0x0000FF, 0, 160, 240 * 160);
            break;
      case 2:
            Disp_sendPixels(0x00FF00, 0, 0, 240 * 160);
            break;
      case 3:
            Disp_sendPixels(0x000000, 0, 160, 240 * 160);
            break;
      case 4:
            Disp_sendPixels(0xFFFFFF, 0, 0, 240 * 160);
            break;
      default:
            break;            
     }
     count++;
}