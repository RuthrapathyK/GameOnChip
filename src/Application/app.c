#include "../Drivers/SPI/spi.h"
#include "../Drivers/GPIO/gpio.h"
#include "../Drivers/PinMux/pinconfig.h"
#include "../BSP/TouchDisplay/display.h"
#include "../OS/scheduler.h"
#include "app.h"

uint32_t App_TaskStack[APP_TASK_STACK_SIZE]={0};
uint8_t count = 0;
Disp_Pixel_type Diplay_Pixel = {0};

void App_Task(void)
{
  Disp_Init();

  while(1)
  {
    count %= 5;

     switch(count)
     {
      case 0:
            Diplay_Pixel.Pixel_Red = 63;
            Diplay_Pixel.Pixel_Green = 0;
            Diplay_Pixel.Pixel_Blue = 0;
            Disp_sendPixels(&Diplay_Pixel, 0, 0, 240 * 160);
            break;
      case 1:
            Diplay_Pixel.Pixel_Red = 0;
            Diplay_Pixel.Pixel_Green = 0;
            Diplay_Pixel.Pixel_Blue = 63;
            Disp_sendPixels(&Diplay_Pixel, 0, 160, 240 * 160);
            break;
      case 2:
            Diplay_Pixel.Pixel_Red = 0;
            Diplay_Pixel.Pixel_Green = 63;
            Diplay_Pixel.Pixel_Blue = 0;
            Disp_sendPixels(&Diplay_Pixel, 0, 0, 240 * 160);
            break;
      case 3:
            Diplay_Pixel.Pixel_Red = 0;
            Diplay_Pixel.Pixel_Green = 0;
            Diplay_Pixel.Pixel_Blue = 0;
            Disp_sendPixels(&Diplay_Pixel, 0, 160, 240 * 160);
            break;
      case 4:
            Diplay_Pixel.Pixel_Red = 63;
            Diplay_Pixel.Pixel_Green = 63;
            Diplay_Pixel.Pixel_Blue = 63;
            Disp_sendPixels(&Diplay_Pixel, 0, 0, 240 * 160);
            break;
      default:
            break;            
     }
     count++;
  }
}
