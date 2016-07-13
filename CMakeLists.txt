cmake_minimum_required (VERSION 2.6)
project (ArduinoCMakeExample)

if(NOT ARDUINO_ROOT)
    message(FATAL_ERROR "Variable ARDUINO_ROOT not set")
endif()
if(NOT ARDUINO_CMAKE)
    message(FATAL_ERROR "Variable ARDUINO_CMAKE not set")
endif()

# ################ #
# command example #
# ################ #

# 1. make sure avr-gcc is in PATH
# 2. set environment variables ARDUINO_ROOT and ARDUINO_CMAKE
# 3. run the following command:
# cmake -G "Unix Makefiles" .. 
#       -DCMAKE_TOOLCHAIN_FILE="${ARDUINO_CMAKE}/AVRtoolchain.cmake" 
#       -DARDUINO_ROOT="${ARDUINO_ROOT}" 
#       -DARDUINO_CMAKE="${ARDUINO_CMAKE}"

# tested with:
#    Windows MYS2 shell
#    Apple with Macports avr-gcc
#    Debian 8 with avr-gcc

# specify target name
set(FIRMWARE_TARGET firmware)

# ################ #
# arduino settings #
# ################ #

# arduino cmake modules folder
# ----------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ARDUINO_CMAKE}/modules")

# arduino board
include("ArduinoProMini5V328")
# upload port and serial picocom communications settings
set(ARDUINO_PORT "COM3")
set(ARDUINO_SERIAL_SPEED "115200")
# arduino cmake script
include("Arduino")
# optional Wire library to include (from Arduino)
# include("ArduinoLibraryWire")

# ################ #
# custom libraries #
# ################ #

# optional custom library to include
# include("ArduinoLibraryArdUtils")

# ##################### #
# Firmware source files #
# ##################### #

# Include files
include_directories("${PROJECT_SOURCE_DIR}/include")

# sources
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp"
                  "${PROJECT_SOURCE_DIR}/src/*.c")

# target
add_executable(${FIRMWARE_TARGET}
	${SOURCES}
	${ARDUINO_SOURCE_FILES})
