set(SOURCES
  structure/SGApplication.cxx
  structure/SGCmdApplication.cxx
)

set(HEADERS
  structure/SGApplication.hxx
  structure/SGCmdApplication.hxx
)

add_library(simgear ${SOURCES} ${HEADERS})
