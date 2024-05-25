#include <cstdint>

#include "pwm_dc_motor.hpp"
#include "user_lib_cpp.hpp"

namespace Motor {
bool PwmDcMotor::ctrl() {
    bool ret(true);

    UserLib::abs_limit<float>(ctrl_val, 1.0f);

    if (ctrl_val < 0)
        ret = imp.run();
    else
        ret = imp.run();

    return ret;
}

bool PwmDcMotor::feedback() {
    bool ret(true);
    float speed(0.0f);
    float angle(0.0f);

    imp.fbk();

    angle = get_angle() + ecd_delta * PULSE_TO_RAD_RATIO;
    angle = UserLib::rad_format(angle);
    speed = ecd_delta * PULSE_TO_RAD_RATIO / FBK_PERIOD * 1000.0f;

    update(speed, angle);

    return ret;
}
} // namespace Motor
