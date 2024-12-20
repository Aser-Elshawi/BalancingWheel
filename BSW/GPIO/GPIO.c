/*******************************************************************************
 * Title                 :   ****MODULE_TITLE*****
 * Module                :   GPIO
 * Filename              :   GPIO.c
 * Author                :   Eslam Akrm
 * Origin Date           :   Apr 20, 2022
 * Version               :   1.0.0
 * Compiler              :   Texas Instruments v20.2.6 LTS
 * Target                :   TM4C123GH6PM
 * Notes                 :   None
 *******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
 *
 *    Date         Software Version    Initials     Description
 *  Apr 20, 2022             1.0.0       Eslam     Module Created.
 *
 *******************************************************************************/

/******************************************************************************
 * Include Standard C Header files
 *******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
/******************************************************************************
 * Include Compiler Libraries Header files
 *******************************************************************************/
#include <driverlib/sysctl.h>
#include <inc/hw_memmap.h>
#include <driverlib/gpio.h>
/******************************************************************************
 * Include any service file that will be used
 *******************************************************************************/
//#include "SERVICES/STD_TYPES/STD_TYPES.h"
/******************************************************************************
 * Include Module.h file
 *******************************************************************************/
#include "GPIO.h"
/******************************************************************************
 * Include Module_cfg.h file
 *******************************************************************************/

/******************************************************************************
 * Include Module_Private.h file
 *******************************************************************************/
#define GPIO_PRIVATE_ENABLE /* Private header file guard */

#undef  GPIO_PRIVATE_ENABLE /* Private header file guard */

/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/

/******************************************************************************
 * Module Typedefs
 *******************************************************************************/

/******************************************************************************
 * Module Variable Definitions
 *******************************************************************************/

/************************************/
/* Public (Shared) Global Variables */
/************************************/

/*************************************/
/* Private (Static) Global Variables */
/*************************************/
/* constant array holding SYSCTLPERGPIO base address needed to initialize the GPIO system clock
 * input = number of the gpio(0->7)
 * */
const uint32_t gpio_get_sysctlPerGpio[6]=
{
 SYSCTL_PERIPH_GPIOA,SYSCTL_PERIPH_GPIOB,SYSCTL_PERIPH_GPIOC,SYSCTL_PERIPH_GPIOD,SYSCTL_PERIPH_GPIOE,SYSCTL_PERIPH_GPIOF
};
/******************************************************************************
 * Function Definitions
 *******************************************************************************/

/*****************************/
/* Public (Shared) Functions */
/*****************************/

/******************************************************************************
 * Function name : GPIO_Init
 * Parameters (in): None
 * Parameters (in/out): None
 * Parameters (out): None
 * Return value: None
 * Function description : None
 *  ----------------------
 *  - HISTORY OF CHANGES -
 *  ----------------------
 *    Date         Software Version    Initials     Description
 *  Apr 20, 2022        1.0.0           Eslam       Module Created.
 *
 * Notes : None
 *******************************************************************************/
void GPIO_configure(GPIO_port_t port, GPIO_pin_t pin, GPIO_pinDirection_t direction){

    uint8_t port_num = 0;
    switch (port)
    {
        case GPIO_port_A:
            port_num = 0;
            break;
        case GPIO_port_B:
            port_num = 1;
            break;
        case GPIO_port_C:
            port_num = 2;
            break;
        case GPIO_port_D:
            port_num = 3;
            break;
        case GPIO_port_E:
            port_num = 4;
            break;
        case GPIO_port_F:
            port_num = 5;
            break;
        default:
            break;
    }
    SysCtlPeripheralEnable(gpio_get_sysctlPerGpio[port_num]);
    while(!SysCtlPeripheralReady(gpio_get_sysctlPerGpio[port_num]));

    switch (direction) {
    case GPIO_pinDirection_input:

        GPIOPinTypeGPIOInput(port, pin);

        break;
    case GPIO_pinDirection_output:
        GPIOPinTypeGPIOOutput(port, pin);
        break;
    default:
        break;
    }

}
void GPIO_set(GPIO_port_t port, GPIO_pin_t pin){
    GPIOPinWrite(port, pin, pin);
}
void GPIO_clear(GPIO_port_t port, GPIO_pin_t pin){
    GPIOPinWrite(port, pin, (uint8_t)0);
}
void GPIO_toggle(GPIO_port_t port, GPIO_pin_t pin){
    int32_t i32Val;
    i32Val = GPIOPinRead(port, pin);
    if((uint8_t)i32Val){
        GPIOPinWrite(port, pin, (uint8_t)0);
    }else{
        GPIOPinWrite(port, pin, pin);
    }
}
STD_inputReading_t GPIO_read(GPIO_port_t port, GPIO_pin_t pin){

    STD_inputReading_t ret_value;

    if(GPIOPinRead(port, pin) & pin){
        ret_value = HIGH;
    }else{
        ret_value = LOW;
    }
    return ret_value;
}

void GPIO_intConfigure(GPIO_port_t port, GPIO_pin_t pin, GPIO_int_detectionType_t detection, void (*intHandler)(void)){
    GPIOIntTypeSet(port, pin, detection);
    GPIOIntRegisterPin(port, pin, intHandler);
}
void GPIO_intEnable(GPIO_port_t port, GPIO_pin_t pin){
    GPIOIntEnable(port, pin);
}
void GPIO_intDisable(GPIO_port_t port, GPIO_pin_t pin){
    GPIOIntDisable(port, pin);
}
void GPIO_enablePullUp(GPIO_port_t port, GPIO_pin_t pin){
    GPIOPadConfigSet(port, pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}
/******************************/
/* Private (Static) Functions */
/******************************/

/*************** END OF FUNCTIONS ***************************************************************************/
