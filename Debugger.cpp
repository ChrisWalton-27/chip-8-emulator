//
// Created by Davon on 8/29/2026.
//

#include "Debugger.h"

void Debugger::run() {running = true;}
void Debugger::pause() {running = false;}
void Debugger::step() {running = false; stepRequested = true;}
bool Debugger::isRunning() const {return running;}

void Debugger::update(Chip8& chip8) {
    if (running) {
        chip8.cycle();
    }
    else if (stepRequested) {
        chip8.cycle();
        stepRequested = false;
    }
}