cmake_minimum_required(VERSION 3.5)
project(monte_carlo_method)
set(target "monte_carlo_method")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)

file(GLOB SRC "src/*.cpp")

add_executable(${target} ${SRC})