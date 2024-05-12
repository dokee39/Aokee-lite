#pragma once

#include "pwm_dc_motor_imp.hpp"
#include "robot_ctrl.hpp"
#include "stm32f4xx_hal_tim.h"
#include "tim.h"

namespace CONFIG
{
    const typename Motor::PwmDcMotorImpConfig CHASSIS_MOTOR_IMP_LEFT {
        .htim_pwm = htim12,
        .TIM_PWM_CHANNEL_A = TIM_CHANNEL_1,
        .TIM_PWM_CHANNEL_B = TIM_CHANNEL_2,
        .htim_ecd = htim2,
        .TIM_ECD_CHANNEL_A = TIM_CHANNEL_1,
        .TIM_ECD_CHANNEL_B = TIM_CHANNEL_2,
    };

    const typename Motor::PwmDcMotorImpConfig CHASSIS_MOTOR_IMP_RIGHT {
        .htim_pwm = htim12,
        .TIM_PWM_CHANNEL_A = TIM_CHANNEL_3,
        .TIM_PWM_CHANNEL_B = TIM_CHANNEL_4,
        .htim_ecd = htim3,
        .TIM_ECD_CHANNEL_A = TIM_CHANNEL_1,
        .TIM_ECD_CHANNEL_B = TIM_CHANNEL_2,
    };

    const typename Motor::PwmDcMotorConfig CHASSIS_MOTOR {
        .CCR_VAL_MAX_ = 65535,
        .FBK_PERIOD_ = 1,
        .PULSE_TO_RAD_RATIO_ = 3.14f
    };

}















