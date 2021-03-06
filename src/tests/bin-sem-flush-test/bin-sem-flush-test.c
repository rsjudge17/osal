/*
** Binary Semaphore Flush Test
*/
#include <stdio.h>
#include "common_types.h"
#include "osapi.h"

#define TASK_STACK_SIZE  4096
#define TASK_1_PRIORITY  100
#define TASK_2_PRIORITY  110
#define TASK_3_PRIORITY  120

uint32 task_1_stack[TASK_STACK_SIZE];
uint32 task_1_id; 

uint32 task_2_stack[TASK_STACK_SIZE];
uint32 task_2_id; 

uint32 task_3_stack[TASK_STACK_SIZE];
uint32 task_3_id; 

uint32 bin_sem_id;

void task_1(void)
{
    uint32             status;
    OS_bin_sem_prop_t  bin_sem_prop;
    int                counter = 0;

    OS_printf("Starting task 1\n");
    OS_TaskRegister();

    OS_printf("TASK 1: Waiting on the semaphore\n");
    status = OS_BinSemTake(bin_sem_id);
    if ( status != OS_SUCCESS )
    {
       OS_printf("TASK 1: Error calling OS_BinSemTake\n");
    }
    else
    {
       status = OS_BinSemGetInfo (bin_sem_id, &bin_sem_prop);
       OS_printf("TASK 1: out of BinSemTake: %d\n",(int)bin_sem_prop.value);
    }

    while(1)
    {
        OS_TaskDelay(1000);
        OS_printf("TASK 1:   Doing some work: %d\n", (int)counter++);

    }
}

void task_2(void)
{
    uint32             status;
    OS_bin_sem_prop_t  bin_sem_prop;
    int                counter = 0;

    OS_printf("Starting task 2\n");
    OS_TaskRegister();

    OS_printf("TASK 2: Waiting on the semaphore\n");
    status = OS_BinSemTake(bin_sem_id);
    if ( status != OS_SUCCESS )
    {
       OS_printf("TASK 2: Error calling OS_BinSemTake\n");
    }
    else
    {
       status = OS_BinSemGetInfo (bin_sem_id, &bin_sem_prop);
       OS_printf("TASK 2: out of BinSemTake: %d\n",(int)bin_sem_prop.value);
    }

    while(1)
    {
        OS_TaskDelay(1000);
        OS_printf("TASK 2:   Doing some work: %d\n", (int)counter++);

    }
}

void task_3(void)
{
    uint32             status;
    OS_bin_sem_prop_t  bin_sem_prop;
    int                counter = 0;

    OS_printf("Starting task 3\n");
    OS_TaskRegister();

    OS_printf("TASK 3: Waiting on the semaphore\n");
    status = OS_BinSemTake(bin_sem_id);
    if ( status != OS_SUCCESS )
    {
       OS_printf("TASK 3: Error calling OS_BinSemTake\n");
    }
    else
    {
       status = OS_BinSemGetInfo (bin_sem_id, &bin_sem_prop);
       OS_printf("TASK 3: out of BinSemTake: %d\n",(int)bin_sem_prop.value);
    }

    while(1)
    {
        OS_TaskDelay(1000);
        OS_printf("TASK 3:   Doing some work: %d\n", (int)counter++);

    }
}

/*
** Main function
*/
void OS_Application_Startup(void)
{
   uint32 status;
   OS_bin_sem_prop_t  bin_sem_prop;

   OS_API_Init();

   OS_printf("OS Application Startup\n");

   /*
   ** Create the binary semaphore
   */
   status = OS_BinSemCreate( &bin_sem_id, "BinSem1", 1, 0);
   if ( status != OS_SUCCESS )
   {
      OS_printf("Error creating Binary Sem\n");
   }
   else
   {
      status = OS_BinSemGetInfo (bin_sem_id, &bin_sem_prop);
      OS_printf("Binary Sem ID = %d, value = %d\n", (int)bin_sem_id, (int)bin_sem_prop.value);
   }

   /*
   ** Take the semaphore so the value is 0 and the next SemTake call should block
   */
   status = OS_BinSemTake(bin_sem_id);
   if ( status != OS_SUCCESS )
   {
      OS_printf("Error calling OS_BinSemTake with bin_sem_id = %d\n",(int)bin_sem_id);
   }
   else
   {
      status = OS_BinSemGetInfo (bin_sem_id, &bin_sem_prop);
      OS_printf("Initial Binary Sem Take: value = %d\n", (int)bin_sem_prop.value);
   }

   /*
   ** Create the tasks
   */
   status = OS_TaskCreate( &task_1_id, "Task 1", task_1, task_1_stack, TASK_STACK_SIZE, TASK_1_PRIORITY, 0);
   if ( status != OS_SUCCESS )
   {
      OS_printf("Error creating Task 1\n");
   }
   else
   {
      OS_printf("Created Task 1\n");
   }

   status = OS_TaskCreate( &task_2_id, "Task 2", task_2, task_2_stack, TASK_STACK_SIZE, TASK_2_PRIORITY, 0);
   if ( status != OS_SUCCESS )
   {
      OS_printf("Error creating Task 2\n");
   }
   else
   {
      OS_printf("Created Task 2\n");
   }
 
   status = OS_TaskCreate( &task_3_id, "Task 3", task_3, task_3_stack, TASK_STACK_SIZE, TASK_3_PRIORITY, 0);
   if ( status != OS_SUCCESS )
   {
      OS_printf("Error creating Task 3\n");
   }
   else
   {
      OS_printf("Created Task 3\n");
   }

   /* 
   ** Delay, then release the semaphore
   */
   OS_TaskDelay(2000); 

   status = OS_BinSemFlush(bin_sem_id);

   OS_printf("Main done!\n");

}

