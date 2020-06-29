#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL2/SDL.h>
#include <map>

class Input{
    public:
        bool update();
        bool isPressed(const char keyCode);

    private :
        std::map<SDL_Keycode, bool> keys {
            {SDLK_x, false}, {SDLK_1, false}, {SDLK_2, false}, {SDLK_3, false}, 
            {SDLK_q, false}, {SDLK_w, false}, {SDLK_e, false}, {SDLK_a, false}, 
            {SDLK_s, false}, {SDLK_d, false}, {SDLK_z, false}, {SDLK_c, false}, 
            {SDLK_4, false}, {SDLK_r, false}, {SDLK_f, false}, {SDLK_v, false}
        };

        void pressedUp(const char keyCode);
        void pressedDown(const char keyCode);
        bool isKeyInMap(const char keyCode);

        /*
            Keypad       Keyboard
            +-+-+-+-+    +-+-+-+-+
            |1|2|3|C|    |1|2|3|4|
            +-+-+-+-+    +-+-+-+-+
            |4|5|6|D|    |Q|W|E|R|
            +-+-+-+-+ => +-+-+-+-+
            |7|8|9|E|    |A|S|D|F|
            +-+-+-+-+    +-+-+-+-+
            |A|0|B|F|    |Z|X|C|V|
            +-+-+-+-+    +-+-+-+-+
        */
};

#endif