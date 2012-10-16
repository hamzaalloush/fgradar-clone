foreach(CURR_DIR
    io
    map
    math
    utils)
  add_subdirectory(${CURR_DIR})
endforeach()

include_directories( ${SIMGEAR_INCLUDE_DIR} )
include_directories( "simgear/structure" )

add_executable(${PACKAGE_LOWER} ${SOURCES} ${HEADERS} main.cpp FGRadarApplication.hxx FGRadarApplication.cxx simgear/structure/FGGLApplication.cxx i18n.hpp)
target_link_libraries(${PACKAGE_LOWER} ${LIBS})

target_link_libraries(fgradar
                ${GLUT_LIBRARIES}
                ${SIMGEAR_CORE_LIBRARIES}
                ${OPENGL_LIBRARIES}
                ${SIMGEAR_CORE_LIBRARY_DEPENDENCIES}
)


install(TARGETS ${PACKAGE_LOWER} RUNTIME DESTINATION bin)
