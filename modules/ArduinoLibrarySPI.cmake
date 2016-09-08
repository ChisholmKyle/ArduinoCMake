
# Arduino directories
set(ARDUINO_SPI_DIR "${ARDUINO_ROOT}/hardware/arduino/avr/libraries/SPI/src")

# Wire headers
include_directories(${ARDUINO_SPI_DIR})

# Wire source files
file(GLOB ARDUINO_SPI_SOURCE_FILES
	${ARDUINO_SPI_DIR}/*.S
	${ARDUINO_SPI_DIR}/*.c
	${ARDUINO_SPI_DIR}/*.cpp)

list(APPEND ARDUINO_SOURCE_FILES ${ARDUINO_SPI_SOURCE_FILES})
