set(SOURCES
  app/SGApplication.cxx
  app/SGCmdApplication.cxx
)

set(HEADERS
  app/SGApplication.hxx
  app/SGCmdApplication.hxx
)

add_library(simgear ${SOURCES} ${HEADERS})
