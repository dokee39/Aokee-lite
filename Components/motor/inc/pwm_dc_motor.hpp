#pragma once

#include <cstdint>

#include "motor_base.hpp"

namespace Motor {

    struct PwmDcMotorConfig
    {
        const uint32_t CCR_VAL_MAX_;
        const uint32_t FBK_PERIOD_;
        const float PULSE_TO_RAD_RATIO_;
    };

    // derived class : DC motor (controlled by PWM & feedback via pulse encoder)
    template <typename T_imp>
    class PwmDcMotor : public PwmDcMotorConfig, public FbkMotorBase<int32_t, T_imp> 
    {
    public:
        explicit PwmDcMotor(const PwmDcMotorConfig &config, T_imp &imp)
            : PwmDcMotorConfig(config)
        {
            this->pimp = &imp;
        }
        ~PwmDcMotor() = default;

        bool ctrl(const int32_t ctrl_val) const;
        bool feedback();
        
    private:
        PwmDcMotor() = delete; // must init
        // PwmDcMotor(const PwmDcMotor &) = delete; // cannot copy
        PwmDcMotor &operator=(const PwmDcMotor &) = delete; // cannot copy
        
    };
}



