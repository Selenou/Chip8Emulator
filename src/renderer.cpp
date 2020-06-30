#include "renderer.hpp"
#include <stdexcept>

Renderer::Renderer(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error(SDL_GetError());
	}

    this->window = SDL_CreateWindow(
		"Chip8 Emulator",
		SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
		VIDEO_WIDTH * 10, 
        VIDEO_HEIGHT * 10,
        SDL_WINDOW_OPENGL
	);

    this->renderer = SDL_CreateRenderer(
        this->window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    this->texture = SDL_CreateTexture(
        this->renderer,
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        VIDEO_WIDTH, 
        VIDEO_HEIGHT
    );

    videoPitch = sizeof(this->videoBuffer[0]) * VIDEO_WIDTH;
}

void Renderer::render(){
    SDL_UpdateTexture(this->texture, nullptr, &(this->videoBuffer), this->videoPitch);
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(this->renderer);
}

Renderer::~Renderer(){
    SDL_DestroyTexture(this->texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}