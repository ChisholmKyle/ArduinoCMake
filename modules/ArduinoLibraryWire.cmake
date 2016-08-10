
# Arduino directories
set(ARDUINO_WIRE_DIR "${ARDUINO_ROOT}/hardware/arduino/avr/libraries/Wire/src")

# Wire headers
include_directories(${ARDUINO_WIRE_DIR})
include_directories(${ARDUINO_WIRE_DIR}/utility)

# Wire source files
file(GLOB ARDUINO_WIRE_SOURCE_FILES
    ${ARDUINO_WIRE_DIR}/utility/*.S
    ${ARDUINO_WIRE_DIR}/utility/*.c
    ${ARDUINO_WIRE_DIR}/utility/*.cpp
	${ARDUINO_WIRE_DIR}/*.S
	${ARDUINO_WIRE_DIR}/*.c
	${ARDUINO_WIRE_DIR}/*.cpp)

list(APPEND ARDUINO_SOURCE_FILES ${ARDUINO_WIRE_SOURCE_FILES})
