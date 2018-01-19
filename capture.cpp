#include "capture.hpp"

Capture::Capture(std::string filename, std::string format, int width, int height)
    :context(nullptr)
    ,filename(filename)
    ,format(format)
    ,width(width)
    ,height(height)
    ,stream(0)
{
    avdevice_register_all();
    av_register_all();
}

Capture::~Capture() {
    if (context != nullptr) {
        avformat_free_context(context);
    }
}

int Capture::init() {
    auto input = av_find_input_format(format.c_str());
    if (!input) {
        return 1;
    }

    std::string size = std::to_string(width) + "x" + std::to_string(height);

    AVDictionary *opts = nullptr;
    av_dict_set(&opts, "video_size", size.c_str(), 0);
    int err = avformat_open_input(&context, filename.c_str(), input, &opts);
    av_dict_free(&opts);

    if (err != 0) {
        return 2;
    }

    stream = this->searchStream(AVMEDIA_TYPE_VIDEO, AV_PIX_FMT_UYVY422);
    if (stream < 0) {
        return 3;
    }

    if (context->streams[stream]->codecpar->width  != width  ||
        context->streams[stream]->codecpar->height != height ) {
        return 4;
    }

    av_dump_format(context, 0, filename.c_str(), 0);
    return 0;
}

int Capture::searchStream(int type, int format) {
    for(unsigned int i=0; i<context->nb_streams; i++) {
        if(context->streams[i]->codecpar->codec_type==type &&
           context->streams[i]->codecpar->format==format) {
            return i;
        }
    }
    return -1;
}

bool Capture::done() {
    return false; // let's stream forever and ever and ever...
}

int Capture::decode(std::function<void (uint8_t*)> callback) {
    AVPacket packet;
    int err = av_read_frame(context, &packet);
    if (err) {
        return err;
    }
    // check if current frame is from the stream we are processing
    if (packet.stream_index != stream) {
        return 1;
    }
    callback(packet.data);
    av_packet_unref(&packet);
    return 0;
}
