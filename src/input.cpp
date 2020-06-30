#include "input.hpp"

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

bool Input::isPressed(const uint8_t keyCode){
    auto keyState = this->keys.find(keyCode);
    return keyState == this->keys.end() ? false : keyState->second;
}

void Input::pressedUp(const uint8_t keyCode){
    if(this->isKeyInMap(keyCode)){
        this->keys[keyCode] = false; 
    } 
}

void Input::pressedDown(const uint8_t keyCode){
    if(this->isKeyInMap(keyCode)){
        this->keys[keyCode] = true;
    }
}

bool Input::isKeyInMap(const uint8_t keyCode){
    auto keyState = this->keys.find(keyCode);
    return keyState == this->keys.end() ? false : true;
}