//
// Created by Davon on 8/29/2026.
//

#include "Debugger.h"

void Debugger::run() {running = true;}
void Debugger::pause() {running = false;}
void Debugger::step() {running = false; stepRequested = true;}
bool Debugger::isRunning() const {return running;}

void Debugger::addBreakpoint(uint16_t addr) {
    breakpoints.insert(addr);
}
void Debugger::removeBreakpoint(uint16_t addr) {
    breakpoints.erase(addr);
}
bool Debugger::hasBreakpoint(uint16_t addr) {
    return breakpoints.count(addr) > 0;
}
void Debugger::update(Chip8& chip8) {
    uint16_t pc = chip8.getCPU().getPC();
    if (breakpoints.count(pc)) {
        running = false;
    }
    if (running) {
        chip8.cycle();
    }
    else if (stepRequested) {
        chip8.cycle();
        stepRequested = false;
    }
}