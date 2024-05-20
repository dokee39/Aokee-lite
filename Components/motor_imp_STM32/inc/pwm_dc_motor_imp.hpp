#pragma once

#include <cstdint>
#include "pwm_dc_motor.hpp"
#include "tim.h"

namespace Motor
{
    struct PwmDcMotorImpConfig
    {
        enum TIM_TYPE_e{
            TIM_INT16 = 0,
            TIM_INT32 = 1,
        };
        static const uint32_t TIM_ECD_CHANNEL_A = TIM_CHANNEL_1;
        static const uint32_t TIM_ECD_CHANNEL_B = TIM_CHANNEL_2;
        
        const TIM_TYPE_e CCR_TYPE;
        const uint32_t CCR_VAL_MAX;
        TIM_HandleTypeDef &htim_pwm;
        const uint32_t TIM_PWM_CHANNEL_A;
        const uint32_t TIM_PWM_CHANNEL_B;

        const TIM_TYPE_e ECD_TYPE;
        TIM_HandleTypeDef &htim_ecd;
    };

    class PwmDcMotorImp : public PwmDcMotorImpConfig, public MotorImpBase, public PwmDcMotor
    {
    public:
        explicit PwmDcMotorImp(const PwmDcMotorImpConfig &config_imp, const PwmDcMotorConfig &config_motor);
        ~PwmDcMotorImp() override = default;

    private:
        PwmDcMotorImp() = delete; // must init

        bool run() override;
        bool fbk() override;

    };
}

