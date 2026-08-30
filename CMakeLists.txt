cmake_minimum_required(VERSION 3.31)
project(CHIP_8_Program)

set(CMAKE_CXX_STANDARD 17)

# SDL2 path
set(SDL2_PATH "C:/SDL2/SDL2-devel-2.32.0-mingw/SDL2-2.32.0/x86_64-w64-mingw32")

# SDL2 include + lib directories (ONLY include/SDL2 is correct)
include_directories(${SDL2_PATH}/include/SDL2)
link_directories(${SDL2_PATH}/lib)

# Executable + all source files
add_executable(CHIP_8_Program
        main.cpp

        CPU.cpp CPU.h
        Memory.cpp Memory.h
        Display.cpp Display.h
        Keyboard.cpp Keyboard.h
        Stack.cpp Stack.h
        Chip8.cpp Chip8.h
        Platform.cpp Platform.h
        Debugger.cpp Debugger.h

        # Dear ImGui core
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp

        # Dear ImGui SDL2 + SDL_Renderer2 backends
        imgui/backends/imgui_impl_sdl2.cpp
        imgui/backends/imgui_impl_sdlrenderer2.cpp
)

# Include directories for ImGui + SDL2
target_include_directories(CHIP_8_Program PRIVATE
        imgui
        imgui/backends
        ${SDL2_PATH}/include/SDL2
)

# Link SDL2
target_link_libraries(CHIP_8_Program mingw32 SDL2main SDL2)

# Copy SDL2.dll after build
add_custom_command(TARGET CHIP_8_Program POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_PATH}/bin/SDL2.dll"
        $<TARGET_FILE_DIR:CHIP_8_Program>)
