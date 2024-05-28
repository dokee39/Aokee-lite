#include "config.hpp"
#include "double_wheel_balance_chassis.hpp"
#include "double_wheel_balance_chassis_config.hpp"

using namespace Config::Chassis::DoubleWheelChassis;

namespace Chassis {
Chassis<Config::Chassis::DoubleWheelBalanceChassisConfig>::Chassis(const Config::Chassis::DoubleWheelBalanceChassisConfig& config):
    lqr(config.LQR),
    yaw(imu.angle[2]),
    tilt_angle(imu.angle[1]),
    tilt_speed(imu.gyro[1]) {
    Motor::MotorImplBase* motor_imp_left = new Motor::MotorImpl(config.MOTOR_IMPL_LEFT);
    Motor::MotorImplBase* motor_imp_right = new Motor::MotorImpl(config.MOTOR_IMPL_RIGHT);
    Motor::MotorBase* motor_left = new Motor::Motor(config.MOTOR, *motor_imp_left);
    Motor::MotorBase* motor_right = new Motor::Motor(config.MOTOR, *motor_imp_right);
    motors.emplace_back(motor_left);
    motors.emplace_back(motor_right);
}

void Chassis<Config::Chassis::DoubleWheelBalanceChassisConfig>::init() {}

void Chassis<Config::Chassis::DoubleWheelBalanceChassisConfig>::update_state() {
    motors[0]->feedback();
    motors[1]->feedback();

    ref.vx = 0.0f;
    ref.vy = (motors[0]->get_speed() + motors[1]->get_speed()) * WHEEL_DIAMETER;
    ref.wz = imu.gyro[0];

    displacement += ref.vy * (float)CYCLE_TIME / 1000.0f;
    if (set.vy != 0)
        displacement = 0.0f;

    yaw_set += set.wz * (float)CYCLE_TIME / 1000.0f;
}

void Chassis<Config::Chassis::DoubleWheelBalanceChassisConfig>::ctrl_val_calc() {
    lqr.update_set((float[6]) { 0.0f, set.vy, TILT_ANGLE_SET, 0.0f, yaw_set, set.wz });
    lqr.update_ref((float[6]) { displacement, ref.vx, tilt_angle, tilt_speed, yaw, ref.wz });

    lqr.calc();
}

void Chassis<Config::Chassis::DoubleWheelBalanceChassisConfig>::ctrl() {
    motors[0]->ctrl_val = lqr.get_u(0);
    motors[1]->ctrl_val = lqr.get_u(1);
    motors[0]->ctrl();
    motors[1]->ctrl();
}
} // namespace Chassis
