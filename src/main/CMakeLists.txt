set(SOURCES
  fgradar_app.cxx
  main.cxx
  props.cxx
)

set(HEADERS
  fgradar_app.hxx
  props.hxx
)

add_executable(${PACKAGE_LOWER} ${SOURCES} ${HEADERS})

foreach(MODULE
    simgear)
  target_link_libraries(${PACKAGE_LOWER} ${MODULE})
endforeach()

# Link the thrid-party libraries, not our source ones
target_link_libraries(${PACKAGE_LOWER} ${LIBS})

install(TARGETS ${PACKAGE_LOWER} RUNTIME DESTINATION bin)

