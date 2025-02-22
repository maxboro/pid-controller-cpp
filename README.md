# Description
Simple example of PID controller in C++.
PID used in simple aircraft 1D simulation (altitude only) to achieve desired altitude from point of start (0 altitude).

# How to run
#### Simulation:
```bash
make           # Builds the project
./bin/exec     # Runs the executable
```

#### Clean:
```bash
make clean     # Cleans up build files
```
# Settings
In file settings.txt you can modify simulation parameters.
- dt (default 0.01) - Time step of simulation
- simulation_time (default 10) - Total time of simulation
- gravity (default 9.81) - g value for simulation in m/s^2
- drag_coefficient (default 9.81) - drag coefficient for simulation
- target_altitude (default 10) - desired altitude
- pid_kp - PID parameter: Proportional gain
- pid_ki - PID parameter: Integral gain
- pid_kd - PID parameter: Derivative gain

# Example 
-