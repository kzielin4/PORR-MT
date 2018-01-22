cmake_minimum_required(VERSION 3.3)
project(hellompi)

set(CMAKE_CXX_STANDARD 11)
#SET(CMAKE_CXX_FLAGS -pthread)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

set(SOURCE_FILES main.cpp src/derivative.h src/derivative.cpp src/Interval.cpp src/Interval.h src/Solver.cpp src/Solver.h)
add_executable(hellompi ${SOURCE_FILES})

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    add_executable(untitled ${SOURCE_FILES} src/derivative.h src/derivative.cpp src/Interval.cpp src/Interval.h src/Solver.cpp src/Solver.h)
    target_link_libraries (untitled ${Boost_LIBRARIES})
endif()

include_directories(/usr/include/mpi/)