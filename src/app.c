#include "spi.h"
#include "gpio.h"
#include "pinconfig.h"
#include "TouchDisplay/display.h"
#include "scheduler.h"

void Task_A(void)
{
  Disp_Init();

  while(1)
  {
    Disp_Run();
  }
}
