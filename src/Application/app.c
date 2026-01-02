#include "../Drivers/SPI/spi.h"
#include "../Drivers/GPIO/gpio.h"
#include "../Drivers/PinMux/pinconfig.h"
#include "../BSP/TouchDisplay/display.h"
#include "../BSP/TouchDisplay/font.h"
#include "../OS/scheduler.h"
#include "app.h"


void App_MultiColour_Display(void);

uint32_t App_TaskStack[APP_TASK_STACK_SIZE]={0};


void App_Task(void)
{
    Alphabet_PixPtr_t PixPointer = {
        .rPtr = 0,
        .cPtr = 0};

    Alphabet_FontProp_t PixProperty = {
        .Font_Color = 0x0000FF,
        .Font_Size =40,
        .Font_Thickness = 2,
        .Font_Spacing = 1};

  Disp_Init();
  /* Write Black in Complete Screen */
  Disp_sendPixels(0x000000, 0, 0, 240 * 320);

  while(1)
  {
      PrintWord("NITHYA\n", &PixPointer, &PixProperty); 
      PixProperty.Font_Size -= 4;
      if(PixProperty.Font_Size < 4)
             PixProperty.Font_Size = 4;
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