foreach(CURR_DIR
    simgear
    scripting
    multiplayer
    main)
  add_subdirectory(${CURR_DIR})
endforeach()
