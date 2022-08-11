cmake_minimum_required(VERSION 3.6)
project(Suzu-cpp)

add_executable(Suzu-cpp main.cpp)

add_subdirectory(deps/sleepy-discord)
target_link_libraries(Suzu-cpp sleepy-discord)