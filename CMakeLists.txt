cmake_minimum_required(VERSION 3.17)
project(learningOpenGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/GLFW)
add_subdirectory(lib/glm)
add_subdirectory(lib/imgui)
#add_subdirectory(test)

########### LIB ###########
add_library(myopengl_lib
        lib/stb_image/stb_image.h
        lib/glad/glad.c
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
        src/Array3D.hpp
        src/ChunkManager.hpp
        src/Face.hpp
        src/ChunkMeshGenerator.hpp
        )
target_include_directories(myopengl_lib PUBLIC
        ${PROJECT_SOURCE_DIR}/lib
        ${PROJECT_SOURCE_DIR}/src)
target_include_directories(myopengl_lib PRIVATE
        ${PROJECT_SOURCE_DIR}/lib/glfw/include)
target_link_libraries(myopengl_lib
        glfw
        glm
        imgui)


########### EXE ###########
add_executable(myopengl src/main.cpp src/Chunk.hpp)
target_link_libraries(myopengl myopengl_lib)


