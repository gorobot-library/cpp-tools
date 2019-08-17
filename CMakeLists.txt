cmake_minimum_required(VERSION 3.9)

project(cpptools)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)
set(cpptools_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

find_package(Catch2 REQUIRED)

include(ExternalProject)
include(GNUInstallDirs)

# # Macro to install header files to the include directory.
# macro(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
#     foreach(HEADER ${${HEADER_LIST}})
#         string(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
#
#         install(FILES
#           ${HEADER}
#           DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/symctrl/${DIR}
#         )
#
#     endforeach()
# endmacro()
#
# # Macro to prepend a string to each element of a list.
# macro(PREPEND NEW_VAR PREFIX)
#   set(NEW_LIST "")
#
#   foreach(FILE_NAME ${ARGN})
#     list(APPEND NEW_LIST "${PREFIX}/${FILE_NAME}")
#   endforeach()
#
#   set(${NEW_VAR} "${NEW_LIST}")
# endmacro()

option(BUILD_TESTS "Build unit tests." ON)

if(BUILD_TESTS)
  enable_testing()
endif()

# Add all external projects.
option(INSTALL_MANIFESTO "Install manifesto parser." ON)

if(INSTALL_MANIFESTO)
  add_subdirectory(manifesto)
endif()

option(INSTALL_CLAP "Install command line argument parser tool." ON)

if(INSTALL_CLAP)
  add_subdirectory(clap)
endif()

option(INSTALL_TPL "Install templating tool." ON)

if(INSTALL_TPL)
  add_subdirectory(tpl)
endif()

option(BUILD_SCAFFOLD "Build scaffolding tool." ON)

if(BUILD_SCAFFOLD)
  add_subdirectory(scaffold)
endif()
