#include "chassis_base.hpp"

namespace Chassis
{
    void ChassisBase::task(void *arg)
    {
        while (true)
        {
            update_state();
            ctrl_val_calc();
            ctrl();
            
            task_delay_until();
        }
    }
}
