#ifndef PILINES_FILTER_H
#define PILINES_FILTER_H

#include "capture.hpp"
#include <functional>

class Filter {

 public:
    Filter(int width, int height);
    ~Filter();

    void setBlur(float blur);
    void setBrightness(float brightness);
    std::function<void (uint8_t*)> scanlines(uint8_t *target,int pitch);

 private:
    int width;
    int height;
    float blur;
    float brightness;
};

#endif
