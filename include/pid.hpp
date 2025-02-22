#ifndef PID_HPP
#define PID_HPP
#include "struct.hpp"

// Just the P part for now
class PIDController {
public:
    PIDController(PIDParams pid_params): _pid_params(pid_params) {};

    double compute(double target, double current) {
        double error = target - current;
        return _pid_params.Kp * error + _pid_params.Ki * 0 + _pid_params.Kd * 0;
    }

private:
    PIDParams _pid_params;
};

#endif
