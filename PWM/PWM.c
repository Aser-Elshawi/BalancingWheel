#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "PWM.h"



// Initialize PWM on PB5 (T1CCP1)
void PWM_Init(uint32_t freq) {
    uint32_t loadValue;

    SYSCTL_RCGCGPIO_R |= 0x02;  // Enable clock for Port B
    SYSCTL_RCGCTIMER_R |= 0x02; // Enable clock for Timer1
    while ((SYSCTL_PRGPIO_R & 0x02) == 0); // Wait for Port B to be ready

    // Configure PB5 as T1CCP1
    GPIO_PORTB_AFSEL_R |= 0x20;  // Enable alternate function on PB5
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFF0FFFFF) | 0x00700000; // Assign T1CCP1 to PB5
    GPIO_PORTB_DEN_R |= 0x20;    // Enable digital functionality on PB5

    // Configure Timer1 for PWM mode
    TIMER1_CTL_R &= ~0x0100;     // Disable Timer1B during setup
    TIMER1_CFG_R = 0x04;         // Configure as 16-bit timer
    TIMER1_TBMR_R = 0x0A;        // PWM mode, periodic timer mode

    // Calculate and set the load value
    loadValue = (16000000 / freq) - 1; // Assuming 16 MHz system clock
    TIMER1_TBILR_R = loadValue;  // Set the interval load value
    TIMER1_TBPR_R = (loadValue >> 16); // Set the prescale value for higher bits

    TIMER1_TBMATCHR_R = loadValue; // Start with 0% duty cycle
    TIMER1_TBPMR_R = (loadValue >> 16);

    TIMER1_CTL_R |= 0x0100;      // Enable Timer1B
}

// Set duty cycle for the PWM
void PWM_SetDutyCycle(uint8_t dutyCycle) {
    uint32_t matchValue;
    if(dutyCycle > 100){
        dutyCycle = 0;
    }
    uint32_t loadValue = (TIMER1_TBILR_R | (TIMER1_TBPR_R << 16)) + 1;

    // Calculate the match value based on the duty cycle
    matchValue = loadValue - (loadValue * dutyCycle / 100);

    TIMER1_TBMATCHR_R = matchValue & 0xFFFF; // Set lower 16 bits
    TIMER1_TBPMR_R = (matchValue >> 16);    // Set higher bits
}
