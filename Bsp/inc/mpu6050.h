/*
 * mpu6050.h
 *
 *  Created on: Nov 13, 2019
 *      Author: Bulanov Konstantin
 */

#ifndef INC_GY521_H_
#define INC_GY521_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c.h"
#include "sw_i2c.h"
#include <stdint.h>

// MPU6050 structure
typedef struct {
    sw_i2c_t* sw_i2c;

    int16_t Accel_X_RAW;
    int16_t Accel_Y_RAW;
    int16_t Accel_Z_RAW;
    float Ax;
    float Ay;
    float Az;

    int16_t Gyro_X_RAW;
    int16_t Gyro_Y_RAW;
    int16_t Gyro_Z_RAW;
    float Gx;
    float Gy;
    float Gz;

    float Temperature;
} MPU6050_t;

uint8_t MPU6050_Init(MPU6050_t* mpu6050, sw_i2c_t* sw_i2c);
void MPU6050_Read_Accel(MPU6050_t* mpu6050);
void MPU6050_Read_Gyro(MPU6050_t* mpu6050);
void MPU6050_Read_Temp(MPU6050_t* mpu6050);
void MPU6050_Read_All(MPU6050_t* mpu6050);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* INC_GY521_H_ */
