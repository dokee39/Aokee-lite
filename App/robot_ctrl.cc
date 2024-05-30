#include "robot_ctrl.hpp"
#include "FreeRTOS.h"
#include "config.hpp"
#include "remote_controller.h"
#include "task.h"
#include "user_lib_cpp.hpp"

extern RC_ctrl_t rc_ctrl;

static void robot_update_set_task(void* arg)
{
    static_cast<Robot::RobotCtrl*>(arg)->update_set_task(nullptr);
}

namespace Robot {
RobotCtrl::RobotCtrl(Chassis::ChassisBase* chassis):
    chassis(chassis),
    chassis_set(chassis->set) {
    TaskHandle_t xCreatedUpdateSetTask = *(new TaskHandle_t);

    xTaskCreate(
        robot_update_set_task,
        "update set task",
        configMINIMAL_STACK_SIZE * 8,
        static_cast<void*>(this),
        (tskIDLE_PRIORITY + Config::Priority::UPDATE_SET),
        &xCreatedUpdateSetTask
    );
}

[[noreturn]] void RobotCtrl::update_set_task(void* arg) {
    TickType_t xLastWakeTime;

    remote_control_init();
    vTaskDelay(pdMS_TO_TICKS(Config::Time::UPDATE_SET_INIT));

    xLastWakeTime = xTaskGetTickCount();

    while (true) {
        float vx_set = rc_ctrl.rc.ch[0];
        float vy_set = rc_ctrl.rc.ch[1];
        float wz_set = rc_ctrl.rc.ch[2];
        UserLib::deadzone_limit(vx_set, Config::RC::VX_SET_MAX);
        UserLib::deadzone_limit(vy_set, Config::RC::VY_SET_MAX);
        UserLib::deadzone_limit(wz_set, Config::RC::WZ_SET_MAX);
        chassis->set.vx = vx_set;
        chassis->set.vy = vy_set;
        chassis->set.wz = wz_set;

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(Config::Time::UPDATE_SET_CYCLE));
    }
}
} // namespace Robot
