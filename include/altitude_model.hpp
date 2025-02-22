#ifndef ALT_MODEL_HPP
#define ALT_MODEL_HPP
#include "struct.hpp"

class AltitudeModel {
public:
    AltitudeModel(SimParams sim_params): _sim_params(sim_params){};

    double get_altitude(){
        return 0;
    }
private:
    SimParams _sim_params;
};

#endif
