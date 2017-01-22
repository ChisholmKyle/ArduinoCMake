
# Arduino directories
set(ARDUINO_EEPROM_DIR "${ARDUINO_ROOT}/hardware/arduino/avr/libraries/EEPROM/src")

# EEPROM headers
include_directories(${ARDUINO_EEPROM_DIR})

# EEPROM source files
# file(GLOB ARDUINO_EEPROM_SOURCE_FILES
# 	${ARDUINO_EEPROM_DIR}/*.S
# 	${ARDUINO_EEPROM_DIR}/*.c
# 	${ARDUINO_EEPROM_DIR}/*.cpp)

# list(APPEND ARDUINO_SOURCE_FILES ${ARDUINO_EEPROM_SOURCE_FILES})
