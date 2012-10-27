cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(FGRadar)

# Include our own cmake modules that aren't included in the default package.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

# Read VERSION file (located in the root directory, same one as this
# CMakeList.txt), strip the result and store it in a variable.
file(READ VERSION VERSION_FILE)
if (NOT VERSION_FILE)
  message(FATAL_ERROR "Failed to determine version number. Check the VERSION file exists in the root folder (${CMAKE_SOURCE_DIR}). If it doesn't, check your download was performed correctly.")
endif()
string(STRIP ${VERSION_FILE} FGRADAR_VERSION)
message(STATUS "Version: ${FGRADAR_VERSION}")

# Make a lower case project name for internal operations (like executable
# name for example).
string(TOLOWER ${PROJECT_NAME} PROJECT_LOWER)

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
# FIXME: The CMake module that searches for sqlite3, always thinks this is an
# optional package.
find_package(Sqlite3 REQUIRED)
if (SQLITE3_FOUND)
  include_directories(SQLITE3_INCLUDE_DIR)
  set(LIBS ${LIBS} ${SQLITE3_LIBRARIES})
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR}/src)
include_directories(${PROJECT_BINARY_DIR}/include)

# Configure file
configure_file(
  "${PROJECT_SOURCE_DIR}/src/include/config.h.in"
  "${PROJECT_BINARY_DIR}/src/include/config.h"
  )

add_subdirectory(src)
