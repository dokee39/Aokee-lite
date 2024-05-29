#include "config.hpp"
#include "double_wheel_balance_chassis.hpp"
#include "double_wheel_balance_chassis_config.hpp"
#include "FreeRTOS.h"
#include "task.h"

using namespace Config::Chassis::DoubleWheelChassis;
using Here = Config::Chassis::DoubleWheelBalanceChassisConfig; 

static void imu_task(void* arg) {
    static_cast<Dev::Imu*>(arg)->task(nullptr);
}

static void chassis_task(void* arg) {
    static_cast<Chassis::Chassis<Here>*>(arg)->task(nullptr);
}

namespace Chassis {
Chassis<Here>::Chassis(const Here& config):
    lqr(config.LQR),
    yaw(imu.angle[2]),
    tilt_angle(imu.angle[1]),
    tilt_speed(imu.gyro[1]) {
    TaskHandle_t xCreatedImuTask = *(new TaskHandle_t);
    TaskHandle_t xCreatedChassisTask = *(new TaskHandle_t);
    
    auto motor_imp_left = new Motor::MotorImpl(config.MOTOR_IMPL_LEFT);
    auto motor_imp_right = new Motor::MotorImpl(config.MOTOR_IMPL_RIGHT);
    Motor::MotorBase* motor_left = new Motor::Motor(config.MOTOR, *motor_imp_left);
    Motor::MotorBase* motor_right = new Motor::Motor(config.MOTOR, *motor_imp_right);

    motors.emplace_back(motor_left);
    motors.emplace_back(motor_right);

    xTaskCreate(
        imu_task,
        "imu task",
        configMINIMAL_STACK_SIZE * 8,
        static_cast<void*>(&this->imu),
        (tskIDLE_PRIORITY + 6),
        &xCreatedImuTask
    );
    xTaskCreate(
        chassis_task,
        "chassis task",
        configMINIMAL_STACK_SIZE * 8,
        static_cast<void*>(this),
        (tskIDLE_PRIORITY + 6),
        &xCreatedChassisTask
    );
}

void Chassis<Here>::init() {}

void Chassis<Here>::update_state() {
    motors[0]->feedback();
    motors[1]->feedback();

    ref.vx = 0.0f;
    ref.vy = (motors[0]->get_speed() + motors[1]->get_speed()) * WHEEL_DIAMETER;
    ref.wz = imu.gyro[0];

    displacement += ref.vy * (float)Config::Time::CHASSIS_CYCLE / 1000.0f;
    if (set.vy != 0)
        displacement = 0.0f;

    yaw_set += set.wz * (float)Config::Time::CHASSIS_CYCLE / 1000.0f;
}

void Chassis<Here>::ctrl_val_calc() {
    lqr.update_set((float[6]) { 0.0f, set.vy, TILT_ANGLE_SET, 0.0f, yaw_set, set.wz });
    lqr.update_ref((float[6]) { displacement, ref.vx, tilt_angle, tilt_speed, yaw, ref.wz });

    lqr.calc();
}

void Chassis<Here>::ctrl() {
    motors[0]->ctrl_val = lqr.get_u(0);
    motors[1]->ctrl_val = lqr.get_u(1);
    motors[0]->ctrl();
    motors[1]->ctrl();
}
} // namespace Chassis
