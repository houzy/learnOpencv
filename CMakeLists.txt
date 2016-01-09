# - Enforce an out-of-source builds before anything else
#
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(STATUS "Requires an out-of-source build.")
    message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
    message(STATUS "CMakeCache.txt")
    message(STATUS "CMakeFiles")
    message(STATUS "Once these files are removed, create a separate directory")
    message(STATUS "and run CMake from there")
    message(FATAL_ERROR "in-source build detected")
endif()

#------------------------------------------------------------------------------
# - Define CMake requirements and override make rules as needed
#
cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)

# If Policy CMP0022 exists, use OLD
# to support versions < 2.8.12.
# This relates to LINK_INTERFACE_LIBRARIES and can be removed once
# minimum required CMake version reaches 2.8.12
if(POLICY CMP0022)
  cmake_policy(SET CMP0022 OLD)
endif()

# If Policy CMP0042 exists, use OLD to prefer the use of install names
# instead of the new @rpath default. This is temporary to suppress warnings
# on newer CMake versions.
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 OLD)
endif()

# If Policy CMP0043 exists, use OLD
# This relates to the use of generator expressions to set COMPILE_DEFINITIONS
# and can be removed once the minimum required CMake version reaches 2.8.10.
if(POLICY CMP0043)
  cmake_policy(SET CMP0043 OLD)
endif()

#----------------------------------------------------------------------------
# - Add functionality provided by standard and custom modules
# See the documentation in each of these modules for further details.
#
# - Versioning. We do this here for now
set(${PROJECT_NAME}_VERSION "0.1.0")
set(${PROJECT_NAME}_VERSION_MAJOR "0")
set(${PROJECT_NAME}_VERSION_MINOR "1")
set(${PROJECT_NAME}_VERSION_PATCH "0")

# Project name
PROJECT(Learn CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake-modules)

message(STATUS "TOP: ${CMAKE_SOURCE_DIR}")
message(STATUS "TOP: ${CMAKE_BINARY_DIR}")
message(STATUS "TOP: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "TOP: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "TOP: ${CMAKE_MODULE_PATH}")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

FIND_PACKAGE( OpenCV 3 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(src)

