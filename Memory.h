#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

class Memory {
private:
    uint8_t data[4096]{};

public:
    Memory();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

#endif