//
// Created by Davon on 8/29/2026.
//

#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "Chip8.h"
#include <unordered_set>


class Debugger {
private:
    bool running = true;
    bool stepRequested = false;
    std::unordered_set<uint16_t> breakpoints;

public:
    void update(Chip8& chip8);
    void run();
    void pause();
    void step();
    bool isRunning() const;

    void addBreakpoint(uint16_t addr);
    void removeBreakpoint(uint16_t addr);
    bool hasBreakpoint(uint16_t addr);

};



#endif //DEBUGGER_H
