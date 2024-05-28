#pragma once

#include <cstdint>

#include "motor_base.hpp"

namespace Motor {

struct PwmDcMotorConfig {
    const uint32_t FBK_PERIOD; // in ms
    const float PULSE_TO_RAD_RATIO;
};

// derived class : DC motor (controlled by PWM & feedback via pulse encoder)
class PwmDcMotor: public PwmDcMotorConfig, public MotorBase {
public:
    explicit PwmDcMotor(const PwmDcMotorConfig& config, MotorImplBase& impl):
        PwmDcMotorConfig(config),
        MotorBase(impl) {}
    ~PwmDcMotor() override = default;

    bool ctrl() override;
    bool feedback() override;

private:
    // ctrl_val is pwm_duty, 0 ~ 1
    int32_t ecd_delta = 0;

};
} // namespace Motor
