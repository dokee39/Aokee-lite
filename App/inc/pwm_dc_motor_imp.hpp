#pragma once

#include <cstdint>
#include "motor_base.hpp"
#include "tim.h"

namespace Motor
{
    class PwmDcMotorImp : public MotorImpBase
    {
    public:
        explicit PwmDcMotorImp(TIM_HandleTypeDef &htim_pwm, const uint32_t TIM_PWM_CHANNEL_A, TIM_HandleTypeDef &htim_ecd, const uint32_t TIM_ECD_CHANNEL_A);
        ~PwmDcMotorImp() = default;

    private:
        TIM_HandleTypeDef &htim_pwm;
        const uint32_t TIM_PWM_CHANNEL_A;
        const uint32_t TIM_PWM_CHANNEL_B;
        TIM_HandleTypeDef &htim_ecd;
        const uint32_t TIM_ECD_CHANNEL_A;
        const uint32_t TIM_ECD_CHANNEL_B;
        
        PwmDcMotorImp(); // must init
        void run(const bool dir, const uint32_t ccr_val);
        int32_t fbk();
        
    };
}

namespace Genshin
{
    class ZhangXinke
    {
    public:
        explicit ZhangXinke() = default;
        virtual ~ZhangXinke() = default;

    };

    class GenshinPlayerBase : public ZhangXinke
    {
    public:
        explicit GenshinPlayerBase() = default;
        virtual ~GenshinPlayerBase() = default;

        virtual void GenshinStart() = 0;

    };
}

