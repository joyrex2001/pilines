#include "display.hpp"

Display::Display(int width, int height)
    :width(width)
    ,height(height)
    ,window(nullptr)
    ,renderer(nullptr)
    ,texture(nullptr)
{
}

Display::~Display() {
    if (texture != nullptr) SDL_DestroyTexture(texture);
    if (renderer != nullptr) SDL_DestroyRenderer(renderer);
    if (window != nullptr) SDL_DestroyWindow(window);
}

int Display::init() {
    int err = SDL_Init(SDL_INIT_EVERYTHING);
    if (err!=0) {
        return 1;
    }
    window = SDL_CreateWindow("", 0, 0, width, height, SDL_WINDOW_BORDERLESS);
    if (!window) {
        return 2;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        return 3;
    }
    texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_UYVY,SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!texture) {
        return 4;
    }
    SDL_ShowCursor(SDL_DISABLE);
    return 0;
}

int Display::lock(void **pixels, int* pitch) {
    return SDL_LockTexture(texture, nullptr, pixels, pitch);
}

void Display::render() {
    SDL_UnlockTexture(texture);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

bool Display::done() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}
