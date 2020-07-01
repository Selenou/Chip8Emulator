#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL2/SDL.h>
#include <array>

class Input{
    public:
        bool update();
        uint8_t isPressed(const uint8_t keyCode);
        void reset();

    private :
        std::array<uint8_t, 16> keys;

        void pressedUp(const uint8_t keyCode);
        void pressedDown(const uint8_t keyCode);

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