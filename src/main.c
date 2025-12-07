#include "common.h"
#include "led.h"
#include "timer.h"
#include "common.h"
#include "scheduler.h"
#include "tasks.h"
#include "spi.h"

#define SCHEDULE_TIME_MS 10

#define SCHEDULE_TIME_FACTOR 1000
#define SCHEDULE_TIME_US (SCHEDULE_TIME_FACTOR * SCHEDULE_TIME_MS)

#define TASK_A_STACK_SIZE 250
#define IDLE_TASK_STACK_SIZE 50

uint32_t stack_TaskA[TASK_A_STACK_SIZE]={0};
uint32_t stack_IdleTask[IDLE_TASK_STACK_SIZE]={0};


void Task_A(void)
{
  SPI_Init();

  while(1)
  {
    SPI_Send();
  }
}

void IdleTask(void)
{
  while(1){
    TESTPIN_ON;
    TESTPIN_OFF;
  }
}
void main()
{
  /* Initialize the LED */
  LED_Init(LED_RED);
  LED_Init(LED_BLUE);
  LED_Init(LED_GREEN);
  TestPin_Init();

  /* Initialize the System Timer */
  SystemTimer_Init(1);

  /* Add Task for Scheduling */
  createTask(stack_TaskA,TASK_A_STACK_SIZE,&Task_A, 1);
  
  /* Set the Systick and PendSV to have Priority 1 (ie.Scheduler should be the Least Priority interrupt and other interrupts are High Priority) */
  SCB->SYSPRI3 &= ~(0x07 << 29);  // SysTick
  SCB->SYSPRI3 &= ~(0x07 << 21);  // PendSV

  SCB->SYSPRI3 |= (0x01 << 29); // SysTick
  SCB->SYSPRI3 |= (0x01 << 21); // PendSV

  /* Idle task should have the Least priority than any other tasks created */
  createTask(stack_IdleTask,IDLE_TASK_STACK_SIZE,&IdleTask, 255);

  /* Initialize and start the Scheduler */
  scheduler_Init(SCHEDULE_TIME_US);

  while(1)
  {
    /* This point shall never be reached*/    
  }
}

/**
 * @brief PB3 is the Test Pin
 * 
 */
void TestPin_Init(void)
{
  /* Enables Clock for Port F */
  SYSCTL->RCGCGPIO |=(1<<1);

  /* Set the Pin Direction as Output */
  GPIOB->DIR |=(1<<3);
  
  /*Select GPIO as pin Function */
  GPIOB->AFSEL &= ~(1<<3);
  
  /* Configure as Digital I/O */
  GPIOB->DEN |=(1<<3);
}