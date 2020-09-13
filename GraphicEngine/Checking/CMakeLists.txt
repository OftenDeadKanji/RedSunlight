cmake_minimum_required(VERSION 3.17)
project(GraphicEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(Checking main.cpp)

include_directories(../GraphicEngine)

target_link_libraries(Checking Engine)