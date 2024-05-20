#pragma once

#include <memory>

#include "chassis_base.hpp"
#include "compatible.h"

namespace Robot
{
    class RobotCtrl 
    {
    public:
        explicit RobotCtrl(std::shared_ptr<Chassis::ChassisBase> chassis)
            : chassis(chassis)
        {}
        ~RobotCtrl() = default;

        std::shared_ptr<Chassis::ChassisBase> chassis;

    private:
        RobotCtrl() = delete; // must init
        RobotCtrl(const RobotCtrl &) = delete; // uncopyable
        RobotCtrl &operator=(const RobotCtrl &) = delete; // uncopyable

    };
}
