add_executable(myopengl_test ${PROJECT_SOURCE_DIR}/lib/catch2/catch.hpp Test1.cpp)
target_include_directories(myopengl_test PRIVATE ${PROJECT_SOURCE_DIR}/lib/catch2/catch.hpp )
target_link_libraries(myopengl_test myopengl_lib)
