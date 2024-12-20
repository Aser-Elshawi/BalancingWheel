

#include <stdint.h>
#include "OS/OS.h"
#define SYS_CLOCK_HZ 80000000U
#include "TASKS/TASKS.h"


int main(){


    TASKS_Init();
    OS_CreateNewTask(TASKS_20ms, 200);
    OS_CreateNewTask(TASKS_1ms, 10);
    OS_CreateNewTask(TASKS_5ms, 50);
    OS_CreateNewTask(TASKS_1Sec,10000);
    OS_CreateNewTask(TASKS_100uS,1);
    OS_CreateNewTask(TASKS_3min,1800000);



    //Update OS

    while(1) OS_ServeOS();
}


