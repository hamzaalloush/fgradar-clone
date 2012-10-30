cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(FGRadar)

# Include our own cmake modules that aren't included in the default package.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

# Try to avoid in-source builds. Compares the binary directory with the
# source directory. If they are equal, it means the user is trying to build
# in-source.
if(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  message(FATAL_ERROR "In-source builds are not recommended, nor permitted. Instead, create a separate directory outside (or inside) ${CMAKE_SOURCE_DIR} and run CMake from there.
Please remove CMake generated files (CMakeCache.txt and CMakeFiles/).")
endif()

# Read VERSION file (located in the root directory, where this CMakeList.txt
# is located) and strip it.
file(READ VERSION VERSION_FILE)
if (NOT VERSION_FILE)
  message(FATAL_ERROR "Failed to determine version number. Check the VERSION file exists in the root folder (${CMAKE_SOURCE_DIR}). If it doesn't, check your download was performed correctly.")
endif()
string(STRIP ${VERSION_FILE} FGRADAR_VERSION)
message(STATUS "Version: ${FGRADAR_VERSION}")

# Make a lower case project name for internal operations (like executable
# name for example).
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

# Include CPack configuration, located in CMakeModules.
include(cpack_config)

# Check for SimGear (REQUIRED).
find_package(SimGear 2.9.0 REQUIRED)
if (SIMGEAR_FOUND)
  include_directories(${SIMGEAR_INCLUDE_DIR})
  set(LIBS ${LIBS} ${SIMGEAR_CORE_LIBRARIES}
    ${SIMGEAR_CORE_LIBRARY_DEPENDENCIES})
endif()

# Check for GTK2 (REQUIRED).
find_package(GTK2 2.6 REQUIRED gtk)
if (GTK2_FOUND)
  include_directories(${GTK2_INCLUDE_DIRS})
  set(LIBS ${LIBS} ${GTK2_LIBRARIES})
endif()

# Check for SQLite3
# FIXME: The CMake module that searches for sqlite3 always thinks this is an
# optional package.
find_package(Sqlite3 REQUIRED)
if (SQLITE3_FOUND)
  include_directories(SQLITE3_INCLUDE_DIR)
  set(LIBS ${LIBS} ${SQLITE3_LIBRARIES})
endif()

include_directories(
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
  ${CMAKE_BINARY_DIR}/include
)

# Configure file. We need to use some things done in compile time from run-time,
# so we use a CMake generated header file.
configure_file(
  "${CMAKE_SOURCE_DIR}/src/include/config.h.in"
  "${CMAKE_BINARY_DIR}/src/include/config.h"
  )

add_subdirectory(src)
