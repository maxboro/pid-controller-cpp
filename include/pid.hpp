#ifndef PID_HPP
#define PID_HPP
#include "struct.hpp"

class PIDController {
public:
    PIDController(const PIDParams &pid_params): _pid_params(pid_params) {
        _error_integral = 0;
        _is_first_run = true;
    };

    // PID calculated desired thrust in this case
    double compute(double target, double current, double dt) {
        double _error_derivative;
        double error = target - current;
        _error_integral += error * dt;

        // derivative
        if (_is_first_run){
            _error_derivative = 0;
            _is_first_run = false;
        } else {
            _error_derivative = (error - _prev_error) / dt;
        }
        _prev_error = error;

        // all components
        double p_error = _pid_params.Kp * error;
        double i_error = _pid_params.Ki * _error_integral;
        double d_error = _pid_params.Kd * _error_derivative;
        return p_error + i_error + d_error;
    }

private:
    PIDParams _pid_params;
    bool _is_first_run;
    double _error_integral;
    double _prev_error;
};

#endif
