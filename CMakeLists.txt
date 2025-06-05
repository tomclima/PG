cmake_minimum_required(VERSION 3.13.0)
project(PG_Project VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(vendor)
add_subdirectory(include)
add_subdirectory(src)
