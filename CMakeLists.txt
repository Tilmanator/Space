cmake_minimum_required(VERSION 3.12)
project(space)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig)

# Get GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES
pkg_check_modules(GTKMM gtkmm-3.0)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.67.0 COMPONENTS filesystem)

set(ALL_LIBS
        ${GTKMM_LIBRARIES}
        )

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(ALL_LIBS
            ${ALL_LIBS}
            ${Boost_LIBRARIES}
            )
endif()

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )

include_directories(
        ${GTKMM_INCLUDE_DIRS}  )

add_executable(space main.cpp)

target_link_libraries(space
        ${ALL_LIBS}
        )

install (TARGETS space DESTINATION bin)