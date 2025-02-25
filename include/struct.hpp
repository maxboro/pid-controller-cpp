#ifndef STRUCT_HPP
#define STRUCT_HPP

struct PIDParams {
    double Kp;
    double Ki;
    double Kd;
};

struct SimParams {
    double dt;
    double simulation_time;
    double gravity;
    double drag_coefficient;
    double target_altitude;
};

struct AircraftState {
    double mass = 1.0;         // kg
    double altitude = 0.0;     // meters
    double velocity = 0.0;     // m/s
    double acceleration = 0.0; // m/s^2
};

#endif
