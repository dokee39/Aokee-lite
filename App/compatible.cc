#include "FreeRTOS.h"
#include "compatible.h"
#include "config.hpp"
#include "led_task.h"
#include "robot_ctrl.hpp"
#include "task.h"
#include "double_wheel_balance_chassis.hpp"

static void imu_task(void* arg);
static void chassis_task(void* arg);
static void update_set_task(void* arg);

void main_entry(void) {
    TaskHandle_t xCreatedLedTask;
    TaskHandle_t xCreatedImuTask;
    TaskHandle_t xCreatedChassisTask;
    TaskHandle_t xCreatedUpdateSetTask;

    Chassis::ChassisBase* chassis = new Chassis::Chassis(Config::Chassis::DoubleWheelBalance);
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
    static_cast<Chassis::Chassis<Config::Chassis::DoubleWheelBalanceChassisConfig>*>(robot.chassis)->imu.task(nullptr);
}

static void chassis_task(void* arg) {
    Robot::RobotCtrl& robot(*static_cast<Robot::RobotCtrl*>(arg));
    robot.chassis->task(nullptr);
}

static void update_set_task(void* arg) {
    Robot::RobotCtrl& robot(*static_cast<Robot::RobotCtrl*>(arg));
    robot.update_set_task(nullptr);
}
