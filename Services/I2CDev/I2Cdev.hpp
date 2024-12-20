/*
 * I2Cdev.hpp
 *
 *  Created on: Dec 11, 2024
 *      Author: aser_
 */

#ifndef SERVICES_I2CDEV_I2CDEV_HPP_
#define SERVICES_I2CDEV_I2CDEV_HPP_


#ifndef I2CDEV_H
#define I2CDEV_H

// I2Cdev Class Definition
class I2Cdev {
public:
    I2Cdev(){
        I2C_IMU_Init();
    }
    /**
     * Write a single byte to a register
     * @param devAddr I2C device address
     * @param regAddr Register address
     * @param data Byte of data to write
     */
    static void writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);

    /**
     * Write multiple bytes to a register
     * @param devAddr I2C device address
     * @param regAddr Starting register address
     * @param length Number of bytes to write
     * @param data Array of data bytes to write
     */
    static void writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);

    /**
     * Read a single byte from a register
     * @param devAddr I2C device address
     * @param regAddr Register address
     * @param data Pointer to store the read byte
     * @return 1 if successful, 0 otherwise
     */
    static uint8_t readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data);

    /**
     * Read multiple bytes from a register
     * @param devAddr I2C device address
     * @param regAddr Starting register address
     * @param length Number of bytes to read
     * @param data Pointer to store the read bytes
     * @return Number of bytes read if successful, 0 otherwise
     */
    static uint8_t readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);

    /**
     * Write a single bit to a register
     * @param devAddr I2C device address
     * @param regAddr Register address
     * @param bitNum Bit number (0-7) to write
     * @param data Value to write (0 or 1)
     */
    static void writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);

    /**
     * Write multiple bits to a register
     * @param devAddr I2C device address
     * @param regAddr Register address
     * @param bitStart Starting bit (0-7)
     * @param length Number of bits to write
     * @param data Value to write (right-aligned)
     */
    static void writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);




    static void writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data);

    /**
     * Read a single bit from a register
     * @param devAddr I2C device address
     * @param regAddr Register address
     * @param bitNum Bit number (0-7) to read
     * @param data Pointer to store the bit value
     * @return 1 if successful, 0 otherwise
     */
    static uint8_t readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data);

    /**
     * Read multiple bits from a register
     * @param devAddr I2C device address
     * @param regAddr Register address
     * @param bitStart Starting bit (0-7)
     * @param length Number of bits to read
     * @param data Pointer to store the read bits (right-aligned)
     * @return 1 if successful, 0 otherwise
     */
    static uint8_t readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data);
};

#endif // I2CDEV_H



#endif /* SERVICES_I2CDEV_I2CDEV_HPP_ */
