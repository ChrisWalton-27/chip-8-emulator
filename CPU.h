//
// Created by Davon on 6/15/2026.
//

#ifndef CPU_H
#define CPU_H
#include <cstdint>
#include <cstdlib>
#include "Display.h"
#include "Keyboard.h"
#include "Memory.h"
#include "Stack.h"


class CPU {
private:

    Memory& memory;
    Display& display;
    Keyboard& keyboard;
    Stack& stack;

    uint16_t pc = 0x200;
    uint16_t I = 0;
    uint8_t V[16]{};
    uint8_t delayTimer = 0;
    uint8_t soundTimer = 0;
    uint16_t currentPC = 0x200;
    uint16_t currentOpcode = 0;


private:
    // opcode handlers
    void OP_00E0(uint16_t op);
    void OP_00EE(uint16_t op);
    void OP_0nnn(uint16_t op);

    void OP_1nnn(uint16_t op);
    void OP_2nnn(uint16_t op);
    void OP_3xkk(uint16_t op);
    void OP_4xkk(uint16_t op);
    void OP_5xy0(uint16_t op);
    void OP_6xkk(uint16_t op);
    void OP_7xkk(uint16_t op);

    void OP_8xy0(uint16_t op);
    void OP_8xy1(uint16_t op);
    void OP_8xy2(uint16_t op);
    void OP_8xy3(uint16_t op);
    void OP_8xy4(uint16_t op);
    void OP_8xy5(uint16_t op);
    void OP_8xy6(uint16_t op);
    void OP_8xy7(uint16_t op);
    void OP_8xyE(uint16_t op);

    void OP_9xy0(uint16_t op);
    void OP_Annn(uint16_t op);
    void OP_Bnnn(uint16_t op);
    void OP_Cxkk(uint16_t op);
    void OP_Dxyn(uint16_t op);

    void OP_Ex9E(uint16_t op);
    void OP_ExA1(uint16_t op);

    void OP_Fx07(uint16_t op);
    void OP_Fx0A(uint16_t op);
    void OP_Fx15(uint16_t op);
    void OP_Fx18(uint16_t op);
    void OP_Fx1E(uint16_t op);
    void OP_Fx29(uint16_t op);
    void OP_Fx33(uint16_t op);
    void OP_Fx55(uint16_t op);
    void OP_Fx65(uint16_t op);

public:
    CPU(Memory& mem, Display& disp ,Keyboard& kb, Stack& st);
    uint16_t fetch();
    void decode(uint16_t op);
    void execute();
    void tickTimers();
    void clear();

    uint16_t getPC() const {return pc;}
    uint16_t getI() const {return I;}
    uint8_t getRegister(int index) const {return V[index];}
    void setRegister(int index, uint8_t value);
    uint8_t getDelayTimer() const {return delayTimer;}
    uint8_t getSoundTimer() const {return soundTimer;}
    uint16_t getCurrentPC() const {return currentPC;}
    uint16_t getCurrentOpcode() const {return currentOpcode;}
};



#endif //CPU_H
