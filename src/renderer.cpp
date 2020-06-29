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
		640, 
        320,
        SDL_WINDOW_OPENGL
	);
}

Renderer::~Renderer(){
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    printf("Inside Renderer destructor\n");
}