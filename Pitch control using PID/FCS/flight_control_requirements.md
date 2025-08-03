# Flight Control System Requirements Document
## Pitch Attitude Control System Design

**Document ID**: FCS-REQ-001  
**Version**: 1.0  
**Date**: August 2025  
**Classification**: Engineering Exercise

---

## 1. SYSTEM OVERVIEW

### 1.1 Purpose
Design and implement a pitch attitude control system for a commercial transport aircraft using PID control methodology.

### 1.2 Scope
This document defines requirements for an inner-loop pitch attitude controller that commands elevator deflection to track pilot or autopilot pitch attitude commands.

### 1.3 Aircraft Configuration
- **Aircraft Type**: Boeing 737-like commercial transport
- **Flight Condition**: Cruise at 35,000 ft altitude, Mach 0.8
- **Mass**: Nominal, mid-cruise weight
- **Configuration**: Clean (gear up, flaps up)

---

## 2. FUNCTIONAL REQUIREMENTS

### 2.1 Primary Function
**REQ-FN-001**: The pitch attitude control system SHALL command elevator deflection to track pitch attitude commands with specified performance.

**REQ-FN-002**: The system SHALL operate as a single-input, single-output (SISO) control loop.
- **Input**: Pitch attitude command (θ_cmd) in degrees
- **Output**: Elevator deflection command (δe_cmd) in degrees

### 2.2 Control Architecture
**REQ-FN-003**: The controller SHALL be implemented as a PID (Proportional-Integral-Derivative) control law in parallel form:
```
δe_cmd = Kp·e + Ki·∫e·dt + Kd·(de/dt) + bias
where e = θ_cmd - θ_actual
```

**REQ-FN-004**: The system SHALL include integrator anti-windup protection during actuator saturation.

---

## 3. PERFORMANCE REQUIREMENTS

### 3.1 Step Response Performance
**REQ-PERF-001**: For a step pitch attitude command, the closed-loop system SHALL meet:
- **Rise Time**: ≤ 3.0 seconds (10% to 90% of final value)
- **Settling Time**: ≤ 10.0 seconds (within ±2% of final value)  
- **Overshoot**: ≤ 15% of commanded step amplitude
- **Steady-State Error**: ≤ 0.1 degrees for constant commands

### 3.2 Command Following
**REQ-PERF-002**: The system SHALL track step commands of the following amplitudes:
- **Small commands**: ±2 degrees
- **Medium commands**: ±5 degrees  
- **Large commands**: ±10 degrees

**REQ-PERF-003**: All performance requirements SHALL be met for both positive and negative step commands.

### 3.3 Disturbance Rejection
**REQ-PERF-004**: The system SHALL reject atmospheric disturbances equivalent to:
- **Wind gusts**: Up to 2 m/s vertical velocity
- **Turbulence**: Light to moderate intensity
- **Recovery time**: ≤ 15 seconds to return within ±1 degree of command

---

## 4. STABILITY REQUIREMENTS

### 4.1 Stability Margins
**REQ-STAB-001**: The open-loop system (controller + aircraft) SHALL maintain:
- **Gain Margin**: ≥ 6.0 dB
- **Phase Margin**: ≥ 45 degrees
- **Stability**: All closed-loop poles in left-half plane

### 4.2 Robustness
**REQ-STAB-002**: Stability margins SHALL be maintained with aircraft parameter variations of:
- **Mass**: ±15% from nominal
- **Center of gravity**: ±5% MAC (mean aerodynamic chord)
- **Stability derivatives**: ±20% from nominal values

---

## 5. ACTUATOR REQUIREMENTS

### 5.1 Elevator Limits
**REQ-ACT-001**: Elevator deflection commands SHALL be limited to:
- **Maximum deflection**: +25 degrees (nose down)
- **Minimum deflection**: -25 degrees (nose up)
- **Rate limit**: 30 degrees/second (if implemented)

### 5.2 Saturation Handling
**REQ-ACT-002**: The controller SHALL include saturation limits and anti-windup protection to prevent:
- **Integrator windup** during actuator saturation
- **Performance degradation** when returning from saturation

---

## 6. AIRCRAFT MODEL REQUIREMENTS

### 6.1 Mathematical Model
**REQ-MODEL-001**: The aircraft dynamics SHALL be represented by the linearized longitudinal equations of motion in state-space form:

**State Vector**: x = [u, α, q, θ]ᵀ where:
- u = forward velocity perturbation (m/s)
- α = angle of attack (rad)  
- q = pitch rate (rad/s)
- θ = pitch attitude (rad)

**REQ-MODEL-002**: The system matrices SHALL use the following stability derivatives:

