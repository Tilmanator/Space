cmake_minimum_required(VERSION 3.12)
project(space)

set(CMAKE_CXX_STANDARD 14)

find_library(gtkmm REQUIRED)
find_package(GTK REQUIRED)

find_package(OpenGL REQUIRED) # OPENGL_LIBRARY
find_package(PkgConfig)

# Get GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES
pkg_check_modules(GTKMM gtkmm-3.0)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        ${GLUT_LIBRARY}
        ${GTKMM_LIBRARIES}
        )

message( "we are in " ${CMAKE_CURRENT_SOURCE_DIR})
message("OPENGL PATH " ${OPENGL_LIBRARY})

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )

include_directories(
        ${GTKMM_INCLUDE_DIRS}  )

add_executable(space main.cpp)

target_link_libraries(space
        ${ALL_LIBS}
        )