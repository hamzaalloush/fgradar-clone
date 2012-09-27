set(SOURCES
  gui/mainwin.cpp
  gui/preferences_dialog.cpp

  io/file_manager.cpp
  io/logger.cpp

  app.cpp)

set(HEADERS
  include/config.h

  io/file_manager.hpp
  io/logger.hpp

  gui/mainwin.hpp
  gui/preferences_dialog.hpp

  app.hpp)

add_executable(${PACKAGE_LOWER} ${SOURCES} ${HEADERS})
target_link_libraries(${PACKAGE_LOWER} ${LIBS})

install(TARGETS ${PACKAGE_LOWER} RUNTIME DESTINATION bin)

