#pragma once

namespace Dev
{
    class Imu
    {
    public:
        explicit Imu() = default;
        ~Imu() = default;
        
        float gyro[3] = {0.0f};
        float acc[3] = {0.0f};
        float quat[4] = {1.0f, 0.0f, 0.0f, 0.0f};
        float angle[3] = {0.0f}; // yaw pitch roll
        float temp = 0.0f;

        [[noreturn]] void task(void *arg);
        void calc_angle();

    };
}


