#include "pwm_dc_motor.hpp"
#include <cstdint>

#include "user_lib_cpp.hpp"

namespace Motor {
    template <typename T_imp>
    bool PwmDcMotor<T_imp>::ctrl(int32_t ctrl_val) const
    {
        bool ret(true);

        UserLib::abs_limit<int32_t>(ctrl_val, CCR_VAL_MAX_);

        if (ctrl_val < 0)
            ret = MotorBase<int32_t, T_imp>::imp.run(false, static_cast<uint32_t>(-ctrl_val));
        else
            ret = MotorBase<int32_t, T_imp>::imp.run(true, static_cast<uint32_t>(ctrl_val));
        
        return ret;
    }

    template <typename T_imp>
    bool PwmDcMotor<T_imp>::feedback()
    {
        bool ret(true);
        int32_t ecd_delta(MotorBase<int32_t, T_imp>::imp.fbk());
        float speed(0.0f);
        float angle(0.0f);
        
        angle = MotorBase<int32_t, T_imp>::get_angle() + ecd_delta * PULSE_TO_RAD_RATIO_;
        angle = UserLib::rad_format(angle);
        speed = ecd_delta * PULSE_TO_RAD_RATIO_ / FBK_PERIOD_ * 1000.0f;

        MotorBase<int32_t, T_imp>::update(speed, angle);

        return ret;
    }
}

