cmake_minimum_required(VERSION 3.17)
project(GraphicEngine)

set(CMAKE_CXX_STANDARD 20)

add_library(Engine "")
add_subdirectory(src)
add_subdirectory(ThirdParty/glfw)
add_subdirectory(ThirdParty/GLAD)

include_directories(ThirdParty/glfw/include)
include_directories(ThirdParty/GLAD/include)

target_precompile_headers(Engine
        PUBLIC
        <memory>
        <string>)

target_link_libraries(Engine PRIVATE glad)
target_compile_definitions(Engine PRIVATE RED_LIB GLFW_INCLUDE_NONE)
target_link_libraries(Engine PUBLIC glfw ${GLFW_LIBRARIES})