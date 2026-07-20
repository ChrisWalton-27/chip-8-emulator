//
// Created by Davon on 6/15/2026.
//

#include "CPU.h"
CPU::CPU(Memory& mem, Display& disp ,Keyboard& kb, Stack& st) : memory(mem), display(disp), keyboard(kb), stack(st) {

}
void CPU::clear() {

}
uint16_t CPU::fetch() {
    uint16_t op = (memory.read(pc) << 8) | memory.read(pc + 1);
    pc += 2;
    return op;

}
void CPU::decode(uint16_t op) {
    switch (op & 0xF000) {

        case 0x0000:
            switch (op & 0x00FF) {
                case 0xE0: OP_00E0(op); break;
                case 0xEE: OP_00EE(op); break;
                default:   OP_0nnn(op); break; // SYS (rarely used)
            }
            break;

        case 0x1000: OP_1nnn(op); break;
        case 0x2000: OP_2nnn(op); break;
        case 0x3000: OP_3xkk(op); break;
        case 0x4000: OP_4xkk(op); break;
        case 0x5000: OP_5xy0(op); break;
        case 0x6000: OP_6xkk(op); break;
        case 0x7000: OP_7xkk(op); break;

        case 0x8000:
            switch (op & 0x000F) {
                case 0x0: OP_8xy0(op); break;
                case 0x1: OP_8xy1(op); break;
                case 0x2: OP_8xy2(op); break;
                case 0x3: OP_8xy3(op); break;
                case 0x4: OP_8xy4(op); break;
                case 0x5: OP_8xy5(op); break;
                case 0x6: OP_8xy6(op); break;
                case 0x7: OP_8xy7(op); break;
                case 0xE: OP_8xyE(op); break;
            }
            break;

        case 0x9000: OP_9xy0(op); break;
        case 0xA000: OP_Annn(op); break;
        case 0xB000: OP_Bnnn(op); break;
        case 0xC000: OP_Cxkk(op); break;
        case 0xD000: OP_Dxyn(op); break;

        case 0xE000:
            switch (op & 0x00FF) {
                case 0x9E: OP_Ex9E(op); break;
                case 0xA1: OP_ExA1(op); break;
            }
            break;

        case 0xF000:
            switch (op & 0x00FF) {
                case 0x07: OP_Fx07(op); break;
                case 0x0A: OP_Fx0A(op); break;
                case 0x15: OP_Fx15(op); break;
                case 0x18: OP_Fx18(op); break;
                case 0x1E: OP_Fx1E(op); break;
                case 0x29: OP_Fx29(op); break;
                case 0x33: OP_Fx33(op); break;
                case 0x55: OP_Fx55(op); break;
                case 0x65: OP_Fx65(op); break;
            }
            break;
    }
}
void CPU::OP_00E0(uint16_t op) {
    display.clear();
}
void CPU::OP_00EE(uint16_t op) {
    pc = stack.pop();
}
void CPU::OP_0nnn(uint16_t op) {

}
void CPU::OP_1nnn(uint16_t op) {
    pc = op & 0x0FFF;
}
void CPU::OP_2nnn(uint16_t op) {
    uint16_t addr = op & 0x0FFF;
    stack.push(pc);
    pc = addr;
}
void CPU::OP_3xkk (uint16_t op) {
    uint8_t x = (op & 0xF00) >> 8;
    uint8_t kk = op & 0x00FF;

    if (V[x] == kk) {
        pc += 2;
    }
}
void CPU::OP_4xkk(uint16_t op) {
    uint8_t x  = (op & 0x0F00) >> 8;
    uint8_t kk = op & 0x00FF;

    if (V[x] != kk) {
        pc += 2;
    }
}
void CPU::OP_5xy0(uint16_t op) {
    uint8_t x = (op & 0xF00) >> 8;
    uint8_t y = (op & 0x00F0) >> 4;

    if (V[x] == V[y] ){
        pc += 2;
    }
}
void CPU::OP_6xkk(uint16_t op) {
    uint8_t x  = (op & 0x0F00) >> 8;
    uint8_t kk = op & 0x00FF;
    V[x] = kk;
}
void CPU::OP_7xkk(uint16_t op) {
    uint8_t x  = (op & 0x0F00) >> 8;
    uint8_t kk = op & 0x00FF;
    V[x] = V[x] + kk;
}
// 8xy0 — SET: Vx = Vy
void CPU::OP_8xy0(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    uint8_t y = (op & 0x00F0) >> 4;
    V[x] = V[y];
}

// 8xy1 — OR: Vx |= Vy
void CPU::OP_8xy1(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    uint8_t y = (op & 0x00F0) >> 4;
    V[x] |= V[y];
}

