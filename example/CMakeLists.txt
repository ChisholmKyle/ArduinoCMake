cmake_minimum_required (VERSION 2.6)
project (ArduinoCMakeExample)

if(NOT ARDUINO_CMAKE)
    message(FATAL_ERROR "Variable ARDUINO_CMAKE not set")
endif()

# ################ #
# command example #
# ################ #

# Setup
# -----
# in ~/.profile set environment variables ARDUINO_ROOT and ARDUINO_CMAKE

# Compile
# -------
# mkdir build && cd build
# cmake -G "Unix Makefiles" .. \
#     -DCMAKE_TOOLCHAIN_FILE="${ARDUINO_CMAKE}/AVRtoolchain.cmake" \
#     -DARDUINO_ROOT="${ARDUINO_ROOT}" \
#     -DARDUINO_CMAKE="${ARDUINO_CMAKE}"
#    make

# ################ #
# general settings #
# ################ #

# specify target name
set(FIRMWARE_TARGET firmware)

# ################ #
# arduino settings #
# ################ #

# board settings
# --------------

# arduino board
set(ARDUINO_BOARD_NAME "ProMini5V328")

# upload port
set(ARDUINO_PORT "/dev/ttyUSB0")

# baud rate - serial communications
set(ARDUINO_SERIAL_SPEED "115200")

# ######### #
# libraries #
# ######### #

# var full printf functionality
# -----------------------------
# set(ARDUINO_AVR_PRINTF_FULL True)

# core libraries
# --------------
# set(ARDUINO_CORE_LIBRARIES "Wire")

# extra libraries
# ---------------
# set(ARDUINO_LIBS_SEARCHPATH "../")
# set(ARDUINO_LIBS "ard_utils")

# ############## #
# Arduino script #
# ############## #

# arduino cmake script
include("${ARDUINO_CMAKE}/Arduino.cmake")

# ##################### #
# Firmware source files #
# ##################### #

# Include files
include_directories("${PROJECT_SOURCE_DIR}")

# sources
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp"
                  "${PROJECT_SOURCE_DIR}/*.c")

# target
add_executable(${FIRMWARE_TARGET}
    ${SOURCES}
    ${ARDUINO_SOURCE_FILES})
