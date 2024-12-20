/*
 * I2Cdev.cpp
 *
 *  Created on: Dec 11, 2024
 *      Author: aser_
 */


#include <stdint.h>
#include "I2C_IMU.h" // Header for I2C functions
#include "I2Cdev.hpp"

#include <Services/I2CDev/I2Cdev.hpp>

#include "I2C_IMU.h" // Include your hardware-specific I2C functions

void I2Cdev::writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data) {
    I2C_IMU_Write(devAddr, regAddr, data);
}

void I2Cdev::writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) {
    for (uint8_t i = 0; i < length; i++) {
        I2C_IMU_Write(devAddr, regAddr + i, data[i]);
    }
}

void I2Cdev::writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {
    uint8_t b;
    readByte(devAddr, regAddr, &b); // Read current register value
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    data <<= (bitStart - length + 1); // Align data
    data &= mask; // Mask the data
    b &= ~mask; // Clear bits
    b |= data; // Set new bits
    writeByte(devAddr, regAddr, b);
}

void I2Cdev::writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data) {
    uint8_t b;
    readByte(devAddr, regAddr, &b); // Read current register value
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    writeByte(devAddr, regAddr, b);
}
void I2Cdev::writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data) {
    // Write the MSB (most significant byte) first
    I2C_IMU_Write(devAddr, regAddr, (data >> 8) & 0xFF);

    // Write the LSB (least significant byte) second
    I2C_IMU_Write(devAddr, regAddr + 1, data & 0xFF);
}

uint8_t I2Cdev::readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data) {
    *data = I2C_IMU_Read(devAddr, regAddr);
    return 1; // Success
}

uint8_t I2Cdev::readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) {
    for (uint8_t i = 0; i < length; i++) {
        data[i] = I2C_IMU_Read(devAddr, regAddr + i);
    }
    return length; // Number of bytes read
}

uint8_t I2Cdev::readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data) {
    uint8_t b;
    readByte(devAddr, regAddr, &b); // Read current register value
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    b &= mask; // Apply mask
    b >>= (bitStart - length + 1); // Align to LSB
    *data = b;
    return 1; // Success
}

uint8_t I2Cdev::readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data) {
    uint8_t b;
    readByte(devAddr, regAddr, &b); // Read current register value
    *data = b & (1 << bitNum);
    return 1; // Success
}


