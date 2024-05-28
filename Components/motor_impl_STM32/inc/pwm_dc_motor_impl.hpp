#pragma once

#include "tim.h"
#include "motor_base.hpp"
#include <cstdint>

namespace Motor {
struct PwmDcMotorImplConfig {
    enum TIM_TYPE_e {
        TIM_INT16 = 0,
        TIM_INT32 = 1,
    };
    static const uint32_t TIM_ECD_CHANNEL_A = TIM_CHANNEL_1;
    static const uint32_t TIM_ECD_CHANNEL_B = TIM_CHANNEL_2;

    const TIM_TYPE_e CCR_TYPE;
    const uint32_t CCR_VAL_MAX;
    TIM_HandleTypeDef& htim_pwm;
    const uint32_t TIM_PWM_CHANNEL_A;
    const uint32_t TIM_PWM_CHANNEL_B;

    const TIM_TYPE_e ECD_TYPE;
    TIM_HandleTypeDef& htim_ecd;
};

template<>
class MotorImpl<PwmDcMotorImplConfig>: public PwmDcMotorImplConfig, public MotorImplBase {
public:
    explicit MotorImpl(const PwmDcMotorImplConfig& config_imp);
    ~MotorImpl() override = default;

private:
    MotorImpl() = delete; // must init

    bool msg_out(std::any& a_ctrl_val) override;
    bool msg_in(std::any& a_fbk_val) override;
};
} // namespace Motor
