#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "Chip8.h"
#include "Platform.h"
#include "Debugger.h"

int main(int argc, char* argv[]) {

    Chip8 chip8;
    Platform platform("CHIP-8", 640, 320, 64, 32);
    Debugger debugger;

    chip8.loadROM("C:/Users/Davon/Downloads/Pong (1 player).ch8");

    const int TARGET_CYCLE_TIME_US = 1060;

    bool quit = false;
    while (!quit) {
        auto startTime = std::chrono::high_resolution_clock::now();

        quit = platform.processInput(chip8.getKeyboard());

        debugger.update(chip8);

        platform.update(chip8, debugger);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

        if (elapsed < TARGET_CYCLE_TIME_US) {
            std::this_thread::sleep_for(std::chrono::microseconds(TARGET_CYCLE_TIME_US - elapsed));
        }
    }

    return 0;
}
