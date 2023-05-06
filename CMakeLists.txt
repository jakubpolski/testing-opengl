cmake_minimum_required(VERSION 3.13.0)
project(testing-opengl VERSION 0.1.0)

add_library(glad
  include/glad/glad.h
  lib/glad.c
)
add_Library(simpler_renderer
  include/simpler_renderer.h
  lib/simpler_renderer.cpp
)

include_directories(include)
link_directories(lib)
link_libraries(
    glad
    glfw3
    simpler_renderer
)
add_link_options(/NODEFAULTLIB:MSVCRT)


MACRO(ADD_ALL_SUBDIRS curdir)
  FILE(GLOB subdirs ${curdir}/*)
  FOREACH(subdir ${subdirs})
    IF(IS_DIRECTORY ${subdir} AND EXISTS ${subdir}/CMakeLists.txt)
      ADD_SUBDIRECTORY("${subdir}")
    ENDIF()
  ENDFOREACH()
ENDMACRO()

ADD_ALL_SUBDIRS("${CMAKE_HOME_DIRECTORY}/projects")