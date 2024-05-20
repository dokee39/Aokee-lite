#include <memory>

#include "compatible.h"
#include "FreeRTOS.h"
#include "motor_base.hpp"
#include "task.h"
#include "config.hpp"
#include "robot_ctrl.hpp"
#include "double_wheel_balance_chassis.hpp"

static void imu_task(void *arg);
static void chassis_task(void *arg);

void main_entry(void)
{
    TaskHandle_t xCreatedImuTask;
    TaskHandle_t xCreatedChassisTask;

    std::shared_ptr<Motor::PwmDcMotorImp> chassis_motor_left(
        std::make_shared<Motor::PwmDcMotorImp>(
            CONFIG::CHASSIS_MOTOR_IMP_LEFT,
            CONFIG::CHASSIS_MOTOR
        )
    );
    std::shared_ptr<Motor::PwmDcMotorImp> chassis_motor_right(
        std::make_shared<Motor::PwmDcMotorImp>(
            CONFIG::CHASSIS_MOTOR_IMP_RIGHT,
            CONFIG::CHASSIS_MOTOR
        )
    );

    std::shared_ptr<Chassis::DoubleWheelBalanceChassis> chassis(
        std::make_shared<Chassis::DoubleWheelBalanceChassis>(
            std::static_pointer_cast<Motor::MotorBase>(chassis_motor_left),
            std::static_pointer_cast<Motor::MotorBase>(chassis_motor_right)
        )
    );

    Robot::RobotCtrl robot(chassis);

    xTaskCreate(imu_task, "imu task", configMINIMAL_STACK_SIZE * 8, static_cast<void *>(&robot), (tskIDLE_PRIORITY + 6), &xCreatedImuTask);
    xTaskCreate(chassis_task, "chassis task", configMINIMAL_STACK_SIZE * 8, static_cast<void *>(&robot), (tskIDLE_PRIORITY + 6), &xCreatedChassisTask);
    
    /* Start scheduler */
    vTaskStartScheduler();
}

static void imu_task(void* arg)
{
    Robot::RobotCtrl &robot(*static_cast<Robot::RobotCtrl *>(arg));
    std::static_pointer_cast<Chassis::DoubleWheelBalanceChassis>(robot.chassis)->imu.task(NULL);
}

static void chassis_task(void *arg)
{
    Robot::RobotCtrl &robot(*static_cast<Robot::RobotCtrl *>(arg));
    robot.chassis->task(NULL);
}
