#include "double_wheel_balance_chassis.hpp"

namespace Chassis {
DoubleWheelBalanceChassis::DoubleWheelBalanceChassis(
    const std::shared_ptr<Motor::MotorBase> motor_left,
    const std::shared_ptr<Motor::MotorBase> motor_right,
    const Lqr::LqrConfig<6, 2> &lqr_config
):  
    lqr(lqr_config),
    yaw(imu.angle[0]),
    tilt_angle(imu.angle[1]), 
    tilt_speed(imu.gyro[1]) {
    motors.emplace_back(motor_left);
    motors.emplace_back(motor_right);
}

void DoubleWheelBalanceChassis::init() {}

void DoubleWheelBalanceChassis::update_state() {
}

void DoubleWheelBalanceChassis::ctrl_val_calc() {
    lqr.calc();
}

void DoubleWheelBalanceChassis::ctrl() {}

void DoubleWheelBalanceChassis::task_delay_until() {}

} // namespace Chassis
