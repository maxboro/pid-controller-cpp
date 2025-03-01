#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <atomic>
#include <csignal>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

// project
#include "settings.hpp"
#include "struct.hpp"
#include "pid.hpp"
#include "altitude_model.hpp"
#include "gui.hpp"

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
    AircraftParams aircraft_params = settings->get_aircraft_params();

    auto pid = PIDController(pid_params);
    auto aircraft_state = AircraftState();
    auto alt_model = AltitudeModel(sim_params, aircraft_params);
    double pid_target_thrust;

    // For rendering plot
    auto alt_log_ptr = std::make_shared<std::vector<double>>();
    auto t_log_ptr = std::make_shared<std::vector<double>>();
    auto mutex_ptr = std::make_shared<std::mutex>();
    std::thread render_thread(render, alt_log_ptr, t_log_ptr, mutex_ptr, &stop_flag);

    for (double t = 0; t <= sim_params.simulation_time; t += sim_params.dt) {
        pid_target_thrust = pid.compute(sim_params.target_altitude, aircraft_state.altitude, sim_params.dt);
        alt_model.update_model(pid_target_thrust, aircraft_state);

        // save alt to log for renderer
        {
            std::lock_guard<std::mutex> lock(*mutex_ptr);
            alt_log_ptr->push_back(aircraft_state.altitude);
            t_log_ptr->push_back(t);
        }

        // print status
        std::cout << "Thrust (PID): " << pid_target_thrust \
            << " Thrust (real): " << aircraft_state.thrust \
            << " Alt: " << aircraft_state.altitude << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // save exit
        if (stop_flag.load()){
            break;
        }
    }

    render_thread.join();
    std::cout << "Execution is finished" << std::endl;
    return 0;
}

#endif
