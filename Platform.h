#pragma once

#include <SDL2/SDL.h>
#include "Keyboard.h"
#include "Chip8.h"
#include "Debugger.h"

class Platform {
public:
    Platform(const char* title, int windowWidth, int windowHeight,
             int textureWidth, int textureHeight);
    ~Platform();

    bool processInput(Keyboard& keyboard);
    void update(Chip8& chip8, Debugger& debugger);

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
};
