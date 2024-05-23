#pragma once

#include "pwm_dc_motor_imp.hpp"
#include "robot_ctrl.hpp"
#include "tim.h"

#warning "reorignize config"

namespace CONFIG {
const typename Motor::PwmDcMotorImpConfig CHASSIS_MOTOR_IMP_LEFT {
    .CCR_TYPE = Motor::PwmDcMotorImpConfig::TIM_INT32,
    .CCR_VAL_MAX = 4294967295,
    .htim_pwm = htim5,
    .TIM_PWM_CHANNEL_A = TIM_CHANNEL_3,
    .TIM_PWM_CHANNEL_B = TIM_CHANNEL_4,

    .ECD_TYPE = Motor::PwmDcMotorImpConfig::TIM_INT32,
    .htim_ecd = htim2,
};

const typename Motor::PwmDcMotorImpConfig CHASSIS_MOTOR_IMP_RIGHT {
    .CCR_TYPE = Motor::PwmDcMotorImpConfig::TIM_INT16,
    .CCR_VAL_MAX = 65535,
    .htim_pwm = htim8,
    .TIM_PWM_CHANNEL_A = TIM_CHANNEL_3,
    .TIM_PWM_CHANNEL_B = TIM_CHANNEL_4,

    .ECD_TYPE = Motor::PwmDcMotorImpConfig::TIM_INT16,
    .htim_ecd = htim3,
};

const typename Motor::PwmDcMotorConfig CHASSIS_MOTOR { .FBK_PERIOD = 1,
                                                       .PULSE_TO_RAD_RATIO = 3.1415926f };

} // namespace CONFIG
