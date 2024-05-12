#pragma once

#include <strings.h>
#include "double_wheel_balance_chassis.hpp"
#include "pwm_dc_motor.hpp"

namespace Robot
{
    struct RobotConfig
    {
        explicit RobotConfig(const Motor::PwmDcMotorImpConfig &chassis_motor_imp_left, 
                             const Motor::PwmDcMotorConfig &chassis_motor_left, 
                             const Motor::PwmDcMotorImpConfig &chassis_motor_imp_right, 
                             const Motor::PwmDcMotorConfig &chassis_motor_right);
        ~RobotConfig() = default;

        const Motor::PwmDcMotorImpConfig &chassis_motor_imp_left;
        const Motor::PwmDcMotorConfig &chassis_motor_left;
        const Motor::PwmDcMotorImpConfig &chassis_motor_imp_right;
        const Motor::PwmDcMotorConfig &chassis_motor_right;
    };
    
    class RobotCtrl
    {
    public:
        explicit RobotCtrl(const RobotConfig & config);
        ~RobotCtrl() = default;

        Chassis::DoubleWheelBalanceChassis chassis;
        
    private:
        RobotCtrl() = delete; // must init
        RobotCtrl(const RobotCtrl &) = delete; // cannot copy
        RobotCtrl &operator=(const RobotCtrl &) = delete; // cannot copu
        
    };
}
