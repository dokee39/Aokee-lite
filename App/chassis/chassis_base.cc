#include "chassis_base.hpp"

namespace Chassis {
[[noreturn]] void ChassisBase::task(void* arg) {
    while (true) {
        update_state();
        ctrl_val_calc();
        ctrl();

        task_delay_until();
    }
}
} // namespace Chassis
