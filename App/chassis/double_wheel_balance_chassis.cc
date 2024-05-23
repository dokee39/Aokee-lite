#include "double_wheel_balance_chassis.hpp"

namespace Chassis {
DoubleWheelBalanceChassis::DoubleWheelBalanceChassis(
    const std::shared_ptr<Motor::MotorBase> motor_left,
    const std::shared_ptr<Motor::MotorBase> motor_right
) {
    motors.emplace_back(motor_left);
    motors.emplace_back(motor_right);
}

void DoubleWheelBalanceChassis::init() {}

void DoubleWheelBalanceChassis::update_state() {}

void DoubleWheelBalanceChassis::ctrl_val_calc() {}

void DoubleWheelBalanceChassis::ctrl() {}

void DoubleWheelBalanceChassis::task_delay_until() const {}

} // namespace Chassis
