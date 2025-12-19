#include "../Drivers/SPI/spi.h"
#include "../Drivers/GPIO/gpio.h"
#include "../Drivers/PinMux/pinconfig.h"
#include "../TouchDisplay/display.h"
#include "../OS/scheduler.h"
#include "app.h"

uint32_t App_TaskStack[APP_TASK_STACK_SIZE]={0};

void App_Task(void)
{
  Disp_Init();

  while(1)
  {
    Disp_Run();
  }
}
