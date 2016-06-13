cmake_minimum_required (VERSION 2.6)
project (ArduinoCMakeExample)

# specify target name
set(FIRMWARE_TARGET firmware)

# ################ #
# arduino settings #
# ################ #

# arduino cmake and library folders
set(ARDUINO_ROOT "/Applications/Arduino.app/Contents/Java")
set(ARDUINO_CMAKE_DIR "${CMAKE_SOURCE_DIR}/cmake")

# arduino board
include("${ARDUINO_CMAKE_DIR}/ArduinoProMini5V328.cmake")
# upload port and serial picocom communications settings
set(ARDUINO_PORT "/dev/tty.usbmodemXXXXXX")
set(ARDUINO_SERIAL_SPEED "115200")
# arduino cmake script
include("${ARDUINO_CMAKE_DIR}/Arduino.cmake")
# optional Wire library to include
include("${CMAKE_SOURCE_DIR}/cmake/ArduinoLibraryWire.cmake")

# Include files
include_directories("${CMAKE_SOURCE_DIR}/include")

# sources
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# target
add_executable(${FIRMWARE_TARGET}
	${SOURCES}
	${ARDUINO_SOURCE_FILES})
