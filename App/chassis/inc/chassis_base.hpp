#pragma once

#include <memory>
#include <vector>

namespace Chassis
{
    struct Status {
        explicit Status(float vx, float vy, float wz) :vx_(vx),vy_(vy),wz_(wz) {}
        explicit Status();

        float vx_ = 0.0f;
        float vy_ = 0.0f;
        float wz_ = 0.0f;
    };

    template <typename T>
    class ChassisBase
    {
    public:
        explicit ChassisBase();
        virtual ~ChassisBase() = default;

        void update_ref(Status &ref) { ref_ = ref; }
        void update_set(Status &set) { set_ = set; }
        const Status &get_ref() const { return ref_; };
        const Status &get_set() const { return set_; };

        [[noreturn]] void task(void* arg);

    protected:
        std::vector<std::shared_ptr<T>> pmotors;

        virtual void update_state() = 0;
        virtual void ctrl_val_calc() = 0;
        virtual void ctrl() = 0;
        virtual void task_delay_until() const = 0;

    private:
        Status ref_;
        Status set_;

    };
}



