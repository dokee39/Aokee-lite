#include "pwm_dc_motor.hpp"
#include <cstdint>

#include "user_lib_cpp.hpp"

namespace Motor {
    bool PwmDcMotor::ctrl(int32_t ctrl_val) const
    {
        bool ret(true);

        UserLib::abs_limit<int32_t>(ctrl_val, CCR_VAL_MAX_);

        if (ctrl_val < 0)
            ret = run_(false, static_cast<uint32_t>(-ctrl_val));
        else
            ret = run_(true, static_cast<uint32_t>(ctrl_val));
        
        return ret;
    }

    bool PwmDcMotor::feedback()
    {
        bool ret(true);
        int32_t ecd_delta(fbk_());
        float speed(0.0f);
        float angle(0.0f);
        
        angle = get_angle() + ecd_delta * PULSE_TO_RAD_RATIO_;
        angle = UserLib::rad_format(angle);
        speed = ecd_delta * PULSE_TO_RAD_RATIO_ / FBK_PERIOD_ * 1000.0f;

        update(speed, angle);

        return ret;
    }
}

