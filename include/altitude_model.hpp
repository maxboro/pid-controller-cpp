#ifndef ALT_MODEL_HPP
#define ALT_MODEL_HPP
#include "struct.hpp"

class AltitudeModel {
public:
    AltitudeModel(SimParams sim_params): _sim_params(sim_params){
        _aircraft_state = AircraftState();
    };

    double get_altitude(double thrust){

        // Physics → Calculate net force
        double gravity_force = _aircraft_state.mass * _sim_params.gravity;
        double drag_force = _sim_params.drag_coefficient * _aircraft_state.velocity * std::abs(_aircraft_state.velocity);
        double net_force = thrust - gravity_force - drag_force;

        // Update aircaft state
        _aircraft_state.acceleration = net_force / _aircraft_state.mass;
        _aircraft_state.velocity += _aircraft_state.acceleration * _sim_params.dt;
        _aircraft_state.altitude += _aircraft_state.velocity * _sim_params.dt;
        if (_aircraft_state.altitude < 0){
            _aircraft_state.altitude = 0;
            if (_aircraft_state.velocity < 0){
                _aircraft_state.velocity = 0;
            }
        }
        return _aircraft_state.altitude;
    }
private:
    SimParams _sim_params;
    AircraftState _aircraft_state;
};

#endif
