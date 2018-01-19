#include "filter.hpp"

Filter::Filter(int width, int height)
    :width(width)
    ,height(height)
    ,blur(0.7)
    ,brightness(1.0)
{
}

Filter::~Filter() {
}

void Filter::setBlur(float b) {
    blur = b;
}

void Filter::setBrightness(float b) {
    brightness = b;
}

std::function<void (uint8_t*)> Filter::scanlines(uint8_t *target,int pitch) {
    return [this,target,pitch] (uint8_t *source) {
        for (int y = 0; y < height ; y+=2) {
            int line1 = (y+0) * width * 2;
            int line2 = (y+1) * width * 2;
            for (int x = 0; x < width; x++) {
                target[line1 + x*2 + 0] = source[line1 + x*2 + 0];
                target[line1 + x*2 + 1] = int(((source[line1 + x*2 + 1]+source[line2 + x*2 + 1])/2)*brightness);
                target[line2 + x*2 + 0] = source[line2 + x*2 + 0];
                target[line2 + x*2 + 1] = int(source[line2 + x*2 + 1]*blur);
            }
        }
    };
}
