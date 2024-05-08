#include "pwm_dc_motor.hpp"
#include <cstdint>

namespace Motor {
    bool PwmDcMotor::ctrl(const int32_t ctrl_val) const
    {
        bool ret(true);
        bool dir(true);
        uint32_t ccr_val(0);

        if (ctrl_val < 0)
        {
            dir = true;
            ccr_val = static_cast<uint32_t>(ctrl_val);
        } else {
            dir = false;
            ccr_val = static_cast<uint32_t>(-ctrl_val);
        }

        ret = run_(dir, ccr_val > CONFIG_.CCR_VAL_MAX_ ? CONFIG_.CCR_VAL_MAX_ : ccr_val); 
        
        return ret;
    }

    bool PwmDcMotor::feedback()
    {
        bool ret(true);
        int32_t ecd_delta(fbk_());
        
        

        return ret;
    }
}

