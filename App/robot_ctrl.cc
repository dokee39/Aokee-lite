#include "robot_ctrl.hpp"
#include "FreeRTOS.h"
#include "config.hpp"
#include "remote_controller.h"
#include "task.h"
#include "user_lib_cpp.hpp"

extern RC_ctrl_t rc_ctrl;

namespace Robot {
[[noreturn]] void RobotCtrl::update_set_task(void* arg) {
    TickType_t xLastWakeTime;

    vTaskDelay(pdMS_TO_TICKS(10));

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

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
    }
}
} // namespace Robot
