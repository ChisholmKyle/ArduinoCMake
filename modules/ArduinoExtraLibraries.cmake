
foreach(ARDUINO_CUSTOM_LIB_NAME in ${ARDUINO_EXTRA_LIBRARIES})

    if(NOT ARDUINO_CMAKE)
        message(FATAL_ERROR "Set the variable ARDUINO_CMAKE before including ArduinoLibraryArdUtils.cmake")
    endif()

    # directory
    # find_path(ARDUINO_CUSTOM_LIB_DIR
    #     name ${ARDUINO_CUSTOM_LIB_NAME}
    #     PATHS ${ARDUINO_CMAKE}/libraries)

    # if(NOT ARDUINO_CUSTOM_LIB_DIR)
    #     # not found
    #     message(FATAL_ERROR "Could not find ard_utils directory (${ARDUINO_CUSTOM_LIB_DIR}). Check that ${ARDUINO_CMAKE}/libraries contains ard_utils")
    # endif()

    # folder containing custom libraries
    set(ARDUINO_CUSTOM_LIB_DIR "${ARDUINO_CMAKE}/libraries")

    # headers
    include_directories(${ARDUINO_CUSTOM_LIB_DIR}/${ARDUINO_CUSTOM_LIB_NAME}/include)

    # source files
    file(GLOB ARDUINO_ARD_UTILS_SOURCE_FILES
    	${ARDUINO_CUSTOM_LIB_DIR}/${ARDUINO_CUSTOM_LIB_NAME}/src/*.S
    	${ARDUINO_CUSTOM_LIB_DIR}/${ARDUINO_CUSTOM_LIB_NAME}/src/*.c
    	${ARDUINO_CUSTOM_LIB_DIR}/${ARDUINO_CUSTOM_LIB_NAME}/src/*.cpp)
    # remove main
    list(REMOVE_ITEM ARDUINO_ARD_UTILS_SOURCE_FILES "${ARDUINO_CUSTOM_LIB_DIR}/${ARDUINO_CUSTOM_LIB_NAME}/src/main.cpp")

    list(APPEND ARDUINO_SOURCE_FILES ${ARDUINO_ARD_UTILS_SOURCE_FILES})

endforeach()