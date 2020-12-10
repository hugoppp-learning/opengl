cmake_minimum_required(VERSION 3.17)
project(openglTEST)

set(CMAKE_CXX_STANDARD 14)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/GLFW)

add_executable(openglTEST src/main.cpp src/glad.c)
target_link_libraries(openglTEST glfw)

target_include_directories(openglTEST PRIVATE ${PROJECT_SOURCE_DIR}/includes)
include_directories(${PROJECT_SOURCE_DIR}/includes)
