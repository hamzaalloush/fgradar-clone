if (HAVE_PCRE)
  set(PCRE_SOURCES regexlib.c)
endif()

if (HAVE_SQLITE)
  set(SQLITE_SOURCES sqlitelib.c)
endif()

if (HAVE_READLINE)
  set(READLINE_SOURCES readlinelib.c)
endif()

if (HAVE_GTK)
  set(GTK_SOURCES gtklib.c cairolib.c)
endif()

set(LIBNASAL_SOURCES
  bitslib.c
  code.c
  codegen.c
  gc.c
  hash.c
  iolib.c
  lex.c
  lib.c
  mathlib.c
  misc.c
  parse.c
  string.c
  thread-posix.c
  thread-win32.c
  threadlib.c
  unixlib.c
  utf8lib.c
  vector.c

  ${PCRE_SOURCES}
  ${SQLITE_SOURCES}
  ${READLINE_SOURCES}
  ${GTK_SOURCES}
  )

set(LIBNASAL_HEADERS
  code.h
  data.h
  iolib.h
  nasal.h
  parse.h
  )

set(NASALBIN_SOURCES nasal-bin.c)

set(INCLUDE_HEADERS
  nasal.h
  naref.h
  )

add_library(nasal STATIC ${LIBNASAL_SOURCES} ${LIBNASAL_HEADERS})
target_link_libraries(nasal ${LIBS} m)

add_executable(nasal-bin ${NASALBIN_SOURCES})
target_link_libraries(nasal-bin nasal)

install(TARGETS nasal-bin nasal RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

install(FILES ${INCLUDE_HEADERS} DESTINATION include)
install(PROGRAMS nasal DESTINATION bin)
