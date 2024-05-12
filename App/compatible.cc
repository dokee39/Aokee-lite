#include "compatible.h"
#include "config.hpp"
#include "robot_ctrl.hpp"

void *new_RobotCtrl()
{
    Robot::RobotConfig robot_config(CONFIG::CHASSIS_MOTOR_IMP_LEFT, 
                                    CONFIG::CHASSIS_MOTOR, 
                                    CONFIG::CHASSIS_MOTOR_IMP_RIGHT, 
                                    CONFIG::CHASSIS_MOTOR);
    return static_cast<void *>(new Robot::RobotCtrl(robot_config));
}


void imu_task(void *arg)
{
    Robot::RobotCtrl &robot = *static_cast<Robot::RobotCtrl *>(arg);
    robot.chassis.imu.task(arg);
}

