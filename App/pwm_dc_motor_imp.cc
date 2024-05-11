#include "pwm_dc_motor_imp.hpp"
#include <cstdint>

namespace Motor
{
    PwmDcMotorImp::PwmDcMotorImp(TIM_HandleTypeDef &htim_pwm, const uint32_t TIM_PWM_CHANNEL_A, TIM_HandleTypeDef &htim_ecd, const uint32_t TIM_ECD_CHANNEL_A)
        : htim_pwm(htim_pwm),
          TIM_PWM_CHANNEL_A(TIM_PWM_CHANNEL_A),
          TIM_PWM_CHANNEL_B(TIM_PWM_CHANNEL_A == TIM_CHANNEL_1 ? TIM_CHANNEL_2 : TIM_CHANNEL_4),
          htim_ecd(htim_ecd),
          TIM_ECD_CHANNEL_A(TIM_ECD_CHANNEL_A),
          TIM_ECD_CHANNEL_B(TIM_ECD_CHANNEL_A == TIM_CHANNEL_1 ? TIM_CHANNEL_2 : TIM_CHANNEL_4)
    {
        HAL_TIM_PWM_Start(&htim_pwm, TIM_PWM_CHANNEL_A);
        HAL_TIM_PWM_Start(&htim_pwm, TIM_PWM_CHANNEL_B);
        HAL_TIM_PWM_Start(&htim_ecd, TIM_ECD_CHANNEL_A);
        HAL_TIM_PWM_Start(&htim_ecd, TIM_ECD_CHANNEL_B);
    }
    
    void PwmDcMotorImp::run(const bool dir, const uint32_t ccr_val)
    {
        if (dir == true)
        {
            __HAL_TIM_SetCompare(&htim_pwm, TIM_PWM_CHANNEL_B, 0);
            __HAL_TIM_SetCompare(&htim_pwm, TIM_PWM_CHANNEL_A, ccr_val);
        } else {
            __HAL_TIM_SetCompare(&htim_pwm, TIM_PWM_CHANNEL_A, 0);
            __HAL_TIM_SetCompare(&htim_pwm, TIM_PWM_CHANNEL_B, ccr_val);
        }
    }
    
    int32_t PwmDcMotorImp::fbk()
    {
        int32_t ecd = __HAL_TIM_GetCounter(&htim_ecd);
        __HAL_TIM_SetCounter(&htim_ecd, 0);

        return ecd;
    }
}
