#pragma once

#include <memory>
#include <vector>

#include "motor_base.hpp"

namespace Chassis
{
    struct Status {
        explicit Status(float vx, float vy, float wz) :vx_(vx),vy_(vy),wz_(wz) {}
        explicit Status() = default;

        float vx_ = 0.0f;
        float vy_ = 0.0f;
        float wz_ = 0.0f;
    };

    class ChassisBase
    {
    public:
        explicit ChassisBase() = default;
        virtual ~ChassisBase() = default;

        void update_ref(Status &ref) { ref_ = ref; }
        void update_set(Status &set) { set_ = set; }
        const Status &get_ref() const { return ref_; };
        const Status &get_set() const { return set_; };

        virtual void init() = 0;
        [[noreturn]] virtual void task(void* arg) final;

    protected:
        virtual void update_state() = 0;
        virtual void ctrl_val_calc() = 0;
        virtual void ctrl() = 0;
        virtual void task_delay_until() const = 0;

        std::vector<std::shared_ptr<Motor::MotorBase>> motors;

    private:
        ChassisBase(const ChassisBase &) = delete; // uncopyable
        ChassisBase &operator=(const ChassisBase &) = delete; // uncopyable
        Status ref_;
        Status set_;

    };
}



