#pragma once

#include "matrix.h"

namespace Lqr
{
    template <int dz, int du>
    struct LqrConfig 
    {
        const Matrixf<du, dz> K;
        const Matrixf<1, du> Umax;
    };

    template <int dz, int du>
    class Lqr
    {
    public:
        explicit Lqr(const LqrConfig<dz, du> &config) : K(config.K), Umax(config.Umax) {}
        ~Lqr() = default;

        void calc() { U = -K * Z; }
        int dim_z() { return dz; }
        int dim_u() { return du; }
        float *get_z_point() { return Z[0]; }
        float *get_u_point() { return U[0]; }

    private:
        Lqr() = delete; // must init
        Lqr(const Lqr &) = delete; // uncopyable
        Lqr &operator=(const Lqr &) = delete; // uncopyable

        Matrixf<1, dz> Z;
        Matrixf<1, du> U;
        const Matrixf<du, dz> K;
        const Matrixf<1, du> Umax;

    };
}
