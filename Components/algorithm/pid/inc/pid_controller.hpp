#pragma once

namespace Pid
{
    struct PidConfig
    {
        explicit PidConfig(float kp, float ki, float kd, float max_out, float max_iout)
            : kp(kp),
              ki(ki),
              kd(kd),
              max_out(max_out),
              max_iout(max_iout) {
        }
        ~PidConfig();

    protected:
        float kp;
        float ki;
        float kd;

        float max_out;
        float max_iout;
    };

    class Pid : public PidConfig
    {
    public:
        explicit Pid(const PidConfig &config)
            :PidConfig(config)
        {}
        ~Pid() = default;

        void calc(float ref, float set);
        void clean();
        float get_out() const { return out_; }

    private:
        float err_[2] = {};  // 误差项 0最新 1上一次 2上上次

        float Pout_ = 0.f;
        float Iout_ = 0.f;
        float Dout_ = 0.f;

        float out_ = 0.f;

    };

}  // namespace Pid

