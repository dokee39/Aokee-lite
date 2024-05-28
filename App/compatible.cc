#include <memory>

#include "FreeRTOS.h"
#include "compatible.h"
#include "config.hpp"
#include "double_wheel_balance_chassis.hpp"
#include "led_task.h"
#include "motor_base.hpp"
#include "robot_ctrl.hpp"
#include "task.h"

static void imu_task(void* arg);
static void chassis_task(void* arg);
static void update_set_task(void* arg);

void main_entry(void) {
    TaskHandle_t xCreatedLedTask;
    TaskHandle_t xCreatedImuTask;
    TaskHandle_t xCreatedChassisTask;
    TaskHandle_t xCreatedUpdateSetTask;

    std::shared_ptr<Motor::PwmDcMotorImp> chassis_motor_left(std::make_shared<Motor::PwmDcMotorImp>(
        Config::Chassis::MOTOR_IMP_LEFT,
        Config::Chassis::MOTOR
    ));
    std::shared_ptr<Motor::PwmDcMotorImp> chassis_motor_right(
        std::make_shared<Motor::PwmDcMotorImp>(
            Config::Chassis::MOTOR_IMP_RIGHT,
            Config::Chassis::MOTOR
        )
    );

    std::shared_ptr<Chassis::DoubleWheelBalanceChassis> chassis(
        std::make_shared<Chassis::DoubleWheelBalanceChassis>(
            std::static_pointer_cast<Motor::FbkMotorBase>(chassis_motor_left),
            std::static_pointer_cast<Motor::FbkMotorBase>(chassis_motor_right),
            Config::Chassis::DOUBLE_WHEEL_BALANCE_CHASSIS_LQR
        )
    );

    Robot::RobotCtrl robot(chassis);

    xTaskCreate(
        led_task,
        "led task",
        configMINIMAL_STACK_SIZE * 1,
        NULL,
        (tskIDLE_PRIORITY + 1),
        &xCreatedLedTask
    );
    xTaskCreate(
        imu_task,
        "imu task",
        configMINIMAL_STACK_SIZE * 8,
        static_cast<void*>(&robot),
        (tskIDLE_PRIORITY + 6),
        &xCreatedImuTask
    );
    // xTaskCreate(
    //     chassis_task,
    //     "chassis task",
    //     configMINIMAL_STACK_SIZE * 8,
    //     static_cast<void*>(&robot),
    //     (tskIDLE_PRIORITY + 6),
    //     &xCreatedChassisTask
    // );
    // xTaskCreate(
    //     update_set_task,
    //     "update set task",
    //     configMINIMAL_STACK_SIZE * 8,
    //     static_cast<void*>(&robot),
    //     (tskIDLE_PRIORITY + 6),
    //     &xCreatedUpdateSetTask
    // );

    /* Start scheduler */
    vTaskStartScheduler();
}

static void imu_task(void* arg) {
    Robot::RobotCtrl& robot(*static_cast<Robot::RobotCtrl*>(arg));
    std::static_pointer_cast<Chassis::DoubleWheelBalanceChassis>(robot.chassis)->imu.task(nullptr);
}

static void chassis_task(void* arg) {
    Robot::RobotCtrl& robot(*static_cast<Robot::RobotCtrl*>(arg));
    robot.chassis->task(nullptr);
}

static void update_set_task(void* arg) {
    Robot::RobotCtrl& robot(*static_cast<Robot::RobotCtrl*>(arg));
    robot.update_set_task(nullptr);
}
