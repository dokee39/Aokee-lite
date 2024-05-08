#pragma once

#include <stdint.h>
#include <functional>
#include "motor_base.hpp"

namespace Motor {

    using driver_set_t = std::function<bool(const bool, const uint32_t)>;
    using ecd_get_t = std::function<int32_t()>;

    struct PwmDcMotorConfig
    {
        PwmDcMotorConfig(uint32_t CCR_VAL_MAX)
            :CCR_VAL_MAX_(CCR_VAL_MAX)
        {}

        uint32_t CCR_VAL_MAX_;
    };

    // derived class : DC motor (controlled by PWM & feedback via pulse encoder)
    class PwmDcMotor : public FbkMotorBase<int32_t, driver_set_t, ecd_get_t>
    {
    public:
        explicit PwmDcMotor(const driver_set_t driver_set, const ecd_get_t ecd_get, const PwmDcMotorConfig &config)
            :FbkMotorBase(driver_set, ecd_get),
             CONFIG_(config),
             ecd_(0)
        {}
        ~PwmDcMotor() = default;

        bool ctrl(const int32_t ctrl_val) const;
        bool feedback();
        
    private:
        const PwmDcMotorConfig CONFIG_;
        int32_t ecd_;
        
        explicit PwmDcMotor(); // must init
        
    };
}



