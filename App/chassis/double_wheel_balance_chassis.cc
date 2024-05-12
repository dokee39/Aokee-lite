#include "double_wheel_balance_chassis.hpp"
#include "pwm_dc_motor_imp.hpp"

namespace Chassis
{
    DoubleWheelBalanceChassis::DoubleWheelBalanceChassis(const Motor::PwmDcMotorImpConfig &config_imp_left, 
                                                         const Motor::PwmDcMotorConfig &config_left, 
                                                         const Motor::PwmDcMotorImpConfig &config_imp_right, 
                                                         const Motor::PwmDcMotorConfig &config_right)
    {
        motor_imps.emplace_back(config_imp_left);
        motor_imps.emplace_back(config_imp_right);

        motors.emplace_back(config_left, motor_imps[0]);
        motors.emplace_back(config_right, motor_imps[1]);
    }


    void DoubleWheelBalanceChassis::init()
    {
        
    }

    void DoubleWheelBalanceChassis::update_state()
    {
        
    }

    void DoubleWheelBalanceChassis::ctrl_val_calc()
    {
        
    }

    void DoubleWheelBalanceChassis::ctrl()
    {
        
    }

    void DoubleWheelBalanceChassis::task_delay_until() const
    {
        
    }

}

