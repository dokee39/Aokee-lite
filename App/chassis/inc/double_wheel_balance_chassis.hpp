#pragma once

#include <cstdint>
#include <vector>

#include "chassis_base.hpp"
#include "pwm_dc_motor.hpp"
#include "imu.hpp"

namespace Chassis
{
    struct DoubleWheelBalanceChassisConfig
    {
        explicit DoubleWheelBalanceChassisConfig() = default;
        ~DoubleWheelBalanceChassisConfig() = default;

    };

    class DoubleWheelBalanceChassis : public DoubleWheelBalanceChassisConfig, public ChassisBase
    {
    public:
        explicit DoubleWheelBalanceChassis() = default;
        ~DoubleWheelBalanceChassis() = default;
        
#warning "init?"
        void init() override;
        
        Dev::Imu imu;
        std::vector<Motor::PwmDcMotor> motors;

    private:
        const uint32_t MOTOR_NUM = 2;

        void update_state() override;
        void ctrl_val_calc() override;
        void ctrl() override;
        void task_delay_until() const override;

    };
}
