#include "chassis_base.hpp"

namespace Chassis
{
    template <typename T>
    void ChassisBase<T>::task(void *arg)
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
