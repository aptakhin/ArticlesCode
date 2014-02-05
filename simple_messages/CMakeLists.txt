cmake_minimum_required(VERSION 2.6.0)
project(SIMPLE_MESSAGE)

add_executable(delegates message.h delegate.h delegates.cpp)
add_executable(functions message.h functions.h functions.cpp)
add_executable(benchmark message.h functions.h benchmark.cpp)
