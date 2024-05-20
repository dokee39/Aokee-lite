#pragma once

namespace Motor
{
    // base class : implement for motor, and its derived class should inherite a motor class
    class MotorImpBase
    {
    public:
        explicit MotorImpBase() = default;
        virtual ~MotorImpBase() = 0;

        // override the following functions in derived class
        virtual bool run() = 0;
        virtual bool fbk() = 0;

    private:
        // MotorImpBase(const MotorImpBase &) = delete; // uncopyable
        MotorImpBase &operator=(const MotorImpBase &) = delete; // uncopyable

    };

    // base class : motor
    class MotorBase
    {
    public:
        explicit MotorBase(MotorImpBase &imp) : imp(imp) {}
        virtual ~MotorBase() = 0;

        virtual bool ctrl() = 0;

    protected:
        MotorImpBase &imp; // implement, reference to derived MotorImp class itself

    private:
        MotorBase() = delete;
        MotorBase(const MotorBase &) = delete; // uncopyable
        MotorBase &operator=(const MotorBase &) = delete; // uncopyable

    };

    // base class : motor with feedback
    class FbkMotorBase : public MotorBase
    {
    public:
        explicit FbkMotorBase(MotorImpBase &imp) : MotorBase(imp) {}
        ~FbkMotorBase() override = 0;

        void update(const float speed_, const float angle_)
        {
            speed = speed_;
            angle = angle_;
        }
        float get_speed() const { return speed; }
        float get_angle() const { return angle; }

        virtual bool feedback();

    private:
        FbkMotorBase() = delete;

        float speed = 0.0f;
        float angle = 0.0f;

    };
} // namespace Motor 

