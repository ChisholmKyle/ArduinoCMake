# ArduinoCMake
A simple CMake build project for Arduino

## Prerequisites

Toolchains and libraries:

- [Arduino](https://www.arduino.cc/en/Main/Software)
- git
- cmake
- GNU make
- Amtel AVR toolchain (gcc-avr)

In order to flash your Arduino, you need

- avrdude

In order to communicate with you Arduino through a serial connection, you need

- picocom (Unix-like OS only)

Installing [Arduino](https://www.arduino.cc/en/Main/Software) for your system is easy, but other prerequisites may be more difficult. The instructions below may be followed below to use *nix-like development tools and environments.

### Linux (Debian 8)

Your flavour of Linux may have different package managers and names for the prerequisites.

1. Install prerequisites with the command `sudo apt-get install git gcc-avr binutils-avr avr-libc avrdude picocom cmake make`
1. Set the Arduino path environment variable `export ARDUINO_ROOT="/opt/arduino"`. Note that this directory is likely different for your installed Arduino library.
1. Set your board and serial port, then compile the example (see below).

### Apple (Macports)

If you want a package manager for Mac, [Macports](https://www.macports.org/) may be the right choice for you. [iTerm2](https://www.iterm2.com/) is also highly recommended as a terminal.

1. Install and update [Macports](https://www.macports.org/)
1. Install prerequisites with the command `sudo port install git avr-gcc avr-binutils avr-libc avrdude picocom cmake gmake`
1. Set the Arduino path environment variable `export ARDUINO_ROOT="/Applications/Arduino.app/Contents/Java"`. Note that this directory may be different for your installed Arduino library.
1. Set your board and serial port, then compile the example (see below).

### Windows (MSYS2)

This is not the only way to use Arduino and CMake on Windows, but it is likely a good choice for you if you're comfortable with Linux or Mac OS X.

1. Install and update [MSYS2](https://msys2.github.io/)
1. Download and extract the [Amtel AVR 8-bit Toolchain for Windows](http://www.atmel.com/tools/atmelavrtoolchainforwindows.aspx). This example assumes you've put the contents in C:/avr8-gnu-toolchain
1. In your MSYS2 MinGW32 shell, install dependencies with the command: `pacman -Syu msys/git msys/make mingw32/mingw-w64-i686-cmake mingw32/mingw-w64-i686-avrdude`
1. Set your PATH to include the Amtel AVR toolchain with the command `export PATH=$PATH:/c/avr8-gnu-toolchain/bin`
1. Set the Arduino path environment variable `export ARDUINO_ROOT="/c/Program Files (x86)/Arduino"`. Note that this directory may be different for your installed Arduino library.
1. Set your board and serial port, then compile the example (see below).

## Set your board and serial communications

Refer to the [CMakeLists.txt](CMakeLists.txt) file for an example blink program. First you must set a name for the firmware you are building to the variable `FIRMWARE_TARGET`.

After the line `set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ARDUINO_CMAKE}/modules")` in your CMakeLists.txt file, set the board. Consult the [modules](modules/) subfolder in this repository for the various boards already defined that you can include (without the .cmake extension). The blink example lists `include("ArduinoProMini5V328")`. If you have an Uno, change this line to `include("ArduinoUno")`. The following table lists the boards available:

| Boards |
| ------ |
| ArduinoUno |
| ArduinoMega1280 |
| ArduinoMega2560 |
| ArduinoProMini3V168 |
| ArduinoProMini5V168 | 
| ArduinoProMini3V328 |
| ArduinoProMini5V328 |

The serial port for communications and uploading to the Arduino needs to be set with the variable `ARDUINO_PORT`. If serial communications are being used with the Arduino and picocom, the `ARDUINO_SERIAL_SPEED` needs to be set. The following table describes the variables:

| Serial | Notes |
| ---- | ----- |
| `ARDUINO_PORT` | Upload serial port. This may begin with `/dev/tty.usbmodem` on a Mac, `/dev/ttyUSB` on Linux, or `COM` in Windows, for example. |
| `ARDUINO_SERIAL_SPEED` | Serial communications baudrate speed for your Arduino. This is not the flash upload speed but rather the serial communications while running your code. |

After setting the above variables, include the [modules/Arduino.cmake](modules/Arduino.cmake) file by placing **include("Arduino")** in your CMakeLists.txt file. You must also set your target executable to depend on the list of Arduino sources like so:

    add_executable(${FIRMWARE_TARGET}
        ${SOURCES}
        ${ARDUINO_SOURCE_FILES})

where `SOURCES` is a list of your custom source files for your project and `ARDUINO_SOURCE_FILES` is the auto-generated list of Arduino core sources to compile.

## Compile the example

See the [CMakeLists.txt](CMakeLists.txt) file for an example blink program. Make sure the `ARDUINO_CMAKE` environment variable is set to the path containing this README. For example, run `export ARDUINO_CMAKE="/path/to/ArduinoCmake"`. Then run the following:

    git clone https://github.com/ChisholmKyle/ArduinoCMake.git
    cd ArduinoCMake && mkdir build && cd build
    cmake -G "Unix Makefiles" .. \
          -DCMAKE_TOOLCHAIN_FILE="${ARDUINO_CMAKE}/modules/AVRtoolchain.cmake" \
          -DARDUINO_ROOT="${ARDUINO_ROOT}" \ 
          -DARDUINO_CMAKE="${ARDUINO_CMAKE}"
    make hex

If you want to upload to your Arduino, run

    make flash

If you want to communicate with your Arduino and display serial data, make sure [`picocom`](https://github.com/npat-efault/picocom) is installed and run

    make serial

## Add your own board

See the include cmake file [modules/ArduinoProMini5V328.cmake](modules/ArduinoProMini5V328.cmake) for an example of board variables that need to be set. Consult the file **hardware/arduino/avr/boards.txt** in your Arduino root folder for setting the following variables in your custom board cmake file:

| Compile | Notes |
| ---- | ----- |
| `ARDUINO_PROTOCOL` | Bootloader protocol to upload your firmware.  Set `ARDUINO_PROTOCOL` to the `upload.protocol` value in **boards.txt** for your board |
| `ARDUINO_VARIANT` | Name which corresponds to your board variant type. Set `ARDUINO_VARIANT` to the `build.variant` value in **boards.txt** for your board.  |
| `ARDUINO_MCU` | MCU part definition. Set `ARDUINO_MCU` to the `build.mcu` value in **boards.txt** for your board. |
| `ARDUINO_FCPU` | Clock frequency. Set `ARDUINO_FCPU` to the `build.f_cpu` value in **boards.txt** for your board. |
| `ARDUINO_UPLOAD_SPEED` | Upload serial baud rate speed to flash your Arduino. Set `ARDUINO_UPLOAD_SPEED` to the `upload.speed` value in **boards.txt** for your board. |
