#pragma once

#include <strings.h>
#include "double_wheel_balance_chassis.hpp"
#include "pwm_dc_motor.hpp"

namespace Robot
{
    class RobotCtrl
    {
    public:
        explicit RobotCtrl();
        ~RobotCtrl() = default;

        Chassis::DoubleWheelBalanceChassis chassis;
        
    };
}
