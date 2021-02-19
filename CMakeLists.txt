cmake_minimum_required(VERSION 3.17)
project(openglTEST)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(openglTEST
        lib/stb_image/stb_image.h
        lib/glad/glad.c
        src/main.cpp
        src/renderer/Shader.cpp
        src/renderer/Shader.hpp
        src/renderer/VertexArray.h
        src/renderer/VertexBufferLayout.hpp
        src/renderer/Buffer.hpp
        src/myAssert.hpp
        src/renderer/Renderer.cpp
        src/renderer/Renderer.hpp
        src/renderer/Texture.cpp
        src/renderer/Texture.hpp
        src/renderer/Window.cpp
        src/renderer/Window.hpp
        src/renderer/VertexBufferLayout.cpp
        src/renderer/Camera.cpp
        src/renderer/Camera.hpp
        src/renderer/Mesh.hpp
        src/renderer/Meshes/Cube.hpp
        src/ChunkGenerator.hpp
        src/Chunk.hpp
        src/Array3D.hpp)

target_include_directories(openglTEST PRIVATE ${PROJECT_SOURCE_DIR}/lib)
target_include_directories(openglTEST PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(openglTEST PRIVATE ${PROJECT_SOURCE_DIR}/lib/glfw/include)

add_subdirectory(lib/GLFW)
add_subdirectory(lib/glm)
add_subdirectory(lib/imgui)

target_link_libraries(openglTEST
        glfw
        glm
        imgui
        )
