cmake_minimum_required(VERSION 3.28)
project(CHIP_8_Program)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_PATH "C:/SDL2/SDL2-devel-2.32.0-mingw/SDL2-2.32.0/x86_64-w64-mingw32")

include_directories(${SDL2_PATH}/include)
include_directories(${SDL2_PATH}/include/SDL2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends)
link_directories(${SDL2_PATH}/lib)

add_executable(CHIP_8_Program
        main.cpp
        Platform.cpp
        Chip8.cpp
        Debugger.cpp
        CPU.cpp
        Stack.cpp
        Memory.cpp
        Display.cpp
        Keyboard.cpp
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_demo.cpp
        imgui/backends/imgui_impl_sdl2.cpp
        imgui/backends/imgui_impl_sdlrenderer2.cpp
)

target_link_libraries(CHIP_8_Program mingw32 SDL2main SDL2)

add_custom_command(TARGET CHIP_8_Program POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_PATH}/bin/SDL2.dll"
        $<TARGET_FILE_DIR:CHIP_8_Program>)