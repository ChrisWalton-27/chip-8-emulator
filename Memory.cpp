#include "Memory.h"

Memory::Memory() {}

uint8_t Memory::read(uint16_t addr) {
    return data[addr];
}
uint16_t Memory::read16(uint16_t addr) const {
    return (data[addr] << 8) | data[addr + 1];
}
void Memory::write(uint16_t addr, uint8_t value) {
    data[addr] = value;
}