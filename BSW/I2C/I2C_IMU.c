/*
 * I2C.c
 *
 *  Created on: Dec 11, 2024
 *      Author: aser_
 */




#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/i2c.h"

#include <BSW/I2C/I2C_IMU.h>

void I2C_IMU_Init(void) {
    // Enable the peripherals for I2C3 and GPIO Port D
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // Configure the pins for I2C (PD0 - SCL, PD1 - SDA)
    GPIOPinConfigure(GPIO_PD0_I2C3SCL);
    GPIOPinConfigure(GPIO_PD1_I2C3SDA);
    GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_1);       // Configure PD1 as SDA
    GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);    // Configure PD0 as SCL

    // Initialize the I2C3 Master module
    I2CMasterInitExpClk(I2C3_BASE, SysCtlClockGet(), true); // true for 400kHz, false for 100kHz
}

void I2C_IMU_Write(uint8_t deviceAddr, uint8_t regAddr, uint8_t data) {
    // Specify the slave device address
    I2CMasterSlaveAddrSet(I2C3_BASE, deviceAddr, false); // false for write

    // Set the register to be written to
    I2CMasterDataPut(I2C3_BASE, regAddr);
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while (I2CMasterBusy(I2C3_BASE));

    // Write the data to the register
    I2CMasterDataPut(I2C3_BASE, data);
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while (I2CMasterBusy(I2C3_BASE));
}
uint8_t I2C_IMU_Read(uint8_t deviceAddr, uint8_t regAddr) {
    uint8_t data;

    // Specify the slave device address
    I2CMasterSlaveAddrSet(I2C3_BASE, deviceAddr, false); // false for write

    // Set the register to be read
    I2CMasterDataPut(I2C3_BASE, regAddr);
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    while (I2CMasterBusy(I2C3_BASE));

    // Set the slave address to read
    I2CMasterSlaveAddrSet(I2C3_BASE, deviceAddr, true); // true for read

    // Read the data
    I2CMasterControl(I2C3_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
    while (I2CMasterBusy(I2C3_BASE));
    data = I2CMasterDataGet(I2C3_BASE);

    return data;
}


