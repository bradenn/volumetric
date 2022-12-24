cmake_minimum_required(VERSION 3.24)
project(flux)

find_package(glfw3 3.3 REQUIRED)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(flux
        src/main.cpp
        src/simulation.cpp
        src/graphics/window.cpp
        src/graphics/renderer.cpp
        src/quanta.cpp)

# Add the header files.
target_include_directories(flux PRIVATE
        src
        src/physics
        src/graphics
        src/utilities)

target_link_libraries(flux glfw)
target_link_libraries(flux OpenGL::GL)