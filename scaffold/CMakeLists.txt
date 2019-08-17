cmake_minimum_required(VERSION 3.9)

project(scaffold)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)
set(scaffold_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

find_package(clap CONFIG REQUIRED)

include(GNUInstallDirs)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

include_directories("${PROJECT_BINARY_DIR}")

# A list of all header files.
set(HEADERS
  lib/scaffold.hpp
  lib/tpl/class.tpl
  lib/tpl/cmake_header_only.tpl
  lib/tpl/header.tpl
  lib/tpl/source.tpl
)

# A list of all source files.
set(SRC
  src/scaffold.cc
)

# ExternalProject_Add(yaml-cpp
#   GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
# )
# # https://github.com/jbeder/yaml-cpp

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} clap)
target_link_libraries(${PROJECT_NAME} stdc++fs)

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
