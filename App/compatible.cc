#include "FreeRTOS.h"
#include "compatible.h"
#include "config.hpp"
#include "imu.hpp"
#include "led_task.h"
#include "robot_ctrl.hpp"
#include "task.h"
#include "double_wheel_balance_chassis.hpp"

void main_entry(void) {
    TaskHandle_t xCreatedLedTask;

    xTaskCreate(
        led_task,
        "led task",
        configMINIMAL_STACK_SIZE * 1,
        NULL,
        (tskIDLE_PRIORITY + 1),
        &xCreatedLedTask
    );

    auto chassis = new Chassis::Chassis(Config::Chassis::DoubleWheelBalance);
    auto robot = new Robot::RobotCtrl(chassis);

    /* Start scheduler */
    vTaskStartScheduler();
}
