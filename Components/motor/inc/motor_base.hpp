#pragma once

namespace Motor
{
    // base class : motor
    template <typename T, typename T_imp>
    class MotorBase
    {
    public:
        explicit MotorBase() = default;
        virtual ~MotorBase() = default;

        virtual bool ctrl(const T ctrl_val) const = 0;

    // protected:
#warning "protected? reference(&)?"
        T_imp *pimp; // implement

    private:
        
    };

    // base class : implement for motor (T_imp in MotorBase, designed for compatible with different platform)
    class MotorImpBase
    {
    public:
        explicit MotorImpBase() = default;
        virtual ~MotorImpBase() = default;

        // overload the following functions in derived class, do not use them directly
        void run();
        void fbk();

    };

    // base class : motor with feedback 
    template <typename T, typename T_imp>
    class FbkMotorBase : public MotorBase<T, T_imp>
    {
    public:
        explicit FbkMotorBase() = default;
        virtual ~FbkMotorBase() = default;

        void update(const float speed, const float angle)
        {
            speed_ = speed;
            angle_ = angle;
        }
        float get_speed() const { return speed_; }
        float get_angle() const { return angle_; }

        bool feedback();

    private:
        float speed_ = 0.0f;
        float angle_ = 0.0f;
        
    };
} // namespace Motor 

