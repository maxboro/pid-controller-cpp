#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <atomic>
#include <csignal>
#include <memory>
#include <thread>
#include <chrono>
#include "settings.hpp"
#include "struct.hpp"
#include "pid.hpp"
#include "altitude_model.hpp"

// Global atomic flag to signal threads to stop
std::atomic<bool> stop_flag(false);

void handle_sigint(int signal) {
    std::cout << "\nCaught signal " << signal << " (SIGINT). Exiting safely..." << std::endl;
    stop_flag.store(true);
}


int main(){
    std::cout << "Running" << std::endl;

    // Register the signal handler
    std::signal(SIGINT, handle_sigint);

    // Load params from settings
    Settings* settings = Settings::get_instance();
    settings->load_settings();
    PIDParams pid_params = settings->get_pid_params();
    SimParams sim_params = settings->get_sim_params();

    auto pid = PIDController(pid_params);
    auto alt_model = AltitudeModel(sim_params);
    double current_alt;
    double thrust;

    for (double t = 0; t <= sim_params.simulation_time; t += sim_params.dt) {
        current_alt = alt_model.get_altitude();
        thrust = pid.compute(sim_params.target_altitude, current_alt);

        std::cout << "Trust: " << thrust << " Atl: " << current_alt << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (stop_flag.load()){
            break;
        }
    }

    std::cout << "Execution is finished" << std::endl;
    return 0;
}

#endif
