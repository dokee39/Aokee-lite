#pragma once

#include "chassis_base.hpp"
#include "imu.hpp"
#include "lqr_controller.hpp"
#include "motor_base.hpp"
#include <memory>

namespace Chassis {
class DoubleWheelBalanceChassis: public ChassisBase {
public:
    explicit DoubleWheelBalanceChassis(
        const std::shared_ptr<Motor::MotorBase> motor_left,
        const std::shared_ptr<Motor::MotorBase> motor_right,
        const Lqr::LqrConfig<6, 2>& lqr_config
    );
    ~DoubleWheelBalanceChassis() override = default;

    void init() override;

    Dev::Imu imu;

private:
    DoubleWheelBalanceChassis() = delete; // must init

    void update_state() override;
    void ctrl_val_calc() override;
    void ctrl() override;
    void task_delay_until() override;

    /* Z[0] : displacement
     * Z[1] : vy (speed)
     * Z[2] : tilt_angle
     * Z[3] : tilt_speed
     * Z[4] : yaw_angle
     * Z[5] : yaw_speed
     * U[0] : left motor control_val
     * U[1] : right motor control_val
    */
    Lqr::Lqr<6, 2> lqr;
    float displacement = 0.0f;
    float& yaw;
    float yaw_set;
    float& tilt_angle;
    float& tilt_speed;

};
} // namespace Chassis

