/*******************************************************************************
 * Title                 :   ****MODULE_TITLE*****
 * Module                :   GPIO
 * Filename              :   GPIO.h
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
 *  Apr 20, 2022             1.0.0           Eslam       Module Created.
 *
 *******************************************************************************/

#ifndef BSW_GPIO_GPIO_H_
#define BSW_GPIO_GPIO_H_

/******************************************************************************
 * Preprocessor Macros (Definitions and static Configurations)
 *******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* Macros (Functions)
*******************************************************************************/
/* translates from gpio base address to sysCtl peripheral address (works only from GPIOA to GPIOH)*/
#define gpioBaseAdd_TO_sysBaseAdd(portAdd) ( 0xF0000800 | (((portAdd>>12)&0x0000000F)-0x00000008) )
/******************************************************************************
 * User-defined Types
 *******************************************************************************/
/*
 * Description: Write Here the Description of your defined type
 * */

typedef enum STD_inputReading_e{
    HIGH = true,
    LOW = false
}STD_inputReading_t;
typedef enum GPIO_pinDirection_e{
    GPIO_pinDirection_input,
    GPIO_pinDirection_output
}GPIO_pinDirection_t;

typedef enum GPIO_port_e{
    GPIO_port_A = GPIO_PORTA_BASE,
    GPIO_port_B = GPIO_PORTB_BASE,
    GPIO_port_C = GPIO_PORTC_BASE,
    GPIO_port_D = GPIO_PORTD_BASE,
    GPIO_port_E = GPIO_PORTE_BASE,
    GPIO_port_F = GPIO_PORTF_BASE
}GPIO_port_t;


typedef enum GPIO_pin_e{
    GPIO_pin_0 = GPIO_PIN_0,
    GPIO_pin_1 = GPIO_PIN_1,
    GPIO_pin_2 = GPIO_PIN_2,
    GPIO_pin_3 = GPIO_PIN_3,
    GPIO_pin_4 = GPIO_PIN_4,
    GPIO_pin_5 = GPIO_PIN_5,
    GPIO_pin_6 = GPIO_PIN_6,
    GPIO_pin_7 = GPIO_PIN_7
}GPIO_pin_t;


typedef enum GPIO_int_detectionType_e{
    GPIO_int_detectionType_falling = GPIO_FALLING_EDGE,
    GPIO_int_detectionType_rising = GPIO_RISING_EDGE,
    GPIO_int_detectionType_both = GPIO_BOTH_EDGES,
    GPIO_int_detectionType_low = GPIO_LOW_LEVEL,
    GPIO_int_detectionType_high = GPIO_HIGH_LEVEL
}GPIO_int_detectionType_t;
/******************************************************************************
* Extern for Public Global Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

void GPIO_configure(GPIO_port_t port, GPIO_pin_t pin, GPIO_pinDirection_t direction); //type input = False , output = true
void GPIO_set(GPIO_port_t port, GPIO_pin_t pin);
void GPIO_clear(GPIO_port_t port, GPIO_pin_t pin);
void GPIO_toggle(GPIO_port_t port, GPIO_pin_t pin);
STD_inputReading_t GPIO_read(GPIO_port_t port, GPIO_pin_t pin);
void GPIO_intConfigure(GPIO_port_t port, GPIO_pin_t pin, GPIO_int_detectionType_t detection, void (*intHandler)(void));
void GPIO_intEnable(GPIO_port_t port, GPIO_pin_t pin);
void GPIO_intDisable(GPIO_port_t port, GPIO_pin_t pin);
void GPIO_enablePullUp(GPIO_port_t port, GPIO_pin_t pin);

#ifdef __cplusplus
}
#endif

#endif /* BSW_GPIO_GPIO_H_ */

/*** End of File **************************************************************/
