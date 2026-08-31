//
// Created by Davon on 6/10/2026.
//

#ifndef CHIP8_H
#define CHIP8_H
#include <fstream>
#include <ctime>
#include <string>
#include "CPU.h"
#include "Memory.h"
#include "Display.h"
#include "Keyboard.h"
#include "Stack.h"

#include "CPU.h"


class Chip8 {
private:
    Memory memory;
    Display display;
    Keyboard keyboard;
    Stack stack;
    CPU cpu;

public:
    Chip8();
    void loadROM(const std::string& path);
    void cycle();
    Display& getDisplay() { return display; }
    Keyboard& getKeyboard() { return keyboard; }
    CPU& getCPU() { return cpu; }
    Memory& getMemory() { return memory; }
    Stack& getStack() { return stack; }
    std::string disassemble(uint16_t opcode, uint16_t pc) const;

};



#endif //CHIP8_H
