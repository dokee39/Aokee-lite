#include "user_lib_cpp.hpp"

#include <cmath>

namespace UserLib
{
    float rad_format(const float ang) {
        float ans = fmodf(ang + PIf, PIf * 2.f);
        return (ans < 0.f) ? ans + PIf : ans - PIf;
    }

    template <typename T>
    void abs_limit(T &num, T limit)
    {
        if (num > limit)
            num = limit;
        else if (num < -limit)
            num = -limit;
    }
    
    template <typename T>
    void unpack(T &t, void *ptr) {
        for (size_t i = 0; i < sizeof(T); i++) {
            *((uint8_t *)&t + i) = *((uint8_t *)ptr + i);
        }
    }

    template <typename T>
    std::vector<uint8_t> pack(T &t) {
        std::vector<uint8_t> ans;
        for (size_t i = 0; i < sizeof(T); i++) {
            ans.push_back(*((uint8_t *)&t + i));
        }
        return ans;
    }
    
}  // namespace UserLib
