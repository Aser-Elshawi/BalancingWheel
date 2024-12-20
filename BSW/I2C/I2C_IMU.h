/*
 * I2C.h
 *
 *  Created on: Dec 11, 2024
 *      Author: aser_
 */

#ifndef BSW_I2C_I2C_IMU_H_
#define BSW_I2C_I2C_IMU_H_

#ifdef __cplusplus
extern "C" {
#endif

void I2C_IMU_Init(void);
void I2C_IMU_Write(uint8_t deviceAddr, uint8_t regAddr, uint8_t data);
uint8_t I2C_IMU_Read(uint8_t deviceAddr, uint8_t regAddr) ;


#ifdef __cplusplus
}
#endif
#endif /* BSW_I2C_I2C_IMU_H_ */

