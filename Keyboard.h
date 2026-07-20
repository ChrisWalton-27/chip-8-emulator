//
// Created by Davon on 6/14/2026.
//

#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <cstdint>


class Keyboard {
private:
    bool keys[16]{};
public:
    Keyboard();
    bool isKeyDown(uint8_t k);
    void setKey(uint8_t k, bool v);
};



#endif //KEYBOARD_H
