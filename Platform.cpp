#include "Platform.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"

Platform::Platform(const char* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

Platform::~Platform() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Platform::processInput(Keyboard& keyboard) {
    bool quit = false;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: quit = true;      break;
                    case SDLK_x:  keyboard.setKey(0x0, true); break;
                    case SDLK_1:  keyboard.setKey(0x1, true); break;
                    case SDLK_2:  keyboard.setKey(0x2, true); break;
                    case SDLK_3:  keyboard.setKey(0x3, true); break;
                    case SDLK_q:  keyboard.setKey(0x4, true); break;
                    case SDLK_w:  keyboard.setKey(0x5, true); break;
                    case SDLK_e:  keyboard.setKey(0x6, true); break;
                    case SDLK_a:  keyboard.setKey(0x7, true); break;
                    case SDLK_s:  keyboard.setKey(0x8, true); break;
                    case SDLK_d:  keyboard.setKey(0x9, true); break;
                    case SDLK_z:  keyboard.setKey(0xA, true); break;
                    case SDLK_c:  keyboard.setKey(0xB, true); break;
                    case SDLK_4:  keyboard.setKey(0xC, true); break;
                    case SDLK_r:  keyboard.setKey(0xD, true); break;
                    case SDLK_f:  keyboard.setKey(0xE, true); break;
                    case SDLK_v:  keyboard.setKey(0xF, true); break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_x:  keyboard.setKey(0x0, false); break;
                    case SDLK_1:  keyboard.setKey(0x1, false); break;
                    case SDLK_2:  keyboard.setKey(0x2, false); break;
                    case SDLK_3:  keyboard.setKey(0x3, false); break;
                    case SDLK_q:  keyboard.setKey(0x4, false); break;
                    case SDLK_w:  keyboard.setKey(0x5, false); break;
                    case SDLK_e:  keyboard.setKey(0x6, false); break;
                    case SDLK_a:  keyboard.setKey(0x7, false); break;
                    case SDLK_s:  keyboard.setKey(0x8, false); break;
                    case SDLK_d:  keyboard.setKey(0x9, false); break;
                    case SDLK_z:  keyboard.setKey(0xA, false); break;
                    case SDLK_c:  keyboard.setKey(0xB, false); break;
                    case SDLK_4:  keyboard.setKey(0xC, false); break;
                    case SDLK_r:  keyboard.setKey(0xD, false); break;
                    case SDLK_f:  keyboard.setKey(0xE, false); break;
                    case SDLK_v:  keyboard.setKey(0xF, false); break;
                }
                break;
        }
    }

    return quit;
}

void Platform::update(Display& display) {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("CHIP-8 Debugger");
    ImGui::Text("Debugger online");
    ImGui::End();

    uint32_t buffer[64 * 32];
    const bool* pixels = display.getPixels();
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            buffer[y * 64 + x] = display.getPixel(x, y) ? 0xFFFFFFFF : 0x000000FF;
        }
    }
    SDL_UpdateTexture(texture, nullptr, buffer, 64 * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);
}