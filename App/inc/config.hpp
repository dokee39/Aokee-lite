#pragma once

#include <cstdint>

// config files
#include "double_wheel_balance_chassis_config.hpp"

namespace Config {

namespace RC {
    const float VX_SET_RATIO = 0.0f;
    const float VY_SET_RATIO = 0.0f;
    const float WZ_SET_RATIO = 0.0f;

    const int16_t VX_SET_DEADZONE = 0;
    const int16_t VY_SET_DEADZONE = 0;
    const int16_t WZ_SET_DEADZONE = 0;

    const float VX_SET_MAX = 0.0f;
    const float VY_SET_MAX = 0.0f;
    const float WZ_SET_MAX = 0.0f;
} // namespace RC
} // namespace Config
