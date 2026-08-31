#include "Platform.h"
#include "Chip8.h"
#include "Debugger.h"
#include "CPU.h"
#include "Stack.h"
#include "Memory.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"




Platform::Platform(const char* title, int windowWidth, int windowHeight,
                   int textureWidth, int textureHeight) {

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);

    // ImGui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

Platform::~Platform() {
    // ImGui shutdown
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

        ImGui_ImplSDL2_ProcessEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_x: keyboard.setKey(0x0, true); break;
                    case SDLK_1: keyboard.setKey(0x1, true); break;
                    case SDLK_2: keyboard.setKey(0x2, true); break;
                    case SDLK_3: keyboard.setKey(0x3, true); break;
                    case SDLK_q: keyboard.setKey(0x4, true); break;
                    case SDLK_w: keyboard.setKey(0x5, true); break;
                    case SDLK_e: keyboard.setKey(0x6, true); break;
                    case SDLK_a: keyboard.setKey(0x7, true); break;
                    case SDLK_s: keyboard.setKey(0x8, true); break;
                    case SDLK_d: keyboard.setKey(0x9, true); break;
                    case SDLK_z: keyboard.setKey(0xA, true); break;
                    case SDLK_c: keyboard.setKey(0xB, true); break;
                    case SDLK_4: keyboard.setKey(0xC, true); break;
                    case SDLK_r: keyboard.setKey(0xD, true); break;
                    case SDLK_f: keyboard.setKey(0xE, true); break;
                    case SDLK_v: keyboard.setKey(0xF, true); break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_x: keyboard.setKey(0x0, false); break;
                    case SDLK_1: keyboard.setKey(0x1, false); break;
                    case SDLK_2: keyboard.setKey(0x2, false); break;
                    case SDLK_3: keyboard.setKey(0x3, false); break;
                    case SDLK_q: keyboard.setKey(0x4, false); break;
                    case SDLK_w: keyboard.setKey(0x5, false); break;
                    case SDLK_e: keyboard.setKey(0x6, false); break;
                    case SDLK_a: keyboard.setKey(0x7, false); break;
                    case SDLK_s: keyboard.setKey(0x8, false); break;
                    case SDLK_d: keyboard.setKey(0x9, false); break;
                    case SDLK_z: keyboard.setKey(0xA, false); break;
                    case SDLK_c: keyboard.setKey(0xB, false); break;
                    case SDLK_4: keyboard.setKey(0xC, false); break;
                    case SDLK_r: keyboard.setKey(0xD, false); break;
                    case SDLK_f: keyboard.setKey(0xE, false); break;
                    case SDLK_v: keyboard.setKey(0xF, false); break;
                }
                break;
        }
    }

    return quit;
}

