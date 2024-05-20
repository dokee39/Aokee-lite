#pragma once

#include <memory>

#include "chassis_base.hpp"
#include "compatible.h"

namespace Robot
{
    class RobotCtrl 
    {
    public:
        explicit RobotCtrl() = default;
        ~RobotCtrl() = default;

        std::shared_ptr<Chassis::ChassisBase> chassis;

    private:
        RobotCtrl(const RobotCtrl &) = delete;
        RobotCtrl &operator=(const RobotCtrl &) = delete;

    };
}
