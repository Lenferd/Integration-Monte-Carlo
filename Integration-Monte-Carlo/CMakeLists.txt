cmake_minimum_required(VERSION 3.5)
project(monte_carlo_method)
set(target "monte_carlo_method")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)

file(GLOB SRC "src/main.cpp")

add_executable(${target} ${SRC})


project(MPI)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(MPI REQUIRED)
include_directories( ${MPI_INCLUDE_PATH} )

set(SOURCE_FILES src/MPI_main.cpp)
add_executable(MPI ${SOURCE_FILES})
target_link_libraries( MPI ${MPI_LIBRARIES} )