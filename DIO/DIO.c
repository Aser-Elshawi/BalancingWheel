/*
 * DIO.c
 *
 *  Created on: Dec 4, 2024
 *      Author: aser_
 */
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

// Initialize PB1 as a digital output
void PinPB1_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x02;          // Enable clock for Port B
    while ((SYSCTL_PRGPIO_R & 0x02) == 0); // Wait for Port B to be ready

    GPIO_PORTB_DIR_R |= 0x02;           // Set PB1 as output
    GPIO_PORTB_DEN_R |= 0x02;           // Enable digital functionality on PB1
}

// Function to set PB1 HIGH or LOW
void PinPB1_Set(bool state) {
    if (state) {
        GPIO_PORTB_DATA_R |= 0x02;      // Set PB1 HIGH
    } else {
        GPIO_PORTB_DATA_R &= ~0x02;     // Set PB1 LOW
    }
}
