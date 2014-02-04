cmake_minimum_required(VERSION 2.6.0)
project(SIMPLE_MESSAGE)

add_executable(delegates delegate.h delegates.cpp)
add_executable(functions functions.h functions.cpp)
add_executable(benchmark functions.h benchmark.cpp)
