#ifndef PILINES_DISPLAY_H
#define PILINES_DISPLAY_H

#include <SDL.h>

class Display {

 public:
    Display(int width, int height);
    ~Display();

    int init();
    bool done();
    int lock(void** pixels, int* pitch);
    void render();

 private:
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

#endif
