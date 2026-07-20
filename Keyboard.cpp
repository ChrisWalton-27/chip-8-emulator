//
// Created by Davon on 6/14/2026.
//

#include "Keyboard.h"
Keyboard::Keyboard() {
}
bool Keyboard::isKeyDown(uint8_t k) {
    return keys[k];
}
void Keyboard::setKey(uint8_t k, bool v) {
    keys[k] = v;
}

