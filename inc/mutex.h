#ifndef MUTEX_H
#define MUTEX_H


#include "TM4C123GH6PM.h"
#include "common.h"
#include "tasks.h"

typedef enum{
    Mutex_Locked = 0,
    Mutex_Unlocked = 1,
    Mutex_Max_State
}Mutex_state_e;

/**
 * Application Shall not modify any of the Members or Unknown behaviour will happen
 */
typedef struct {
    Mutex_state_e Mutex_State;  // State of the Mutex Object(ie. Whether it is Locked or Unlocked)
    uint32_t Task_Index;        // Index of the Task which holds the Mutex's Ownership
    bool isInitialized; 
}Mutex_Type;

void Mutex_Init(Mutex_Type *mutex_obj);
void Mutex_Lock(Mutex_Type *mutex_obj);
void Mutex_Unlock(Mutex_Type *mutex_obj);

#endif