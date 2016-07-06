cmake_minimum_required (VERSION 2.6)
project (ArduinoCMakeExample)

# ################ #
# command examples #
# ################ #

# make sure avr-gcc is in PATH, and environemnt variable ARDUINO_ROOT is set
# then run the following command:
# cmake -G "Unix Makefiles" .. \
#       -DCMAKE_TOOLCHAIN_FILE=cmake/AVRtoolchain.cmake 
#       -DARDUINO_ROOT="${ARDUINO_ROOT}"

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
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# arduino board
include("ArduinoProMini5V328")
# upload port and serial picocom communications settings
set(ARDUINO_PORT "/dev/tty.usbmodemXXXXXX")
set(ARDUINO_SERIAL_SPEED "115200")
# arduino cmake script
include("Arduino")
# optional Wire library to include
include("ArduinoLibraryWire")

# ##################### #
# Firmware source files #
# ##################### #

# Include files
include_directories("${CMAKE_SOURCE_DIR}/include")

# sources
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# target
add_executable(${FIRMWARE_TARGET}
	${SOURCES}
	${ARDUINO_SOURCE_FILES})
