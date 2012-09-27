cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Include our own cmake that aren't included in the default package.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Define the project name.
project(FGRadar)

# We defined the project name with capitals and all that. Define one in lower
# letters, for directory usage.
set(PACKAGE_LOWER fgradar)

# Set version-
set(FGRADAR_MAJOR_VERSION 0)
set(FGRADAR_MINOR_VERSION 3)
set(FGRADAR_PATCH_VERSION 0)
set(FGRADAR_VERSION
  ${FGRADAR_MAJOR_VERSION}.${FGRADAR_MINOR_VERSION}.${FGRADAR_PATCH_VERSION})

# Define the data directory location.
set(DATADIR ${CMAKE_INSTALL_PREFIX}/share/${PACKAGE_LOWER})

# Include CPack configuration.
include(cpack_config)

# Check for libraries #
#######################

message(STATUS "Checking for libraries... ")

# Check for wxWidgets
find_package(wxWidgets COMPONENTS core base REQUIRED)
include("${wxWidgets_USE_FILE}")
set(LIBS ${LIBS} ${wxWidgets_LIBRARIES})

# Check for Boost
# (Just include the thread and system components).
find_package(Boost COMPONENTS thread system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

if(UNIX)
  add_definitions(-Wall)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

include_directories(${PROJECT_BINARY_DIR}/src)
include_directories(${PROJECT_BINARY_DIR}/include)

# Configure file
configure_file(
  ${PROJECT_SOURCE_DIR}/src/include/config.h.in
  ${PROJECT_BINARY_DIR}/src/include/config.h)

message(STATUS "Config file generated.")

# Add subdirectories
add_subdirectory(src)

# Install target #
##################

macro(installfilemacro filepath)
  set(source_regex "(.*)/data/(.*)")
  set(svn_regex "(.*).svn(.*)")
  
  string(REGEX MATCH "${svn_regex}" is_svn_dir "${curr}")
  if(is_svn_dir)
    # don't install SVN files
  else()
    string(REGEX MATCH "${source_regex}" source_path "${curr}")
    if(source_path)
      string(REGEX REPLACE "${source_regex}" "\\2" after_source "${source_path}")
      get_filename_component(install_location ${after_source} PATH)
      install(FILES ${filepath} DESTINATION "share/${PACKAGE_LOWER}/${install_location}")
    endif(source_path)
  endif()
endmacro(installfilemacro)

FILE(GLOB_RECURSE datafiles "${CMAKE_CURRENT_SOURCE_DIR}/data/*")
foreach(curr ${datafiles})
  installfilemacro(${curr})
endforeach()

# Uninstall target #
####################
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