void Platform::update(Chip8& chip8, Debugger& debugger) {

    // ImGui frame begin
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport();

    ImGui::Begin("Display");

    ImGui::SetWindowSize(ImVec2(660, 360), ImGuiCond_FirstUseEver);
    ImGui::SetWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

    // Draw CHIP-8 screen inside ImGui
    ImGui::Image((void*)texture, ImVec2(640, 320));

    ImGui::End();
    // CPU window
    ImGui::SetNextWindowSize(ImVec2(350, 300), ImGuiCond_FirstUseEver);
    ImGui::Begin("CHIP-8 Debugger");

    CPU& cpu = chip8.getCPU();

    ImGui::Text("PC: 0x%03X", cpu.getPC());
    ImGui::Text("Opcode: 0x%04X", cpu.getCurrentOpcode());
    ImGui::Separator();

    ImGui::Text("Registers:");
    for (int i = 0; i < 16; i++) {
        uint8_t value = cpu.getRegister(i);
        char label[8];
        snprintf(label, sizeof(label), "V%X", i);

        int temp = value; // ImGui uses int for InputInt
        if (ImGui::InputInt(label, &temp, 1, 16)) {
            temp &= 0xFF; // clamp to 8-bit
            cpu.setRegister(i, (uint8_t)temp);
        }
    }


    ImGui::Separator();
    ImGui::Text("I: 0x%03X", cpu.getI());
    ImGui::Text("Delay: %d", cpu.getDelayTimer());
    ImGui::Text("Sound: %d", cpu.getSoundTimer());

    ImGui::Separator();
    if (ImGui::Button("Run")) debugger.run();
    ImGui::SameLine();
    if (ImGui::Button("Pause")) debugger.pause();
    ImGui::SameLine();
    if (ImGui::Button("Step")) debugger.step();

    ImGui::End();

    // Stack window
    ImGui::SetNextWindowSize(ImVec2(350, 200), ImGuiCond_FirstUseEver);
    ImGui::Begin("Stack");
    Stack& stack = chip8.getStack();
    ImGui::Text("SP: %d", stack.getSP());
    ImGui::Separator();
    for (int i = 0; i < stack.getSP(); i++)
        ImGui::Text("[%d] 0x%03X", i, stack.getValue(i));
    ImGui::End();

    // Memory window
    ImGui::SetNextWindowSize(ImVec2(350, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Memory");

    Memory& mem = chip8.getMemory();

    // Scrollable region
    ImGui::BeginChild("memscroll", ImVec2(0, 400), true);

    for (uint16_t addr = 0; addr < 4096; addr += 16) {

        // Address label
        ImGui::Text("0x%03X:", addr);
        ImGui::SameLine();

        // 16 editable bytes
        for (int i = 0; i < 16; i++) {
            uint8_t value = mem.read(addr + i);

            // Unique label for ImGui
            char label[16];
            snprintf(label, sizeof(label), "%03X_%X", addr, i);

            int temp = value;

            ImGui::PushItemWidth(30);
            if (ImGui::InputInt(label, &temp, 1, 16, ImGuiInputTextFlags_CharsHexadecimal)) {
                temp &= 0xFF; // clamp to 8-bit
                mem.write(addr + i, (uint8_t)temp);
            }
            ImGui::PopItemWidth();

            ImGui::SameLine();
        }

        ImGui::NewLine();
    }

    ImGui::EndChild();
    ImGui::End();

    // Disassembly window
    ImGui::SetNextWindowSize(ImVec2(350, 300), ImGuiCond_FirstUseEver);
    ImGui::Begin("Disassembly");

    uint16_t pc = chip8.getCPU().getPC();
    Memory& mem2 = chip8.getMemory();

    // Show a few instructions before and after PC
    uint16_t start = (pc >= 10) ? pc - 10 : 0;
    uint16_t end   = (pc + 20 < 4096) ? pc + 20 : 4094;

    ImGui::BeginChild("disasm_scroll", ImVec2(0, 300), true);

    for (uint16_t addr = start; addr < end; addr += 2) {
        uint16_t opcode = mem2.read16(addr);
        std::string text = chip8.disassemble(opcode, addr);

        bool bp = debugger.hasBreakpoint(addr);

        // Breakpoint indicator
        if (bp)
            ImGui::TextColored(ImVec4(1,0,0,1), "●");   // red dot
        else
            ImGui::Text("○");

        ImGui::SameLine();

        // Instruction text
        if (addr == pc)
            ImGui::TextColored(ImVec4(1,1,0,1), "%03X: %s", addr, text.c_str());
        else
            ImGui::Text("%03X: %s", addr, text.c_str());

        // Toggle breakpoint when clicked
        if (ImGui::IsItemClicked()) {
            if (bp) debugger.removeBreakpoint(addr);
            else    debugger.addBreakpoint(addr);
        }
    }


    ImGui::EndChild();
    ImGui::End();


    uint32_t buffer[64 * 32];
    for (int y = 0; y < 32; y++)
        for (int x = 0; x < 64; x++)
            buffer[y * 64 + x] = chip8.getDisplay().getPixel(x, y)
                ? 0xFFFFFFFF : 0x000000FF;

    SDL_UpdateTexture(texture, nullptr, buffer, 64 * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
}

