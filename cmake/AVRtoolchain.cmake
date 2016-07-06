##########################################################################
# executables in use
##########################################################################
find_program(AVR_CC avr-gcc)
find_program(AVR_CXX avr-g++)
if (NOT AVR_CC)
    message(FATAL_ERROR "Please install avr-gcc")
endif ()
if (NOT AVR_CXX)
    message(FATAL_ERROR "Please install avr-g++")
endif ()

##########################################################################
# toolchain starts with defining mandatory variables
##########################################################################
set(CMAKE_SYSTEM_NAME Generic)
# set(CMAKE_SYSTEM_PROCESSOR avr)

set(CMAKE_ASM_COMPILER ${AVR_CC})
set(CMAKE_C_COMPILER ${AVR_CC})
set(CMAKE_CXX_COMPILER ${AVR_CXX})

# no flags
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CMAKE_CXX_LINK_FLAGS "")

# set paths
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

if(AVR_FIND_ROOT_PATH)
	# not added automatically, since CMAKE_SYSTEM_NAME is "generic"
	set(CMAKE_SYSTEM_INCLUDE_PATH "${AVR_FIND_ROOT_PATH}/include")
	set(CMAKE_SYSTEM_LIBRARY_PATH "${AVR_FIND_ROOT_PATH}/lib")
endif()
