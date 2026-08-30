//
// Created by Davon on 8/29/2026.
//

#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "Chip8.h"


class Debugger {
private:
    bool running = true;
    bool stepRequested = false;

public:
    void update(Chip8& chip8);
    void run();
    void pause();
    void step();
    bool isRunning() const;

};



#endif //DEBUGGER_H
