//
// Created by Davon on 6/10/2026.
//
#include <fstream>
#include <ctime>
#include "Chip8.h"
const uint8_t fontset[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8() : cpu(memory, display, keyboard, stack) {
    for (int i = 0; i < 80; i++) {
        memory.write(0x050 + i, fontset[i]);
    }
    srand(time(0));

}
void Chip8::loadROM(const std::string &path) {
    std::ifstream rom(path, std::ios::binary | std::ios::ate);
    if (rom.is_open()) {
        std::streamsize size  = rom.tellg();
        rom.seekg(0, std::ios::beg);
        std::vector<uint8_t> buffer(size);
        rom.read(reinterpret_cast<char*>(buffer.data()), size);
        rom.close();

        for (int i = 0; i < size; i++) {
            memory.write(0x200 + i, buffer[i]);
        }
    }
}
void Chip8::cycle() {
    cpu.execute();
    cpu.tickTimers();
}
std::string Chip8::disassemble(uint16_t opcode, uint16_t pc) const {
    uint16_t nnn = opcode & 0x0FFF;
    uint8_t nn = opcode & 0x00FF;
    uint8_t n = opcode & 0x000F;
    uint8_t x  =(opcode & 0x0F00) >> 8;
    uint8_t y  =(opcode & 0x00F0) >> 4;

    switch (opcode & 0xF000) {
        case 0x0000:
            if (opcode == 0x00E0) return "CLS";
            if (opcode == 0x00EE) return "RET";
            return "SYS " + std ::to_string(nnn);
        case 0x1000:
            return "JP " + std ::to_string(nnn);
        case 0x2000:
            return "CALL " + std ::to_string(nnn);
        case 0x3000:
            return "SE V" + std ::to_string(x) + ", " + std :: to_string(nn);
        case 0x4000:
            return "SNE V" + std ::to_string(x) + ", " + std :: to_string(nn);
        case 0x5000:
            return "SE V" + std ::to_string(x) + ", " + std :: to_string(y);
        case 0x6000:
            return "LD V" + std ::to_string(x) + ", " + std :: to_string(nn);
        case 0x7000:
            "ADD V" + std ::to_string(x) + ", " + std :: to_string(nn);
        case 0x8000:
            switch (n) {
            case 0x0:
                    return "LD V" + std ::to_string(x) + ", V" + std :: to_string(y);
            case 0x1:
                    return "OR V" + std :: to_string(x) + ", V" + std :: to_string(y);
            case 0x2:
                    return "AND V" + std :: to_string(x) + ", V" + std :: to_string(y);
            case 0x3:
                    return "XOR V" + std :: to_string(x) + ", V" + std :: to_string(y);
            case 0x4:
                    return "ADD V" + std :: to_string(x) + ", V" + std :: to_string(y);
            case 0x5:
                    return "SUB V" + std :: to_string(x) + ", V" + std :: to_string(y);
            case 0x6:
                    return "SHR V" + std :: to_string(x) + ", V" + std :: to_string(y);
            case 0x7:
                    return "SUBN V" + std :: to_string(x) + ", V" + std :: to_string(y);
            case 0xE:
                    return "SHL v" + std :: to_string(x);
            }
            break;
        case 0x9000:
            return "SNE V" + std::to_string(x) + ", V" + std::to_string(y);
        case 0xA000:
            return "LD I, " + std::to_string(nnn);
        case 0xB000:
            return "JP V0, " + std::to_string(nnn);
        case 0xC000:
            return "RND V" + std::to_string(x) + ", " + std::to_string(nn);
        case 0xD000:
            return "DRW V" + std::to_string(x) + ", V" + std::to_string(y) + ", " + std::to_string(n);

        case 0xE000:
            if (nn == 0x9E) return "SKP V" + std::to_string(x);
            if (nn == 0xA1) return "SKNP V" + std::to_string(x);
            break;

        case 0xF000:
            switch (nn) {
            case 0x07:
                    return "LD V" + std::to_string(x) + ", DT";
            case 0x0A:
                    return "LD V" + std::to_string(x) + ", K";
            case 0x15:
                    return "LD DT, V" + std::to_string(x);
            case 0x18:
                    return "LD ST, V" + std::to_string(x);
            case 0x1E:
                    return "ADD I, V" + std::to_string(x);
            case 0x29:
                    return "LD F, V" + std::to_string(x);
            case 0x33:
                    return "LD B, V" + std::to_string(x);
            case 0x55:
                    return "LD [I], V0-" + std::to_string(x);
            case 0x65:
                    return "LD V0-" + std::to_string(x) + ", [I]";
            }
            break;
    }

    return "UNKNOWN";
}

