#include "chassis_base.hpp"
#include "FreeRTOS.h"
#include "task.h"

namespace Chassis {
[[noreturn]] void ChassisBase::task(void* arg) {
    TickType_t xLastWakeTime;

    vTaskDelay(pdMS_TO_TICKS(10));

    while (true) {
        update_state();
        ctrl_val_calc();
        ctrl();

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
    }
}
} // namespace Chassis
