cmake_minimum_required(VERSION 3.21)
project(SPCMouse)

set(CMAKE_CXX_STANDARD 14)

add_executable(SPCMouse main.cpp MouseData.h)
target_link_libraries(SPCMouse libhidapi-hidraw.so)
