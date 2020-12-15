cmake_minimum_required(VERSION 3.17)
project(openglTEST)

set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(IMGUI_SOURCE_FILES
        src/imgui/imconfig.h
        src/imgui/imgui.cpp
        src/imgui/imgui.h
        src/imgui/imgui_demo.cpp
        src/imgui/imgui_draw.cpp
        src/imgui/imgui_impl_glfw.cpp
        src/imgui/imgui_impl_glfw.h
        src/imgui/imgui_impl_opengl3.cpp
        src/imgui/imgui_impl_opengl3.h
        src/imgui/imgui_internal.h
        src/imgui/imgui_tables.cpp
        src/imgui/imgui_widgets.cpp
        src/imgui/imstb_rectpack.h
        src/imgui/imstb_textedit.h
        src/imgui/imstb_truetype.h
        )

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
        src/Renderer/GLDebugCallBack.h src/Renderer/Window.cpp src/Renderer/Window.h src/Renderer/VertexBufferLayout.cpp)


add_executable(openglTEST ${SOURCE_FILES} ${IMGUI_SOURCE_FILES})

target_include_directories(openglTEST PRIVATE ${PROJECT_SOURCE_DIR}/lib)
target_include_directories(openglTEST PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(openglTEST PRIVATE ${PROJECT_SOURCE_DIR}/lib/glfw/include)

add_subdirectory(lib/GLFW)
add_subdirectory(lib/glm)


target_link_libraries(openglTEST
        glfw
        glm
        )

