#pragma once

#include <cstdint>
#include "motor_base.hpp"
#include "tim.h"

namespace Motor
{
    struct PwmDcMotorImpConfig
    {
        TIM_HandleTypeDef &htim_pwm;
        const uint32_t TIM_PWM_CHANNEL_A;
        const uint32_t TIM_PWM_CHANNEL_B;
        TIM_HandleTypeDef &htim_ecd;
        const uint32_t TIM_ECD_CHANNEL_A;
        const uint32_t TIM_ECD_CHANNEL_B;
    };

    class PwmDcMotorImp : public PwmDcMotorImpConfig, public MotorImpBase
    {
    public:
        explicit PwmDcMotorImp(const PwmDcMotorImpConfig &config);
        ~PwmDcMotorImp() = default;

    private:
        PwmDcMotorImp() = delete; // must init
        // PwmDcMotorImp(const PwmDcMotorImp &) = delete; // cannot copy
        PwmDcMotorImp &operator=(const PwmDcMotorImp &) = delete; // cannot copu

        void run(const bool dir, const uint32_t ccr_val);
        int32_t fbk();

    };
}

