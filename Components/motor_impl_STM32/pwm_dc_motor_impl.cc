#include <cstdint>
#include <any>

#include "pwm_dc_motor_impl.hpp"

namespace Motor {
MotorImpl<PwmDcMotorImplConfig>::MotorImpl(
    const PwmDcMotorImplConfig& config_imp
):
    PwmDcMotorImplConfig(config_imp) {
    // timer would not restart since there ia a judge inside HAL driver
    HAL_TIM_PWM_Start(&htim_pwm, TIM_PWM_CHANNEL_A);
    HAL_TIM_PWM_Start(&htim_pwm, TIM_PWM_CHANNEL_B);
    HAL_TIM_Encoder_Start(&htim_ecd, TIM_ECD_CHANNEL_A);
    HAL_TIM_Encoder_Start(&htim_ecd, TIM_ECD_CHANNEL_B);
}

bool MotorImpl<PwmDcMotorImplConfig>::msg_out(std::any a_ctrl_val) {
    bool ret(true);
    float& ctrl_val(*std::any_cast<float *>(a_ctrl_val));

    if (ctrl_val < 0) {
        __HAL_TIM_SetCompare(&htim_pwm, TIM_PWM_CHANNEL_B, 0);
        __HAL_TIM_SetCompare(
            &htim_pwm,
            TIM_PWM_CHANNEL_A,
            static_cast<uint32_t>(-ctrl_val * CCR_VAL_MAX)
        );
    } else {
        __HAL_TIM_SetCompare(&htim_pwm, TIM_PWM_CHANNEL_A, 0);
        __HAL_TIM_SetCompare(
            &htim_pwm,
            TIM_PWM_CHANNEL_B,
            static_cast<uint32_t>(ctrl_val * CCR_VAL_MAX)
        );
    }

    return ret;
}

bool MotorImpl<PwmDcMotorImplConfig>::msg_in(std::any a_fbk_val) {
    bool ret(true);
    float& ecd_delta(*std::any_cast<float*>(a_fbk_val));

    switch (ECD_TYPE) {
        case TIM_INT16: {
            int16_t ecd = __HAL_TIM_GetCounter(&htim_ecd);
            ecd_delta = static_cast<int32_t>(ecd);
        } break;
        case TIM_INT32: {
            int32_t ecd = __HAL_TIM_GetCounter(&htim_ecd);
            ecd_delta = ecd;
        } break;
        default:
            break;
    }
    __HAL_TIM_SetCounter(&htim_ecd, 0);

    return ret;
}
} // namespace Motor
