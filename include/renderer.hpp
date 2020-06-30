#ifndef RENDERER_HPP
#define RENDERER_HPP

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <array>

const unsigned int VIDEO_WIDTH = 64;
const unsigned int VIDEO_HEIGHT = 32;

class Renderer {
    public:
        Renderer();
        ~Renderer();
        void render();
        inline std::array<uint32_t, VIDEO_WIDTH * VIDEO_HEIGHT>& getBuffer(){
            return videoBuffer;
        }
    private:
        std::array<uint32_t, VIDEO_WIDTH * VIDEO_HEIGHT> videoBuffer;
        SDL_Window *window;
        SDL_Renderer * renderer;
        SDL_Texture *texture;
        int videoPitch;
};

#endif