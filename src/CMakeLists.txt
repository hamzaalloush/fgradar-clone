foreach(CURR_DIR
    main)
  add_subdirectory(${CURR_DIR})
endforeach()

add_executable(${PACKAGE_LOWER} ${SOURCES} ${HEADERS})

target_link_libraries(${PACKAGE_LOWER} ${LIBS})

install(TARGETS ${PACKAGE_LOWER} RUNTIME DESTINATION bin)
