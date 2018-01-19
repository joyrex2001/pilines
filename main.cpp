#include "capture.hpp"
#include "display.hpp"
#include "filter.hpp"
#include <iostream>

int main() {
    const auto width = 720;
    const auto height = 480;

    auto capture = new Capture("/dev/video0","v4l2",width,height);
    auto err = capture->init();
    if (err != 0) {
        std::cout << "Error initalizing capture device" << std::endl;
        exit(err);
    }

    auto display = new Display(width,height);
    err = display->init();
    if (err != 0) {
        std::cout << "Error initalizing display" << std::endl;
        exit(err);
    }

    auto filter = new Filter(width,height);

    while (!display->done() && !capture->done()) {
        int pitch;
        uint8_t *pixels;
        err = display->lock((void **)&pixels,&pitch);
        if (err !=0) {
            std::cout << "Error locking display" << std::endl;
            exit(err);
        }
        capture->decode(filter->scanlines(pixels,pitch));
        display->render();
    }

    delete display;
    delete capture;
}
