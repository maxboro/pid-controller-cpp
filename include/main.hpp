#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <atomic>
#include <csignal>
#include "settings.hpp"

// Global atomic flag to signal threads to stop
std::atomic<bool> stop_flag(false);

void handle_sigint(int signal) {
    printf("\nCaught signal %d (SIGINT). Exiting safely...\n", signal);
    stop_flag.store(true);
}

int main(){
    std::cout << "Running" << std::endl;

    // Load params from settings
    Settings* settings = Settings::get_instance();
    settings->load_settings();

    // Register the signal handler
    std::signal(SIGINT, handle_sigint);

    std::cout << "Execution is finished" << std::endl;
    return 0;
}

#endif
