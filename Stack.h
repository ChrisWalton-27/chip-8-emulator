#ifndef STACK_H
#define STACK_H
#include <cstdint>

class Stack {
private:
    uint16_t data[16]{};
    uint8_t sp = 0;

public:
    Stack();
    void push(uint16_t value);
    uint16_t pop();
    uint8_t getSP() const {return sp;}
    uint16_t getValue(int index) const {return data[index];}
};

#endif //STACK_H
