#pragma once

#include <memory>

#include "chassis_base.hpp"

namespace Robot {
class RobotCtrl {
public:
    explicit RobotCtrl(std::shared_ptr<Chassis::ChassisBase> chassis):
        chassis(chassis),
        chassis_set(chassis->set) {}
    ~RobotCtrl() = default;

    [[noreturn]] void update_set_task(void* arg);

    std::shared_ptr<Chassis::ChassisBase> chassis;

private:
    RobotCtrl() = delete; // must init
    RobotCtrl(const RobotCtrl&) = delete; // uncopyable
    RobotCtrl& operator=(const RobotCtrl&) = delete; // uncopyable

    Chassis::Status& chassis_set;
};
} // namespace Robot
