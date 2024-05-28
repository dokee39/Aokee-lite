#pragma once

#include "pwm_dc_motor.hpp"
#include "pwm_dc_motor_impl.hpp"
#include "matrix.h"
#include "tim.h"
#include "lqr_controller.hpp"


namespace Config::Chassis {
namespace DoubleWheelChassis {

const uint32_t CYCLE_TIME = 1;

const float WHEEL_DIAMETER = 5.0f;
const float TILT_ANGLE_SET = 0.0f;

const typename Motor::PwmDcMotorImplConfig MOTOR_IMPL_LEFT {
    .CCR_TYPE = Motor::PwmDcMotorImplConfig::TIM_INT32,
    .CCR_VAL_MAX = 2500,
    .htim_pwm = htim5,
    .TIM_PWM_CHANNEL_A = TIM_CHANNEL_3,
    .TIM_PWM_CHANNEL_B = TIM_CHANNEL_4,

    .ECD_TYPE = Motor::PwmDcMotorImplConfig::TIM_INT32,
    .htim_ecd = htim2,
};

const typename Motor::PwmDcMotorImplConfig MOTOR_IMPL_RIGHT {
    .CCR_TYPE = Motor::PwmDcMotorImplConfig::TIM_INT16,
    .CCR_VAL_MAX = 2500,
    .htim_pwm = htim8,
    .TIM_PWM_CHANNEL_A = TIM_CHANNEL_3,
    .TIM_PWM_CHANNEL_B = TIM_CHANNEL_4,

    .ECD_TYPE = Motor::PwmDcMotorImplConfig::TIM_INT16,
    .htim_ecd = htim3,
};

const typename Motor::PwmDcMotorConfig MOTOR { 
    .FBK_PERIOD = 1,
    .PULSE_TO_RAD_RATIO = 3.1415926f 
};

const typename Lqr::LqrConfig<6, 2> LQR {
    .K = Matrixf<2, 6>((float[12]) { 0.0f }),
    .Umax = Matrixf<1, 2>((float[2]) { 1.0f, 1.0f }),
};

} // namespace DoubleWheelBalance    

struct DoubleWheelBalanceChassisConfig {
    const Motor::PwmDcMotorImplConfig MOTOR_IMPL_LEFT;
    const Motor::PwmDcMotorImplConfig MOTOR_IMPL_RIGHT;
    const Motor::PwmDcMotorConfig MOTOR;
    const Lqr::LqrConfig<6, 2> LQR;
};

const typename Config::Chassis::DoubleWheelBalanceChassisConfig DoubleWheelBalance {
    .MOTOR_IMPL_LEFT = DoubleWheelChassis::MOTOR_IMPL_LEFT,
    .MOTOR_IMPL_RIGHT = DoubleWheelChassis::MOTOR_IMPL_RIGHT,
    .MOTOR = DoubleWheelChassis::MOTOR,
    .LQR = DoubleWheelChassis::LQR,
};

} // namespace Config::Chassis
