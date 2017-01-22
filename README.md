# ArduinoCMake
A simple CMake build project for Arduino and AVR microcontrollers.

## Prerequisites

- [Arduino](https://www.arduino.cc/en/Main/Software)
- git
- cmake
- GNU make
- Amtel AVR toolchain (gcc-avr)

In order to flash your Arduino, you need

- avrdude
- avr-binutils

In order to communicate with you Arduino through a serial connection, you need

- picocom (Unix-like OS only)

Installing [Arduino](https://www.arduino.cc/en/Main/Software) for your system is easy, but other prerequisites may be more difficult. The instructions below may be followed below to use *nix-like development tools and environments.

### Linux (Debian 8)

Note that your flavour of Linux may have different package managers and names for the prerequisites.

1. Install prerequisites with the command

    ```bash
    sudo apt-get install git gcc-avr binutils-avr avr-libc avrdude picocom cmake make`
    ```

### Apple (Macports)

If you want a package manager for Mac, [Macports](https://www.macports.org/) may be the right choice for you. [iTerm2](https://www.iterm2.com/) is also highly recommended as a terminal.

1. Install and update [Macports](https://www.macports.org/)
1. Install prerequisites with the command

    ```bash
    sudo port install git avr-gcc avr-binutils avr-libc avrdude picocom cmake gmake
    ```

### Windows (Ubuntu Bash)

TODO: It would be interesting to try the (beta) [Windows 10 Linux/Ubuntu bash](https://msdn.microsoft.com/en-us/commandline/wsl/about) environment, especially if picocom can be used.

### Windows (MSYS2)

This is not the only way to use Arduino and CMake on Windows, but it is likely a good choice for you if you're comfortable with Linux or Mac OS X.

1. Install and update [MSYS2](https://msys2.github.io/)
1. Download and extract the [Amtel AVR 8-bit Toolchain for Windows](http://www.atmel.com/tools/atmelavrtoolchainforwindows.aspx).
1. Set your Windows PATH environment variable to include the Amtel AVR toolchain 'bin' directory.
1. In your MSYS2 MinGW32 shell, install dependencies with the command

    ```bash
    pacman -Syu msys/git msys/make mingw32/mingw-w64-i686-cmake mingw32/mingw-w64-i686-avrdude
    ```

## Compile Example

1. Follow instructions to install prerequisites (above), then clone and copy the example to a new folder called 'blink'

    ```bash
    git clone https://github.com/ChisholmKyle/ArduinoCMake.git
    cp -r ArduinoCMake/example blink
    ```

1. Set environment variable `ARDUINO_CMAKE` to the path of the root directory of this repository and `ARDUINO_ROOT` to the Arduino SDK. Note that the `ARDUINO_ROOT` directory may be different for your installed Arduino SDK.

    ```bash
    export ARDUINO_ROOT=/Applications/Arduino.app/Contents/Java
    export ARDUINO_CMAKE="$(pwd)/ArduinoCMake"
    ```

2. In the blink folder "CMakeLists.txt" file, set the `ARDUINO_PORT` and `ARDUINO_BOARD_NAME` to your serial port and board.

3. Compile using cmake in a subfloder named 'build'.

    ```bash
    cd blink && mkdir build && cd build
    cmake -G "Unix Makefiles" .. \
          -DCMAKE_TOOLCHAIN_FILE="${ARDUINO_CMAKE}/AVRtoolchain.cmake" \
          -DARDUINO_ROOT="${ARDUINO_ROOT}" \
          -DARDUINO_CMAKE="${ARDUINO_CMAKE}"
    make
    ```

3. If you want to upload to your Arduino, run

    ```bash
    make flash
    ```

3. If you want to communicate with your Arduino and display serial data, make sure [`picocom`](https://github.com/npat-efault/picocom) is installed and run

    ```bash
    make serial
    ```
    If you don't have picocom installed, you can use the Arduino IDE serial monitor instead.


## Configuration

### Environment variables


| Variable | Notes |
| ---- | ----- |
| `ARDUINO_ROOT` | Arduino SDK root directory. |
| `ARDUINO_CMAKE` | Path to this repository (ArduinoCMake). |


### Target, board, and serial communications

Refer to the [CMakeLists.txt](CMakeLists.txt) file for an example blink program. First you must set a name for the firmware you are building to the variable `FIRMWARE_TARGET`.

In your CMakeLists.txt file, set the board variable `ARDUINO_BOARD_NAME`. Consult the [modules](modules/) subfolder in this repository for the various boards already defined that you can include (without the "Arduino" prefix or .cmake extension). The blink example lists `set(ARDUINO_BOARD_NAME "ProMini5V328")`. If you have an Uno, change this line to `set(ARDUINO_BOARD_NAME "Uno")`. The following table lists the boards available:

| Board (`ARDUINO_BOARD_NAME`) |
| ------ |
| Uno |
| Mega1280 |
| Mega2560 |
| ProMini3V168 |
| ProMini5V168 |
| ProMini3V328 |
| ProMini5V328 |

The serial port for communications and uploading to the Arduino needs to be set with the variable `ARDUINO_PORT`. If serial communications are being used with the Arduino and picocom, the `ARDUINO_SERIAL_SPEED` needs to be set. The following table describes the variables:

| Variable | Notes |
| ---- | ----- |
| `ARDUINO_PORT` | Upload serial port. This may begin with `/dev/tty.usbmodem` on a Mac, `/dev/ttyUSB` on Linux, or `COM` in Windows, for example. |
| `ARDUINO_SERIAL_SPEED` | Serial communications baudrate speed for your Arduino. This is not the flash upload speed but rather the serial communications while running your code. |

### Add libraries

Add core libraries for Arduino and custom libraries. The following table lists the core libraries available:

| Core Libraries (`ARDUINO_CORE_LIBRARIES`) |
| ------ |
| Wire |
| SPI |
| EEPROM |

Add custom libraries for Arduino by setting `ARDUINO_LIBS_SEARCHPATH` and `ARDUINO_LIBS` in your CMakeLists.txt file. Source and header files will be added from the specified library folder and `src` and `include` subfolders. Note that this simply adds the include paths and source files. No special configuration options are performed.

| Variable | Notes |
| ---- | ----- |
| `ARDUINO_LIBS_SEARCHPATH` | List of serach paths that include custom libraries. |
| `ARDUINO_LIBS` | List of libraries to include which are also the subfolder names in the search paths `ARDUINO_LIBS_SEARCHPATH`. |

Consult the [modules](modules/) subfolder in this repository for the various core libraries already defined (cmake files are prefixed "ArduinoLibrary"). Please feel free to contribute and add other [core (Standard) libraries](https://www.arduino.cc/en/reference/libraries) from the Arduino SDK.

### Include Arduino sources for your executable

After setting the configuration variables and before adding your source files, include the [Arduino.cmake](Arduino.cmake) file by placing **include("${ARDUINO_CMAKE}/Arduino.cmake")** in your CMakeLists.txt file. You must also set your target executable to depend on the list of Arduino sources. In the blink example, we have:

    add_executable(${FIRMWARE_TARGET}
        ${SOURCES}
        ${ARDUINO_SOURCE_FILES})

where `SOURCES` is a list of your custom source files for your project and `ARDUINO_SOURCE_FILES` is the auto-generated list of Arduino core sources to compile (required).

## Add your own board

See the include cmake file [modules/ArduinoProMini5V328.cmake](modules/ArduinoProMini5V328.cmake) for an example of board variables that need to be set. Consult the file **hardware/arduino/avr/boards.txt** in your Arduino root folder for setting the following variables in your custom board cmake file:

| Compile | Notes |
| ---- | ----- |
| `ARDUINO_PROTOCOL` | Bootloader protocol to upload your firmware.  Set `ARDUINO_PROTOCOL` to the `upload.protocol` value in **boards.txt** for your board |
| `ARDUINO_VARIANT` | Name which corresponds to your board variant type. Set `ARDUINO_VARIANT` to the `build.variant` value in **boards.txt** for your board.  |
| `ARDUINO_MCU` | MCU part definition. Set `ARDUINO_MCU` to the `build.mcu` value in **boards.txt** for your board. |
| `ARDUINO_FCPU` | Clock frequency. Set `ARDUINO_FCPU` to the `build.f_cpu` value in **boards.txt** for your board. |
| `ARDUINO_EXTRA_FLAGS` | Compiler-specific flags for the board. Set `ARDUINO_FCPU` to the `build.extra_flags` value in **boards.txt** for your board. |
| `ARDUINO_UPLOAD_SPEED` | Upload serial baud rate speed to flash your Arduino. Set `ARDUINO_UPLOAD_SPEED` to the `upload.speed` value in **boards.txt** for your board. |
