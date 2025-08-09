
#ifndef __SEMAPHORES_H
#define __SEMAPHORES_H

#include "TM4C123GH6PM.h"
#include "common.h"
#include "tasks.h"
#include "scheduler.h"

/**
 * @brief The Function gets Exclusive access to the memory passed and decreaments it by 1
 * 
 * @param sem_obj Address of the variable for which value needs to be decreamented
 */
void Sem_Take(uint32_t * sem_obj);

/**
 * @brief The Function gets Exclusive access to the memory passed and increaments it by 1
 * 
 * @param sem_obj Address of the variable for which value needs to be Increamented
 */
void Sem_Give(uint32_t * sem_obj);

typedef uint32_t Semaphore_Type;

#endif