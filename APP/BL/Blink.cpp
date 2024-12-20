/*
 * Blink.c
 *
 *  Created on: Dec 7, 2024
 *      Author: aser_
 */
#include <stdint.h>
#include <stdbool.h>
/******************************************************************************
 * Include Compiler Libraries Header files
 *******************************************************************************/
#include <driverlib/sysctl.h>
#include <inc/hw_memmap.h>
#include <driverlib/gpio.h>
#include "../GPIO/GPIO.h"
#include "Blink.hpp"
void Blink_init(void){

    GPIO_configure(GPIO_port_D, GPIO_pin_2, GPIO_pinDirection_output); //type input = False , output = true
    GPIO_configure(GPIO_port_F, GPIO_pin_3, GPIO_pinDirection_output); //type input = False , output = true
    GPIO_configure(GPIO_port_F, GPIO_pin_2, GPIO_pinDirection_output); //type input = False , output = true
    GPIO_configure(GPIO_port_F, GPIO_pin_1, GPIO_pinDirection_output); //type input = False , output = true
}

void Blink_cyclic(void){
    static uint8_t tog=1;
    GPIO_toggle(GPIO_port_D, GPIO_pin_2);
        if (tog & 0x01)
            GPIO_set(GPIO_port_F, GPIO_pin_3); // Green
        else
            GPIO_clear(GPIO_port_F, GPIO_pin_3); // Green
        if (tog & 0x02)
            GPIO_set(GPIO_port_F, GPIO_pin_2); // Blue
        else
            GPIO_clear(GPIO_port_F, GPIO_pin_2); // Blue
        if (tog & 0x04)
            GPIO_set(GPIO_port_F, GPIO_pin_1); // Red
        else
            GPIO_clear(GPIO_port_F, GPIO_pin_1); // Red
        tog = (tog>=7)?0:tog+1;
}
