#include "mutex.h"
#include "semaphores.h"

void Mutex_Init(Mutex_Type *mutex_obj)
{
    /* Check the Input Parameters */
    ASSERT(mutex_obj != NULL);

    /* Initialize the Mutex Object */
    mutex_obj->Mutex_State = Mutex_Unlocked;
    mutex_obj->Task_Index = 255; // Make it as the Last Task Index
    mutex_obj->isInitialized = true;
}

void Mutex_Lock(Mutex_Type *mutex_obj)
{
    /* Check the Input Parameters */
    ASSERT((mutex_obj != NULL) && (mutex_obj->Mutex_State < Mutex_Max_State));
    
    /* Perform Locking only when the Mutex Object is Initialized */
    ASSERT(mutex_obj->isInitialized == true);

    /* Lock the Mutex if it is available. If not move the Task to Sleep State */
    Sem_Take((Semaphore_Type *) &mutex_obj->Mutex_State);

    /* Make Current Task as the Owner of the Mutex */
    mutex_obj->Task_Index = getCurrent_TaskIdx();

}

void Mutex_Unlock(Mutex_Type *mutex_obj)
{
    /* Check the Input Parameters */
    ASSERT((mutex_obj != NULL) && (mutex_obj->Mutex_State < Mutex_Max_State));
    
    /* Perform Locking only when the Mutex Object is Initialized */
    ASSERT(mutex_obj->isInitialized == true);

    /* Check if The Current Task is the Owner of the Mutex */
    if(mutex_obj->Task_Index == getCurrent_TaskIdx())
        Sem_Give((Semaphore_Type *) &mutex_obj->Mutex_State); // Unlock the Mutex
    else
        ASSERT(0); // Assert the Program
}