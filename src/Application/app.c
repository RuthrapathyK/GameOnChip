#include "../Drivers/SPI/spi.h"
#include "../Drivers/GPIO/gpio.h"
#include "../Drivers/PinMux/pinconfig.h"
#include "../BSP/TouchDisplay/display.h"
#include "../BSP/TouchDisplay/font.h"
#include "../OS/scheduler.h"
#include "../BSP/Serial_Keyboard/keyboard.h"
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


      DISP_Init();
      SKEY_Init();

      /* Write Black in Complete Screen */
      DISP_sendPixels(0x000000, 0, 0, DISP_RESOLUTION_COLUMN * DISP_RESOLUTION_ROW);

      uint8_t c[2] = {0};

      while(1)
      {
            c[0] = SKEY_ReceiveChar();
            PrintWord(c, &PixPointer, &PixProperty); 
      }
}

void App_MultiColour_Display(void)
{
    static uint8_t count = 0;
    
    count %= 5;

     switch(count)
     {
      case 0:
            DISP_sendPixels(0xFF0000, 0, 0, 240 * 160);
            break;
      case 1:
            DISP_sendPixels(0x0000FF, 0, 160, 240 * 160);
            break;
      case 2:
            DISP_sendPixels(0x00FF00, 0, 0, 240 * 160);
            break;
      case 3:
            DISP_sendPixels(0x000000, 0, 160, 240 * 160);
            break;
      case 4:
            DISP_sendPixels(0xFFFFFF, 0, 0, 240 * 160);
            break;
      default:
            break;            
     }
     count++;
}