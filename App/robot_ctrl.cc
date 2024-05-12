#include "robot_ctrl.hpp"
#include "double_wheel_balance_chassis.hpp"

namespace Robot
{
    RobotConfig::RobotConfig(const Motor::PwmDcMotorImpConfig &chassis_motor_imp_left, 
                             const Motor::PwmDcMotorConfig &chassis_motor_left, 
                             const Motor::PwmDcMotorImpConfig &chassis_motor_imp_right, 
                             const Motor::PwmDcMotorConfig &chassis_motor_right)
        : chassis_motor_imp_left(chassis_motor_imp_left),
          chassis_motor_left(chassis_motor_left),
          chassis_motor_imp_right(chassis_motor_imp_right),
          chassis_motor_right(chassis_motor_right)
    {
        
    }
    
    RobotCtrl::RobotCtrl(const RobotConfig &config)
        : chassis(config.chassis_motor_imp_left, config.chassis_motor_left, config.chassis_motor_imp_right, config.chassis_motor_right)
    {
#warning "todo"
        
    }
}

