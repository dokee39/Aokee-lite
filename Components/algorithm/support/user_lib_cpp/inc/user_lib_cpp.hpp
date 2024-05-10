#pragma once

#include <vector>
#include <cstdint>

namespace UserLib
{
    const float PIf = 3.14159265358979323846f;	/* pi */
        
    float rad_format(const float ang);
    
    template <typename T>
    void abs_limit(T &num, T limit);

    template <typename T>
    void unpack(T &t, void *ptr);

    template <typename T>
    std::vector<uint8_t> pack(T &t);

}  // namespace UserLib
