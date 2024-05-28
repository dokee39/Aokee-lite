#include <math.h>
#include <stdint.h>
#include "mpu6050.h"
#include "sw_i2c.h"

#define RAD_TO_DEG 57.295779513082320876798154814105f

#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_CONFIG_REG 0x1B
#define GYRO_XOUT_H_REG 0x43

// Setup MPU6050
#define MPU6050_ADDR 0xD0
const float ACCEL_Z_CORRECTOR = 34534.0f;
const float ACCEL_RATIO = 1.0f / (ACCEL_Z_CORRECTOR / 2.0f) * 9.7914f; // 2g, Chongqin
const float GYRO_RATIO = 1.0f / (65535.0f / 2.0f / 250.0f) / RAD_TO_DEG; // 250 dps

uint8_t MPU6050_Init(MPU6050_t *mpu6050, sw_i2c_t* sw_i2c)
{
    uint8_t check;
    uint8_t Data;

    mpu6050->sw_i2c = sw_i2c;

    SW_I2C_initial(mpu6050->sw_i2c);

    // check device ID WHO_AM_I
    SW_I2C_Read_8addr(mpu6050->sw_i2c, MPU6050_ADDR, WHO_AM_I_REG, &check, 1);

    if (check == 104) // 0x68 will be returned by the sensor if everything goes well
    {
        // power management register 0X6B we should write all 0's to wake the sensor up
        Data = 0;
        SW_I2C_Write_8addr(mpu6050->sw_i2c, MPU6050_ADDR, PWR_MGMT_1_REG, &Data, 1);

        // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
        Data = 0x07;
        SW_I2C_Write_8addr(mpu6050->sw_i2c, MPU6050_ADDR, SMPLRT_DIV_REG, &Data, 1);

        // Set accelerometer configuration in ACCEL_CONFIG Register
        // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
        Data = 0x00;
        SW_I2C_Write_8addr(mpu6050->sw_i2c, MPU6050_ADDR, ACCEL_CONFIG_REG, &Data, 1);

        // Set Gyroscopic configuration in GYRO_CONFIG Register
        // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
        Data = 0x00;
        SW_I2C_Write_8addr(mpu6050->sw_i2c, MPU6050_ADDR, GYRO_CONFIG_REG, &Data, 1);

        return 0;
    }
    return 0x80 & check;
}

void MPU6050_Read_Accel(MPU6050_t *mpu6050)
{
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from ACCEL_XOUT_H register

    SW_I2C_Read_8addr(mpu6050->sw_i2c, MPU6050_ADDR, ACCEL_XOUT_H_REG, Rec_Data, 6);

    mpu6050->Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    mpu6050->Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    mpu6050->Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    /*** convert the RAW values into acceleration in 'g'
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 16384.0
         for more details check ACCEL_CONFIG Register              ****/

    mpu6050->Ax = mpu6050->Accel_X_RAW * ACCEL_RATIO;
    mpu6050->Ay = mpu6050->Accel_Y_RAW * ACCEL_RATIO;
    mpu6050->Az = mpu6050->Accel_Z_RAW * ACCEL_RATIO;
}

void MPU6050_Read_Gyro(MPU6050_t *mpu6050)
{
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from GYRO_XOUT_H register
    SW_I2C_Read_8addr(mpu6050->sw_i2c, MPU6050_ADDR, GYRO_XOUT_H_REG, Rec_Data, 6);

    mpu6050->Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    mpu6050->Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    mpu6050->Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    /*** convert the RAW values into dps (�/s)
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 131.0
         for more details check GYRO_CONFIG Register              ****/

    mpu6050->Gx = mpu6050->Gyro_X_RAW * GYRO_RATIO;
    mpu6050->Gy = mpu6050->Gyro_Y_RAW * GYRO_RATIO;
    mpu6050->Gz = mpu6050->Gyro_Z_RAW * GYRO_RATIO;
}

void MPU6050_Read_Temp(MPU6050_t *mpu6050)
{
    uint8_t Rec_Data[2];
    int16_t temp;

    // Read 2 BYTES of data starting from TEMP_OUT_H_REG register
    SW_I2C_Read_8addr(mpu6050->sw_i2c, MPU6050_ADDR, TEMP_OUT_H_REG, Rec_Data, 2);

    temp = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    mpu6050->Temperature = (float)((int16_t)temp / (float)340.0 + (float)36.53);
}

void MPU6050_Read_All(MPU6050_t *mpu6050)
{
    uint8_t Rec_Data[14];
    int16_t temp;

    // Read 14 BYTES of data starting from ACCEL_XOUT_H register

    SW_I2C_Read_8addr(mpu6050->sw_i2c, MPU6050_ADDR, ACCEL_XOUT_H_REG, Rec_Data, 14);

    mpu6050->Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    mpu6050->Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    mpu6050->Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
    temp = (int16_t)(Rec_Data[6] << 8 | Rec_Data[7]);
    mpu6050->Gyro_X_RAW = (int16_t)(Rec_Data[8] << 8 | Rec_Data[9]);
    mpu6050->Gyro_Y_RAW = (int16_t)(Rec_Data[10] << 8 | Rec_Data[11]);
    mpu6050->Gyro_Z_RAW = (int16_t)(Rec_Data[12] << 8 | Rec_Data[13]);

    mpu6050->Ax = mpu6050->Accel_X_RAW * ACCEL_RATIO;
    mpu6050->Ay = mpu6050->Accel_Y_RAW * ACCEL_RATIO;
    mpu6050->Az = mpu6050->Accel_Z_RAW * ACCEL_RATIO;
    mpu6050->Temperature = (float)((int16_t)temp / (float)340.0 + (float)36.53);
    mpu6050->Gx = mpu6050->Gyro_X_RAW * GYRO_RATIO;
    mpu6050->Gy = mpu6050->Gyro_Y_RAW * GYRO_RATIO;
    mpu6050->Gz = mpu6050->Gyro_Z_RAW * GYRO_RATIO;
}

