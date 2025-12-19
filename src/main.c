#include "common.h"
#include "OS/scheduler.h"
#include "OS/tasks.h"
#include "Application/app.h"
#include "Debug/testpin.h"
#include "../src/Drivers/Timer/timer.h"

#define SCHEDULE_TIME_MS 10

#define SCHEDULE_TIME_FACTOR 1000
#define SCHEDULE_TIME_US (SCHEDULE_TIME_FACTOR * SCHEDULE_TIME_MS)

extern uint32_t App_TaskStack[APP_TASK_STACK_SIZE];

void main()
{
  TestPin_Init();

  /* Add Task for Scheduling */
  createTask(App_TaskStack,APP_TASK_STACK_SIZE,&App_Task, 1);

  /* Initialize the System Timer */
  SystemTimer_Start(1);

  /* Initialize and start the Scheduler */
  OS_schedulerRun(SCHEDULE_TIME_US);

  while(1)
  {
    /* This point shall never be reached*/    
  }
}
