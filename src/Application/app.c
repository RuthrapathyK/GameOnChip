#include "../Drivers/spi.h"
#include "../Drivers/gpio.h"
#include "../Drivers/pinconfig.h"
#include "../TouchDisplay/display.h"
#include "../OS/scheduler.h"

void Task_A(void)
{
  Disp_Init();

  while(1)
  {
    Disp_Run();
  }
}
