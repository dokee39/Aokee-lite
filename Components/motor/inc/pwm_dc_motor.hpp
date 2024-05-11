#pragma once

#include <cstdint>

#include "motor_base.hpp"

namespace Motor {

    struct PwmDcMotorConfig
    {
    public:
        explicit PwmDcMotorConfig(uint32_t CCR_VAL_MAX, uint32_t FBK_PERIOD, float PULSE_TO_RAD_RATIO)
            : CCR_VAL_MAX_(CCR_VAL_MAX),
              FBK_PERIOD_(FBK_PERIOD),
              PULSE_TO_RAD_RATIO_(PULSE_TO_RAD_RATIO) {
        }
        ~PwmDcMotorConfig() = default;

        const uint32_t CCR_VAL_MAX_;
        const uint32_t FBK_PERIOD_;
        const float PULSE_TO_RAD_RATIO_;

    private:
        PwmDcMotorConfig(); // must init
        
    };

    // derived class : DC motor (controlled by PWM & feedback via pulse encoder)
    template <typename T_imp>
    class PwmDcMotor : public PwmDcMotorConfig, public FbkMotorBase<int32_t, T_imp> 
    {
    public:
        explicit PwmDcMotor(const PwmDcMotorConfig &config, T_imp &imp)
            : PwmDcMotorConfig(config),
              MotorBase<int32_t, T_imp>::imp(imp) {
        }
        ~PwmDcMotor() = default;

        bool ctrl(const int32_t ctrl_val) const override;
        bool feedback();
        
    private:
        PwmDcMotor(); // must init
        
    };
}



