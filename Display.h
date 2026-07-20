#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>
#include <vector>

class Display {
private:
    bool pixels[64][32]{};

public:
    Display();
    void clear();
    bool draw(uint8_t x, uint8_t y, const std::vector<uint8_t>& sprite);

    const bool* getPixels() const { return &pixels[0][0]; }
    // Display.h
    bool getPixel(int x, int y) const { return pixels[x][y]; }
};

#endif // DISPLAY_H
