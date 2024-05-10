#pragma once

#include <cstdint>
#include <memory>

#include "chassis_base.hpp"
#warning "解耦？"
#include "imu.hpp"

namespace Chassis
{
    struct DoubleWheelBalanceChassisConfig
    {
        explicit DoubleWheelBalanceChassisConfig();
        ~DoubleWheelBalanceChassisConfig();

    };

    template <typename T>
    class DoubleWheelBalanceChassis : public DoubleWheelBalanceChassisConfig, public ChassisBase<T>
    {
    public:
        explicit DoubleWheelBalanceChassis();
        ~DoubleWheelBalanceChassis() = default;

    private:
        const uint32_t MOTOR_NUM = 2;

#warning "init?"
        Dev::Imu imu;

        void update_state() override;
        void ctrl_val_calc() override;
        void ctrl() override;
        void task_delay_until() const override;

    };
}
