#include "Display.h"

Display::Display() {
    clear();
}

void Display::clear() {
    for (int x = 0; x < 64; x++) {
        for (int y = 0; y < 32; y++) {
            pixels[x][y] = false;
        }
    }
}

bool Display::draw(uint8_t x, uint8_t y, const std::vector<uint8_t>& sprite) {
    bool collision = false;
    for (size_t row = 0; row < sprite.size(); row++) {
        uint8_t byte = sprite[row];
        for (int col = 0; col < 8; col++) {
            bool spriteBit = (byte & (0x80 >> col)) != 0;
            if (spriteBit) {
                int px = (x + col) % 64;
                int py = (y + row) % 32;

                bool oldPixel = pixels[px][py];
                bool newPixel = oldPixel ^ spriteBit;

                if (oldPixel && !newPixel) {
                    collision = true;
                }

                pixels[px][py] = newPixel;
            }
        }
    }

    return collision;
}
