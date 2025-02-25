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
```terminal
Running
Reading the settings.
dt: 0.01
simulation_time: 10
gravity: 9.81
drag_coefficient: 0.1
target_altitude: 10
pid_kp: 2
pid_ki: 0.5
pid_kd: 1
Settings are loaded.
Trust: 20 Atl: 0.001019
Trust: 19.998 Atl: 0.00305669
Trust: 19.9939 Atl: 0.00611236
Trust: 19.9878 Atl: 0.0101849
Trust: 19.9796 Atl: 0.0152727
Trust: 19.9695 Atl: 0.0213739
Trust: 19.9573 Atl: 0.028486
Trust: 19.943 Atl: 0.0366064
...
Trust: 13.1258 Atl: 3.4178
Trust: 13.1644 Atl: 3.3989
Trust: 13.2022 Atl: 3.38037
^C
Caught signal 2 (SIGINT). Exiting safely...
Execution is finished
```