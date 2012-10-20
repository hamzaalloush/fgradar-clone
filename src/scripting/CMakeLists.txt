set(SOURCES
  cairolib.c
  gtklib.c
  iolib.c
  nasal-props.cxx
  NasalSys.cxx
  sgsocketlib.cxx
  unixlib.c
)

set(HEADERS
  iolib.h
  NasalSys.hxx
)

add_library(scripting ${SOURCES} ${HEADERS})
