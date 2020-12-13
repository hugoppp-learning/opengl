cmake_minimum_required(VERSION 3.17)
project(openglTEST)

set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/GLFW)
add_subdirectory(lib/glm)

set(SOURCE_FILES
        lib/stb_image/stb_image.h
        lib/glad/glad.c
        src/main.cpp
        src/Renderer/Shader.cpp
        src/Renderer/Shader.h
        src/Renderer/VertexArray.h
        src/Renderer/VertexBufferLayout.h
        src/Renderer/VertexAttributes.h
        src/Renderer/VertexBuffer.h
        src/Renderer/IndexBuffer.h
        src/myAssert.h
        src/Renderer/Renderer.cpp
        src/Renderer/Renderer.h
        src/Renderer/Texture.cpp src/Renderer/Texture.h
        src/Renderer/GLDebugCallBack.h)

add_executable(openglTEST ${SOURCE_FILES})
target_link_libraries(openglTEST
        glfw
        glm)

target_include_directories(openglTEST PRIVATE ${PROJECT_SOURCE_DIR}/lib)
#target_include_directories(openglTEST PRIVATE ${PROJECT_SOURCE_DIR}/includes)
target_include_directories(openglTEST PRIVATE ${PROJECT_SOURCE_DIR}/src)

