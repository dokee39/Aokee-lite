#include "compatible.h"
#include <memory>
#include "config.hpp"
#include "robot_ctrl.hpp"
#include "double_wheel_balance_chassis.hpp"

void *new_RobotCtrl()
{
    return (void *)(new Robot::RobotCtrl());
}

void imu_task(void *arg)
{
    Robot::RobotCtrl &robot = *static_cast<Robot::RobotCtrl *>(arg);
    std::static_pointer_cast<Chassis::DoubleWheelBalanceChassis>(robot.chassis)->imu.task(arg);
}

