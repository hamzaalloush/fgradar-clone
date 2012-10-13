foreach(CURR_DIR
    io
    map
    math
    utils)
  add_subdirectory(${CURR_DIR})
endforeach()

add_executable(${PACKAGE_LOWER} ${SOURCES} ${HEADERS} main.cpp i18n.hpp)
target_link_libraries(${PACKAGE_LOWER} ${LIBS})

install(TARGETS ${PACKAGE_LOWER} RUNTIME DESTINATION bin)
