#include "semaphores.h"


extern Task_type PrioTask_Table[MAX_TASK_LIMIT];

/**
 * @brief The Function gets Exclusive access to the memory passed and decreaments it by 1
 * 
 * @param sem_obj Address of the variable for which value needs to be decreamented
 */
void Sem_Take(Semaphore_Type * sem_obj)
{
  // The argument will be by default stored in R0 for this compiler. 
  // If it changes then next assembly codes will also change

  // Start of the assembly function(This is busy wait implementation)
  __asm volatile (
          "MOV R11, R0\n\t"         // Move the R0 value(ie. argument) to R11 for further usage in assembly

      "lockTry:\n\t"                // Branch Label 
        "LDREX R4, [R11]\n\t"       // Load value at sem_obj into R4 by Exclusively tagging processor and memory
        "CMP R4, #0\n\t"            // Compare with 0
        "BEQ OS_semSleep\n\t"       // If zero, move to OS_semSleep
        "SUB R4, R4, #1\n\t"        // If not equal to Zero then take the Token (R1 = R0 - 1)
        "STREX R5, R4, [R11]\n\t"   // Try to store R4 back to sem_obj
        "CMP R5, #0\n\t"            // Was store successful?
        "BNE lockTry\n\t"           // If not successful retry from Branch Label
        "B Sem_TakeEnd\n\t"          // Branch to completion
    );

__asm volatile("OS_semSleep:"); // Start of assembly label and the following C code belongs to this

  /* Store the Address of the Semaphore Object in the corresponding Task's Priority Table*/
  PrioTask_Table[getCurrent_TaskIdx()].syncPrim = sem_obj;

  /* Change the task state to Sleep */
  PrioTask_Table[getCurrent_TaskIdx()].TaskState = Task_Sleep;

  /* Trigger the scheduler */
  SYSTICK_TRIGGER;

  __asm volatile("B lockTry"); // Retry Locking once the Task has waked up from Sleep 

  __asm volatile("Sem_TakeEnd:"); // This is the label to execute the closing of instructions
}

/**
 * @brief The Function gets Exclusive access to the memory passed and increaments it by 1
 * 
 * @param sem_obj Address of the variable for which value needs to be Increamented
 */
void Sem_Give(Semaphore_Type * sem_obj)
{
  // The argument will be by default stored in R0 for this compiler. 
  // If it changes then next assembly codes will also change

  // Start of the assembly function
  __asm volatile(
    "MOV R3, R0\n\t"                   // Move the R0 value to R3 for further usage in assembly

    "unlockTry:\n\t"                   // Branch Label 
            "LDREX R0, [R3]\n\t"       // Load value at sem_obj into R0 by Exclusively tagging processor and memory
            "ADD R1, R0, #1\n\t"       // Add 1 to the value
            "STREX R2, R1, [R3]\n\t"   // Try to store R1 back to sem_obj
            "CMP R2, #0\n\t"           // Was store successful?
            "BNE unlockTry\n\t"        // If not successful retry from Branch Label
  );

  /* Trigger the scheduler */
  SYSTICK_TRIGGER;
}