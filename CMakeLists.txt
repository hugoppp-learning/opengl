cmake_minimum_required(VERSION 3.17)
project(openglTEST)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
        src/renderer/Shader.cpp
        src/renderer/Shader.h
        src/renderer/VertexArray.h
        src/renderer/VertexBufferLayout.h
        src/renderer/Buffer.h
        src/myAssert.h
        src/renderer/Renderer.cpp
        src/renderer/Renderer.h
        src/renderer/Texture.cpp src/renderer/Texture.h
        src/renderer/Window.cpp
        src/renderer/Window.h
        src/renderer/VertexBufferLayout.cpp
        src/renderer/Camera.cpp
        src/renderer/Camera.h
        src/renderer/Mesh.cpp
        src/renderer/Mesh.h)


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

