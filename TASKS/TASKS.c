/*
 * TASKS.c
 *
 *  Created on: Dec 16, 2021
 *      Author: asere
 */

#include <APP/BL/Blink.hpp>

#include <stdint.h>
#include <stdbool.h>
#include <APP/PRINT/print.hpp>
#include <APP/IMU/IMU.hpp>

#include "OS/OS.h"
//#include "SERVICES/STD_TYPES/STD_TYPES.h"
//#include "SERVICES/DEBUG_PORT/DEBUG_PORT.h"
//#include "BSW/UART/UART.h"
//#include "BSW/GPIO/GPIO.h"
//#include "BSW/TIMER/TIMER.h"
//#include "BSW/TIMER_AL/TIMER.h"
//#include "BSW/EEPROM/EEPROM.h"
#include "TASKS/TASKS.h"

#include <driverlib/sysctl.h>
#include <inc/hw_memmap.h>
#include <driverlib/gpio.h>



void TASKS_Init(){

    OS_Init();
    //Blink_init();
    IMU_Init();

}

void TASKS_20ms()
{

}

void TASKS_5ms()
{


}

void TASKS_1Sec()
{
    Blink_cyclic();
}



void TASKS_1ms()
{
    //IMU_Cyclic();
    print_Cyclic();

}

void TASKS_100uS(){


}
void TASKS_3min(){
    //EEPROM_cyclic10min();
}
