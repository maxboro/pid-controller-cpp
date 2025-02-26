#ifndef ALT_MODEL_HPP
#define ALT_MODEL_HPP
#include <algorithm>
#include "struct.hpp"

class AltitudeModel {
public:
    AltitudeModel(
        const SimParams &sim_params, 
        const AircraftParams &aircraft_params
    ): _sim_params(sim_params), _aircraft_params(aircraft_params){};

    double update_model(double pid_target_thrust, AircraftState &aircraft_state){
        // Check if PID calculated desired thrust is achievable by particular aircraft
        aircraft_state.thrust = std::clamp(pid_target_thrust, _aircraft_params.min_thrust, _aircraft_params.max_thrust);

        // Physics → Calculate net force
        double gravity_force = _aircraft_params.mass * _sim_params.gravity;
        double drag_force = _sim_params.drag_coefficient * aircraft_state.velocity * std::abs(aircraft_state.velocity);
        double net_force = aircraft_state.thrust - gravity_force - drag_force;

        // Update aircraft state
        aircraft_state.acceleration = net_force / _aircraft_params.mass;
        aircraft_state.velocity += aircraft_state.acceleration * _sim_params.dt;
        aircraft_state.altitude += aircraft_state.velocity * _sim_params.dt;
        if (aircraft_state.altitude < 0){
            aircraft_state.altitude = 0;
            if (aircraft_state.velocity < 0){
                aircraft_state.velocity = 0;
            }
        }
        return aircraft_state.altitude;
    }
private:
    SimParams _sim_params;
    AircraftParams _aircraft_params;
};

#endif
