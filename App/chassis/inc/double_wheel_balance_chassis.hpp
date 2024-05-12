#pragma once

#include <cstdint>
#include <vector>

#include "chassis_base.hpp"
#include "imu.hpp"
#include "pwm_dc_motor_imp.hpp"
#include "pwm_dc_motor.hpp"

namespace Chassis
{
    class DoubleWheelBalanceChassis : public ChassisBase
    {
    public:
        explicit DoubleWheelBalanceChassis(const Motor::PwmDcMotorImpConfig &config_imp_left, 
                                           const Motor::PwmDcMotorConfig &config_left, 
                                           const Motor::PwmDcMotorImpConfig &config_imp_right, 
                                           const Motor::PwmDcMotorConfig &config_right);
        ~DoubleWheelBalanceChassis() = default;
        
#warning "init?"
        void init() override;
        
        Dev::Imu imu;
        std::vector<Motor::PwmDcMotorImp> motor_imps;
        std::vector<Motor::PwmDcMotor<Motor::PwmDcMotorImp>> motors;

    private:
        DoubleWheelBalanceChassis() = delete; // must init
        DoubleWheelBalanceChassis(const DoubleWheelBalanceChassis &) = delete; // cannot copy
        DoubleWheelBalanceChassis &operator=(const DoubleWheelBalanceChassis &) = delete; // cannot copu

        void update_state() override;
        void ctrl_val_calc() override;
        void ctrl() override;
        void task_delay_until() const override;

    };
}
