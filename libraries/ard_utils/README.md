# ArdUtils

Utilities for Arduino. The library provides a C code API for i2C devices, serial communications, PID control, filtering, spline functions, etc.

## Usage

See [ArduinoCMake](https://www.github.com/ChisholmKyle/ArduinoCMake) to set up a programming and toolchain environment for your Arduino. In your CMakeFileLists.txt, make sure the following lines are included after `include("Arduino")`:

    include("ArduinoLibraryWire")
    include("ArduinoLibraryArdUtils")

Compile and upload following instructions from [ArduinoCMake](https://www.github.com/ChisholmKyle/ArduinoCMake).

## Summary

| Header | Description |
| ------ | ----------- |
| [ard_crc.h](include/ard_crc.h) | Cyclic Redundancy Check |
| [ard_i2c.h](include/ard_i2c.h) | C wrapper for I2C communications |
| [ard_mpu6050.h](include/mpu_6050.h) | C wrapper for I2C communications with the MPU6050 IMU |
| [ard_pid.h](include/ard_pid.h) | Discrete PID controller |
| [ard_pot.h](include/ard_pot.h) | Potentiometer analog input utility functions |
| [ard_serial.h](include/ard_serial.h) | Serial communications with CRC and simple packets |
| [ard_sos.h](include/ard_sos.h) | Digital Second Order Systems filters |
| [ard_spline.h](include/ard_spline.h) | Fourth-order spline function evaluation |
| [ard_timing.h](include/ard_timing.h) | Simple polling timer (without interrupts) |
| [ard_traj.h](include/ard_traj.h) | Simple sequencer and trajectory generator |

## Compatibility With Scientific Computing Software

The digital filtering, PID controllers, and spline function evaluations are all compatible with parameters output from Matlab/Octave/Scipy. Example Python scripts (using Scipy) to generate appropriate constants and parameters for these modules are provided in the [py/examples](py/examples) subfolder.
