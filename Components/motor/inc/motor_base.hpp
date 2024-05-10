#pragma once

namespace Motor
{
    // base class : motor
    template <typename T, typename T_run>
    class MotorBase
    {
    public:
        explicit MotorBase(const T_run run) :run_(run) {}
        virtual ~MotorBase() = default;

        virtual bool ctrl(const T ctrl_val) const = 0;

    protected:
        const T_run run_;

    private:
        MotorBase(); // must init
        
    };

    // base class : motor with feedback 
    template <typename T, typename T_run, typename T_fbk>
    class FbkMotorBase : public MotorBase<T, T_run>
    {
    public:
        explicit FbkMotorBase(const T_run run, const T_fbk fbk)
            : MotorBase<T, T_run>(run),
              fbk_(fbk),
              speed_(0.0f),
              angle_(0.0f) {
        }
        virtual ~FbkMotorBase() = default;

        void update(const float speed, const float angle)
        {
            speed_ = speed;
            angle_ = angle;
        }
        float get_speed() const { return speed_; }
        float get_angle() const { return angle_; }

        bool feedback();

    protected:
        const T_fbk fbk_;

    private:
        float speed_;
        float angle_;
        
        FbkMotorBase(); // must init
    };
} // namespace Motor 

