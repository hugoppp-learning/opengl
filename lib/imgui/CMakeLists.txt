set(IMGUI_SOURCE_FILES
        imconfig.h
        imgui.cpp
        imgui.h
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_impl_glfw.cpp
        imgui_impl_glfw.h
        imgui_impl_opengl3.cpp
        imgui_impl_opengl3.h
        imgui_internal.h
        imgui_tables.cpp
        imgui_widgets.cpp
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h
        )

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)
add_library(imgui ${IMGUI_SOURCE_FILES})
target_include_directories(imgui PRIVATE ${PROJECT_SOURCE_DIR}/lib/glfw/include ${PROJECT_SOURCE_DIR}/lib)
