/*
 * OS.c
 *
 *  Created on: Jun 29, 2021
 *      Author: 
 */


#include <stdint.h>
#include <stdbool.h>
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "OS.h"



typedef struct task_s
{
    taskPtr_t taskPointer;
    uint8_t task_id;
    uint32_t task_time;
    uint32_t task_counter;
    uint8_t state;
    //max task time
} task_t;



task_t tasks[TASK_MAX]; // Max 5 tasks in this mini OS
volatile uint32_t millis = 0;

void SycTickInt()
{
    OS_handlerCallBack();
    millis++;
}

//This waits the number of miliseconds specified by parameter
void delay(uint32_t time_ms)
{
    uint32_t temp = millis;
    while ((millis - temp) < time_ms)
    {
    }
}


// init OS timer
void OS_Init(void)
{
    SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_SYSDIV_2_5 | SYSCTL_XTAL_16MHZ );
    SysTickPeriodSet(8000);
    SysTickIntRegister(SycTickInt);
    SysTickIntEnable();
    SysTickEnable();
}
void OS_handlerCallBack(void){
    uint8_t i;
    for(i = 0;i<TASK_MAX;i++){
        if((tasks[i].taskPointer != NULL)&&(tasks[i].state == IDLE)) // check if task exist
        {
            if(tasks[i].task_counter >= (tasks[i].task_time-1)){ // time expired
                tasks[i].state = RUN; //allow to run
                tasks[i].task_counter = 0;
            }else{
                tasks[i].task_counter++;
            }


        }
        //if all tasks is idle && all blocked(not in run 'allow to run'){ put processor in sleep mode }

        // if task_counter >= task_max_time { terminate the task }
    }

}
void OS_ServeOS(void)
{
    uint8_t i;
    for(i = 0;i<TASK_MAX;i++){
        if(tasks[i].taskPointer != NULL) // check if task exist
        {
            if(tasks[i].state == RUN){ // time expired
                tasks[i].state = RUNNING;
                tasks[i].taskPointer();
                tasks[i].state = IDLE;
            }
        }
    }
}
// define the TASK_TIME is multiples of 100us
OS_State_t OS_CreateNewTask(taskPtr_t task, uint32_t TASK_TIME)
{
    OS_State_t ret;
    static uint8_t task_indx=0;
    //  OStimer_Suspened();
    if(task_indx < TASK_MAX)
    {
        tasks[task_indx].taskPointer = task;
        tasks[task_indx].task_time = TASK_TIME;
        tasks[task_indx].task_id = task_indx;
        tasks[task_indx].task_counter = 0;
        tasks[task_indx].state = IDLE;
        ret = OS_TASK_CREATED;
    }else{
        ret = OS_MAX_TASK_REACHED;
    }

    task_indx++;
    //  OStimer_Resume();
    return ret;
}

