#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

class Memory {
private:
    uint8_t data[4096]{};

public:
    Memory();
    uint8_t read(uint16_t addr);
    uint16_t read16(uint16_t addr) const;
    void write(uint16_t addr, uint8_t value);
};

#endif