// 8xy2 — AND: Vx &= Vy
void CPU::OP_8xy2(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    uint8_t y = (op & 0x00F0) >> 4;
    V[x] &= V[y];
}

// 8xy3 — XOR: Vx ^= Vy
void CPU::OP_8xy3(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    uint8_t y = (op & 0x00F0) >> 4;
    V[x] ^= V[y];
}

// 8xy4 — ADD: Vx += Vy, VF = carry
void CPU::OP_8xy4(uint16_t op) {
    uint8_t x    = (op & 0x0F00) >> 8;
    uint8_t y    = (op & 0x00F0) >> 4;
    uint16_t sum = V[x] + V[y];
    uint8_t flag = (sum > 255) ? 1 : 0;
    V[x]   = sum & 0xFF;
    V[0xF] = flag;
}

// 8xy5 — SUB: Vx -= Vy, VF = NOT borrow (1 if Vx >= Vy)
void CPU::OP_8xy5(uint16_t op) {
    uint8_t x    = (op & 0x0F00) >> 8;
    uint8_t y    = (op & 0x00F0) >> 4;
    uint8_t flag = (V[x] >= V[y]) ? 1 : 0;
    V[x]   = V[x] - V[y];
    V[0xF] = flag;
}

// 8xy6 — SHR: VF = LSB of Vx, then Vx >>= 1
void CPU::OP_8xy6(uint16_t op) {
    uint8_t x    = (op & 0x0F00) >> 8;
    uint8_t flag = V[x] & 0x1;
    V[x] >>= 1;
    V[0xF] = flag;
}

// 8xy7 — SUBN: Vx = Vy - Vx, VF = NOT borrow (1 if Vy >= Vx)
void CPU::OP_8xy7(uint16_t op) {
    uint8_t x    = (op & 0x0F00) >> 8;
    uint8_t y    = (op & 0x00F0) >> 4;
    uint8_t flag = (V[y] >= V[x]) ? 1 : 0;
    V[x]   = V[y] - V[x];
    V[0xF] = flag;
}

// 8xyE — SHL: VF = MSB of Vx, then Vx <<= 1
void CPU::OP_8xyE(uint16_t op) {
    uint8_t x    = (op & 0x0F00) >> 8;
    uint8_t flag = (V[x] >> 7) & 0x1;
    V[x] <<= 1;
    V[0xF] = flag;
}

void CPU::OP_9xy0(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    uint8_t y = (op & 0x00F0) >> 4;
    if (V[x] != V[y]) pc += 2;
}

void CPU::OP_Annn(uint16_t op) {
    I = op & 0x0FFF;
}

void CPU::OP_Bnnn(uint16_t op) {
    pc = (op & 0x0FFF) + V[0];
}

void CPU::OP_Cxkk(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    uint8_t kk = op & 0x00FF;
    V[x] = (rand() % 256) & kk;
}

void CPU::OP_Dxyn(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    uint8_t y = (op & 0x00F0) >> 4;
    uint8_t n = op & 0x000F;

    std::vector<uint8_t> sprite(n);
    for (uint8_t i = 0; i < n; i++) {
        sprite[i] = memory.read(I + i);
    }

    V[0xF] = display.draw(V[x], V[y], sprite) ? 1 : 0;
}

void CPU::OP_Ex9E(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    if (keyboard.isKeyDown(V[x])) pc += 2;
}

void CPU::OP_ExA1(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    if (!keyboard.isKeyDown(V[x])) pc += 2;
}

void CPU::OP_Fx07(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    V[x] = delayTimer;
}

void CPU::OP_Fx0A(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    for (uint8_t i = 0; i <= 0xF; i++) {
        if (keyboard.isKeyDown(i)) {
            V[x] = i;
            return;
        }
    }
    pc -= 2;
}

void CPU::OP_Fx15(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    delayTimer = V[x];
}

void CPU::OP_Fx18(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    soundTimer = V[x];
}

void CPU::OP_Fx1E(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    I += V[x];
}

void CPU::OP_Fx29(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    I = 0x050 + (5 * V[x]);
}

void CPU::OP_Fx33(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    uint8_t value = V[x];
    memory.write(I,     value / 100);
    memory.write(I + 1, (value / 10) % 10);
    memory.write(I + 2, value % 10);
}

void CPU::OP_Fx55(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    for (uint8_t i = 0; i <= x; i++) {
        memory.write(I + i, V[i]);
    }
}

void CPU::OP_Fx65(uint16_t op) {
    uint8_t x = (op & 0x0F00) >> 8;
    for (uint8_t i = 0; i <= x; i++) {
        V[i] = memory.read(I + i);
    }
}

void CPU::execute() {
    uint16_t op = fetch();
    decode(op);
}
void CPU::tickTimers() {
    if (delayTimer > 0) delayTimer--;
    if (soundTimer > 0) soundTimer--;
}
