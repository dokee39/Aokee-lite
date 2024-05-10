#pragma once

#include <cstdint>
#include <functional>

#include "motor_base.hpp"

namespace Motor {

    using driver_set_t = std::function<bool(const bool, const uint32_t)>;
    using ecd_get_t = std::function<int32_t()>;

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
    class PwmDcMotor : public PwmDcMotorConfig, public FbkMotorBase<int32_t, driver_set_t, ecd_get_t> 
    {
    public:
        explicit PwmDcMotor(const PwmDcMotorConfig &config, const driver_set_t driver_set, const ecd_get_t ecd_get)
            : PwmDcMotorConfig(config),
              FbkMotorBase(driver_set, ecd_get) {
        }
        ~PwmDcMotor() = default;

        bool ctrl(const int32_t ctrl_val) const override;
        bool feedback();
        
    private:
        PwmDcMotor(); // must init
        
    };
}



