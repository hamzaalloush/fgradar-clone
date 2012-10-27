set(SOURCES
  fgradar_app.cxx
  main.cxx
)

set(HEADERS
  fgradar_app.hxx
)

add_executable(${PROJECT_LOWER} ${SOURCES} ${HEADERS})

foreach(MODULE
    ##
    # this adds our own helpers from the simgear folder (namely the
    # SGApplication stuff)
    # NOTE: these are intended to be eventually merged with SG upstream
    # so that this can be removed then!
    simgear

    scripting
    multiplayer)
  target_link_libraries(${PROJECT_LOWER} ${MODULE})
endforeach()

# Link the thrid-party libraries, not our source ones
target_link_libraries(${PROJECT_LOWER} ${LIBS})

install(TARGETS ${PROJECT_LOWER} RUNTIME DESTINATION bin)
