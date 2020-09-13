cmake_minimum_required(VERSION 3.17)
project(GraphicEngine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory("${PROJECT_SOURCE_DIR}/GraphicEngine" "${PROJECT_SOURCE_DIR}/GraphicEngine/output")
add_subdirectory("${PROJECT_SOURCE_DIR}/Checking" "${PROJECT_SOURCE_DIR}/Checking/output")