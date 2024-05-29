#pragma once

#include <any>

namespace Motor {
// base class : implement for motor, and its derived class should inherite a motor class
class MotorImplBase {
public:
    explicit MotorImplBase() = default;
    virtual ~MotorImplBase() = default;

    // override the following functions in derived class
    virtual bool msg_out(std::any a_ctrl_val) = 0;
    virtual bool msg_in(std::any a_fbk_val) = 0;

private:
    MotorImplBase(const MotorImplBase&) = delete; // uncopyable
    MotorImplBase& operator=(const MotorImplBase&) = delete; // uncopyable
};

// base class : motor
class MotorBase {
public:
    explicit MotorBase(MotorImplBase& impl): impl(impl) {}
    virtual ~MotorBase() = default;

    virtual bool ctrl() = 0;
    virtual bool feedback() = 0;

    void update(const float speed_, const float angle_) {
        speed = speed_;
        angle = angle_;
    }
    float get_speed() const {
        return speed;
    }
    float get_angle() const {
        return angle;
    }

    // for compatibility.
    // if there are additional values for control, 
    // please set them using a member function of derived class in other places like robot.update_set_task() 
    float ctrl_val = 0.0f;

protected:
    MotorImplBase& impl;

private:
    explicit MotorBase() = delete;
    MotorBase(const MotorBase&) = delete; // uncopyable
    MotorBase& operator=(const MotorBase&) = delete; // uncopyable


    float speed = 0.0f;
    float angle = 0.0f;
};

template<typename Tcfg> // wait for specialization for different types of chassis
class MotorImpl: public MotorImplBase {
public:
    explicit MotorImpl(const Tcfg& config);
    ~MotorImpl() override = default;

private:
    MotorImpl() = delete; // must init
};

template<typename Tcfg> // wait for specialization for different types of chassis
class Motor: public MotorBase {
public:
    explicit Motor(const Tcfg& config, MotorImplBase& impl);
    ~Motor() override = default;

private:
    Motor() = delete; // must init
};

} // namespace Motor
