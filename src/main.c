#include "common.h"
#include "LED/led.h"
#include "Drivers/timer.h"
#include "common.h"
#include "OS/scheduler.h"
#include "OS/tasks.h"
#include "Application/app.h"
#include "Debug/testpin.h"

#define SCHEDULE_TIME_MS 10

#define SCHEDULE_TIME_FACTOR 1000
#define SCHEDULE_TIME_US (SCHEDULE_TIME_FACTOR * SCHEDULE_TIME_MS)

#define TASK_A_STACK_SIZE 250

uint32_t stack_TaskA[TASK_A_STACK_SIZE]={0};

void main()
{
  TestPin_Init();

  /* Initialize the System Timer */
  SystemTimer_Start(1);

  /* Add Task for Scheduling */
  createTask(stack_TaskA,TASK_A_STACK_SIZE,&Task_A, 1);

  /* Initialize and start the Scheduler */
  OS_schedulerRun(SCHEDULE_TIME_US);

  while(1)
  {
    /* This point shall never be reached*/    
  }
}
