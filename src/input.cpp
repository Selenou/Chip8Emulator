#include "input.hpp"
#include <iostream>

bool Input::update(){
    SDL_Event event;
    
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            return true;
        }

        SDL_Keycode keyCode = event.key.keysym.sym;

        if(event.type == SDL_KEYDOWN){
            this->pressedDown(keyCode);
        } else if(event.type == SDL_KEYUP){
            this->pressedUp(keyCode);
        }
    }

    return false;
}

void Input::reset(){
    this->keys.fill(0);
}

uint8_t Input::isPressed(const uint8_t keyCode){
    auto c= this->keys[keyCode];
    return c;
}

void Input::pressedUp(const uint8_t keyCode){
    switch (keyCode){
        case SDLK_x: this->keys[0] = 0; break;
        case SDLK_1: this->keys[1] = 0; break;
        case SDLK_2: this->keys[2] = 0; break;
        case SDLK_3: this->keys[3] = 0; break;
        case SDLK_q: this->keys[4] = 0; break;
        case SDLK_w: this->keys[5] = 0; break;
        case SDLK_e: this->keys[6] = 0; break;
        case SDLK_a: this->keys[7] = 0; break;
        case SDLK_s: this->keys[8] = 0; break;
        case SDLK_d: this->keys[9] = 0; break;
        case SDLK_z: this->keys[0xA] = 0; break;
        case SDLK_c: this->keys[0xB] = 0; break;
        case SDLK_4: this->keys[0xC] = 0; break;
        case SDLK_r: this->keys[0xD] = 0; break;
        case SDLK_f: this->keys[0xE] = 0; break;
        case SDLK_v: this->keys[0xF] = 0; break;
    } 
}

void Input::pressedDown(const uint8_t keyCode){  
    switch (keyCode){
        case SDLK_x: this->keys[0] = 1; break;
        case SDLK_1: this->keys[1] = 1; break;
        case SDLK_2: this->keys[2] = 1; break;
        case SDLK_3: this->keys[3] = 1; break;
        case SDLK_q: this->keys[4] = 1; break;
        case SDLK_w: this->keys[5] = 1; break;
        case SDLK_e: this->keys[6] = 1; break;
        case SDLK_a: this->keys[7] = 1; break;
        case SDLK_s: this->keys[8] = 1; break;
        case SDLK_d: this->keys[9] = 1; break;
        case SDLK_z: this->keys[0xA] = 1; break;
        case SDLK_c: this->keys[0xB] = 1; break;
        case SDLK_4: this->keys[0xC] = 1; break;
        case SDLK_r: this->keys[0xD] = 1; break;
        case SDLK_f: this->keys[0xE] = 1; break;
        case SDLK_v: this->keys[0xF] = 1; break;
    }
}