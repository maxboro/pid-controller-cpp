#ifndef STRUCT_HPP
#define STRUCT_HPP

struct PIDParams {
    double Kp;
    double Ki;
    double Kd;
};

struct SimParams {
    double dt;                // s
    double simulation_time;   // s
    double gravity;           // m/s^2
    double drag_coefficient;  // Newtons
    double target_altitude;   // meters
};

struct AircraftParams {
    double mass;          // kg
    double min_thrust;    // Newtons
    double max_thrust;    // Newtons
};

struct AircraftState {
    double altitude = 0.0;     // meters
    double velocity = 0.0;     // m/s
    double acceleration = 0.0; // m/s^2
    double thrust = 0.0;       // Newtons
};

#endif
