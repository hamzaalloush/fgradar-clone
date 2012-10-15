cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

project(nasal)
set(NASAL_VERSION 1.1pre)

option(ENABLE_GTK "Enable GTK. OFF by default." OFF)

# Check for threads
find_package(Threads REQUIRED)
set(LIBS ${LIBS} ${CMAKE_THREAD_LIBS_INIT})

# Check for PCRE (not required)
find_package(PCRE)
if (PCRE_FOUND)
  include_directories(${PCRE_INCLUDE_DIR})
  set(LIBS ${LIBS} ${PCRE_LIBRARIES})
  set(HAVE_PCRE TRUE)
else()
  set(HAVE_PCRE FALSE)
endif()

# Check for Sqlite3 (not required)
find_package(Sqlite3)
if (SQLITE3_FOUND)
  include_directories(${SQLITE3_INCLUDE_DIR})
  set(LIBS ${LIBS} ${SQLITE3_LIBRARIES})
  set(HAVE_SQLITE TRUE)
else()
  set(HAVE_SQLITE FALSE)
endif()

#Check for Readline
find_package(Readline)
if (READLINE_FOUND)
  include_directories(${READLINE_INCLUDE_DIR})
  set(LIBS ${LIBS} ${READLINE_LIBRARY})
  set(HAVE_READLINE TRUE)
else()
  set(HAVE_READLINE FALSE)
endif()

# Check for GTK2 (user tells us if we should look for it or not).
if (ENABLE_GTK)
  message(STATUS "GTK enabled, looking for GTK2...")

  find_package(GTK2 2.6 REQUIRED gtk)

  if (GTK2_FOUND)
    include_directories(${GTK2_INCLUDE_DIRS})
    set(LIBS ${LIBS} ${GTK2_LIBRARIES})
    set(HAVE_GTK TRUE)
  else()
    set(HAVE_GTK FALSE)
  endif()
else()
  message(STATUS "GTK disabled.")

  set(HAVE_GTK FALSE)
endif()

configure_file(
  ${PROJECT_SOURCE_DIR}/src/config.h.in
  ${PROJECT_BINARY_DIR}/src/config.h)
message(STATUS "Configuration file generated.")

include_directories(${CMAKE_BINARY_DIR}/src)

add_subdirectory(src)
add_subdirectory(lib)


