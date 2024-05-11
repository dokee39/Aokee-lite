#include "compatible.h"
#include "robot_ctrl.hpp"

void *new_RobotCtrl()
{
    return static_cast<void *>(new Robot::RobotCtrl());
}


void imu_task(void *arg)
{
    Robot::RobotCtrl &robot = *static_cast<Robot::RobotCtrl *>(arg);
    robot.chassis.imu.task(arg);
}

