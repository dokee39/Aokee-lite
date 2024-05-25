#pragma once

#include <cstdint>

#include "motor_base.hpp"

namespace Motor {

struct PwmDcMotorConfig {
    const uint32_t FBK_PERIOD; // in ms
    const float PULSE_TO_RAD_RATIO;
};

// derived class : DC motor (controlled by PWM & feedback via pulse encoder)
class PwmDcMotor: public PwmDcMotorConfig, public FbkMotorBase {
public:
    explicit PwmDcMotor(const PwmDcMotorConfig& config, MotorImpBase& imp):
        PwmDcMotorConfig(config),
        FbkMotorBase(imp) {}
    ~PwmDcMotor() override = default;

    bool ctrl() override;
    bool feedback() override;

    // contrl_val here is pwm_duty

protected:
    int32_t ecd_delta = 0;

};
} // namespace Motor
