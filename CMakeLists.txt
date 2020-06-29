cmake_minimum_required(VERSION 3.0)

project(Chip8)

set(CMAKE_CXX_STANDARD 14)

# Ugly SDL2
set(SDL2_DIR C:\\Users\\Romain\\Workspace\\vcpkg\\installed\\x86-windows\\share\\sdl2)
find_package(SDL2 REQUIRED)

include_directories(include)

add_executable(
    Chip8 
    src/main.cpp 
    src/memory.cpp
    src/chip8.cpp
    src/renderer.cpp
    src/cpu.cpp
    src/input.cpp
    include/memory.hpp
    include/chip8.hpp
    include/renderer.hpp
    include/cpu.hpp
    include/input.hpp
)

target_link_libraries(Chip8 PRIVATE SDL2::SDL2)