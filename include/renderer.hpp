#ifndef RENDERER_HPP
#define RENDERER_HPP

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <array>

class Renderer {
    public:
        Renderer();
        ~Renderer();
    private:
        std::array<uint8_t, 64 * 32> videoBuffer; // uint32_t better for SDL ?
        SDL_Window *window;
};

#endif