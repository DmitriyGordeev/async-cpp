cmake_minimum_required(VERSION 3.21)
project(async_examples)

set(CMAKE_CXX_STANDARD 20)

include_directories(deps/doctest/doctest/)
include_directories(deps/cpp-httplib/)

add_subdirectory(src)
add_subdirectory(test)

