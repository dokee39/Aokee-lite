#include "double_wheel_balance_chassis.hpp"
#include "config.hpp"

namespace Chassis {
DoubleWheelBalanceChassis::DoubleWheelBalanceChassis(
    const std::shared_ptr<Motor::FbkMotorBase> motor_left,
    const std::shared_ptr<Motor::FbkMotorBase> motor_right,
    const Lqr::LqrConfig<6, 2> &lqr_config
):  
    lqr(lqr_config),
    yaw(imu.angle[2]),
    tilt_angle(imu.angle[1]), 
    tilt_speed(imu.gyro[1]) {
    motors.emplace_back(motor_left);
    motors.emplace_back(motor_right);
}

void DoubleWheelBalanceChassis::init() {}

void DoubleWheelBalanceChassis::update_state() {
    motors[0]->feedback();
    motors[1]->feedback();
    
    ref.vx = 0.0f;
    ref.vy = (motors[0]->get_speed() + motors[1]->get_speed()) * Config::Chassis::WHEEL_DIAMETER;
    ref.wz = imu.gyro[0];

    displacement += ref.vy * (float)Config::Chassis::CYCLE_TIME / 1000.0f; 
    if (set.vy != 0)
        displacement = 0.0f;

    yaw_set += set.wz * (float)Config::Chassis::CYCLE_TIME / 1000.0f;
}

void DoubleWheelBalanceChassis::ctrl_val_calc() {
    lqr.update_set((float[6]){ 0.0f, set.vy, Config::Chassis::TILT_ANGLE_SET, 0.0f, yaw_set, set.wz });
    lqr.update_ref((float[6]){ displacement, ref.vx, tilt_angle, tilt_speed, yaw, ref.wz });
    
    lqr.calc();
}

void DoubleWheelBalanceChassis::ctrl() {
    motors[0]->ctrl_val = lqr.get_u(0);
    motors[1]->ctrl_val = lqr.get_u(1);
    motors[0]->ctrl();
    motors[1]->ctrl();
}
} // namespace Chassis
