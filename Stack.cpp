#include "Stack.h"
#include <stdexcept>

Stack::Stack() : data{}, sp(0) {}

void Stack::push(uint16_t value) {
    if (sp >= 16) {
        throw std::runtime_error("Stack overflow: CHIP-8 stack is full");
    }

    data[sp] = value;
    sp++;
}

uint16_t Stack::pop() {
    if (sp == 0) {
        throw std::runtime_error("Stack underflow: CHIP-8 stack is empty");
    }

    sp--;
    return data[sp];
}
