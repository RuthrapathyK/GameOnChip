#include "spi.h"
#include "gpio.h"
#include "pinconfig.h"
#include "display.h"
#include "scheduler.h"

void Task_A(void)
{
  Disp_Init();

  while(1)
  {
    Disp_Run();
    OS_delay(1000);
  }
}
