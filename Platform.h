#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL2/SDL.h>
#include "Display.h"
#include "Keyboard.h"

class Platform {
private:
    SDL_Window*   window   = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture*  texture  = nullptr;

public:
    Platform(const char* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
    ~Platform();
    bool processInput(Keyboard& keyboard);
    void update(Display& display);
};

#endif //PLATFORM_H