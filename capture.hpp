#ifndef PILINES_CAPTURE_H
#define PILINES_CAPTURE_H

extern "C" {
#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
}
#include <string>
#include <functional>

class Capture {

 public:
    Capture(std::string filename, std::string format, int width, int height);
    ~Capture();

    int init();
    bool done();
    int decode(std::function<void (uint8_t*)> callback);

 private:
    int searchStream(int stream, int format);
    AVFormatContext *context;

    std::string filename;
    std::string format;
    int width;
    int height;
    int stream;
};

#endif
