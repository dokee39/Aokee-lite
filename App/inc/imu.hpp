#pragma once

#include "mpu6050.h"
#include "i2c.h"
#include "FreeRTOS.h"
#include "portmacro.h"
#include "sw_i2c.h"
#include "task.h"

extern sw_i2c_t sw_i2c1;

namespace Dev {
class Imu {
public:
    explicit Imu() = default;
    ~Imu() = default;

    float gyro[3] = { 0.0f };
    float gyro_offset[3] = { 0.017172f, 0.015918f, -0.007618f };
    float acc[3] = { 0.0f };
    float angle[3] = { 0.0f }; // roll pitch yaw
    float temp = 0.0f;

    [[noreturn]] void task(void* arg);

private:
    sw_i2c_t& sw_i2c_imu = sw_i2c1;

    TickType_t xLastWakeTime;
    MPU6050_t mpu6050;
    float quat[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    const float GYRO_OFFSET_MAX = 1.0f;
    uint32_t cali_time_count = 0;
    const uint32_t CALI_TIME = 20000;
    
    void calc_angle();
    void cali_hook();
};
} // namespace Dev