**Longitudinal Stability Derivatives**:
- Xu = -0.045 (1/s)
- Xα = 0.0 (1/s)  
- Xq = 0.0 (1/s)
- Xδe = 0.0 (1/s)
- Zu = -0.27 (1/s)
- Zα = -1.3 (1/s)
- Zq = 0.0 (1/s)  
- Zδe = -0.44 (1/s)
- Mu = 0.0 (1/s²)
- Mα = -0.7 (1/s²)
- Mq = -0.4 (1/s²)
- Mδe = -1.28 (1/s²)

**Flight Parameters**:
- U₀ = 250 m/s (trim airspeed)
- g = 9.81 m/s² (gravitational acceleration)

### 6.2 Initial Conditions
**REQ-MODEL-003**: Simulations SHALL start from trimmed flight conditions:
- Initial state: x₀ = [0, 0, 0, 0]ᵀ
- Initial elevator position: δe₀ = 0 degrees

---

## 7. SIMULATION REQUIREMENTS

### 7.1 Simulation Environment
**REQ-SIM-001**: The system SHALL be implemented and tested in MATLAB/Simulink environment.

**REQ-SIM-002**: Simulation parameters SHALL be:
- **Simulation time**: 30 seconds minimum
- **Solver**: Variable-step (ode45 or equivalent)
- **Relative tolerance**: 1e-6
- **Absolute tolerance**: 1e-9

### 7.2 Test Cases
**REQ-SIM-003**: The following test cases SHALL be executed:

**Step Response Tests**:
- Test 1: +5 degree step at t=2s
- Test 2: +10 degree step at t=2s  
- Test 3: -5 degree step at t=2s
- Test 4: -10 degree step at t=2s

**Robustness Tests**:
- Test 5: Repeat Test 1 with +20% increase in Mα
- Test 6: Repeat Test 1 with -20% decrease in Mα

### 7.3 Data Collection
**REQ-SIM-004**: The following signals SHALL be recorded during simulation:
- Pitch attitude command (degrees)
- Actual pitch attitude (degrees)  
- Pitch attitude error (degrees)
- Elevator deflection command (degrees)
- Control signal components (P, I, D terms)

---

## 8. DESIGN CONSTRAINTS

### 8.1 Controller Structure
**REQ-CONST-001**: Only classical PID control methodologies SHALL be used.

**REQ-CONST-002**: No advanced control techniques (LQR, H∞, adaptive, etc.) are permitted for this exercise.

### 8.2 Implementation Constraints  
**REQ-CONST-003**: The controller SHALL be implementable using standard Simulink blocks:
- PID Controller block, or
- Individual P, I, D blocks with manual tuning

**REQ-CONST-004**: No custom MATLAB functions or S-functions are required.

---

## 9. VERIFICATION REQUIREMENTS

### 9.1 Performance Verification
**REQ-VER-001**: All performance requirements SHALL be verified through simulation results demonstrating:
- Step response characteristics within specifications
- Stability margin calculations  
- Robustness with parameter variations

### 9.2 Analysis Requirements
**REQ-VER-002**: The following analyses SHALL be performed and documented:
- Open-loop aircraft analysis (poles, zeros, frequency response)
- Closed-loop performance analysis  
- Root locus or frequency domain design rationale
- PID gain selection justification

### 9.3 Documentation
**REQ-VER-003**: Results SHALL be documented including:
- Simulink model screenshot/block diagram
- Final PID gains (Kp, Ki, Kd)
- Performance metric summary table
- Time history plots for all test cases
- Engineering assessment of design adequacy

---

## 10. DELIVERABLES

### 10.1 Design Deliverables
1. **Simulink Model File**: Complete working model (.slx file)
2. **MATLAB Script**: Setup parameters and analysis code (.m file)  
3. **Design Report**: Technical documentation (PDF)
4. **Test Results**: Simulation plots and performance data

### 10.2 Design Report Contents
The design report SHALL include:
- Executive summary of design approach
- Aircraft model derivation and validation
- PID controller design methodology  
- Performance requirement verification
- Robustness analysis results
- Conclusions and recommendations

---

## 11. SUCCESS CRITERIA

### 11.1 Minimum Acceptable Performance
The design SHALL be considered successful if:
- All step response requirements are met (REQ-PERF-001)
- System remains stable for all test conditions
- Actuator limits are properly handled
- Robustness requirements are satisfied

### 11.2 Excellent Performance Targets
Exceptional designs will demonstrate:
- Settling time < 7 seconds
- Overshoot < 10%  
- Smooth control signals without excessive activity
- Graceful degradation under parameter variations

---

**END OF REQUIREMENTS DOCUMENT**

*This document provides complete specifications for designing a pitch attitude control system. The designer should implement the system in Simulink, tune the PID controller to meet all requirements, and document the results as specified.*