cmake_minimum_required(VERSION 3.5)
project(marixMultiplication)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(target "normal_algorithm")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)

file(GLOB SRC "src/main.cpp")

add_executable(${target} ${SRC})


set(target "mpi")

find_package(MPI REQUIRED)
include_directories( ${MPI_INCLUDE_PATH} )

set(SOURCE_FILES src/MPI_main.cpp)
add_executable(mpi ${SOURCE_FILES})
target_link_libraries( mpi ${MPI_LIBRARIES} )