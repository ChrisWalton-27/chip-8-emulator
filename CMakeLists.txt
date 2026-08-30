cmake_minimum_required(VERSION 3.31)
project(CHIP_8_Program)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_PATH "C:/SDL2/SDL2-devel-2.32.0-mingw/SDL2-2.32.0/x86_64-w64-mingw32")

include_directories(${SDL2_PATH}/include)
link_directories(${SDL2_PATH}/lib)

add_executable(CHIP_8_Program main.cpp
        Memory.cpp
        Memory.h
        Chip8.cpp
        Chip8.h
        Stack.cpp
        Stack.h
        Display.cpp
        Display.h
        Keyboard.cpp
        Keyboard.h
        CPU.cpp
        CPU.h
        Platform.cpp
        Platform.h
        Debugger.cpp
        Debugger.h)

target_link_libraries(CHIP_8_Program mingw32 SDL2main SDL2)

add_custom_command(TARGET CHIP_8_Program POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_PATH}/bin/SDL2.dll"
        $<TARGET_FILE_DIR:CHIP_8_Program>)