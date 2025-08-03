% Problem: PID Controller Design for Pitch Attitude Control
% Aircraft: Boeing 737-like commercial aircraft
% Flight Condition: 35,000 ft, Mach 0.8

clear; clc; close all;

%% Aircraft Parameters
% Flight conditions
U0 = 250;           % Trim airspeed (m/s)
g = 9.81;           % Gravitational acceleration (m/s^2)

% Stability derivatives (given in problem statement)
Xu = -0.045;        % Speed stability (1/s)
Xalpha = 0;         % X-force due to angle of attack (1/s)
Xq = 0;             % X-force due to pitch rate (1/s)
Xdelta_e = 0;       % Elevator X-force effectiveness (1/s)

Zu = -0.27;         % Vertical force due to speed (1/s)
Zalpha = -1.3;      % Vertical force due to angle of attack (1/s)
Zq = 0;             % Vertical force due to pitch rate (1/s)
Zdelta_e = -0.44;   % Elevator vertical force effectiveness (1/s)

Mu = 0.0;           % Pitching moment due to speed (1/s^2)
Malpha = -0.7;      % Pitch stiffness (1/s^2)
Mq = -0.4;          % Pitch damping (1/s^2)
Mdelta_e = -1.28;   % Elevator control power (1/s^2)