#pragma once

#include <memory>
#include "chassis_base.hpp"
#include "imu.hpp"
#include "motor_base.hpp"

namespace Chassis
{
    class DoubleWheelBalanceChassis : public ChassisBase
    {
    public:
        explicit DoubleWheelBalanceChassis(const std::shared_ptr<Motor::MotorBase> motor_left, 
                                           const std::shared_ptr<Motor::MotorBase> motor_right);
        ~DoubleWheelBalanceChassis() override = default;

        void init() override;

        Dev::Imu imu;

    private:
        DoubleWheelBalanceChassis() = delete; // must init

        void update_state() override;
        void ctrl_val_calc() override;
        void ctrl() override;
        void task_delay_until() const override;

    };
}

