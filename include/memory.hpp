#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <vector>

const size_t FONT_SET_SIZE = 80;
const size_t ROM_MEMORY_LOCATION = 0x200;

class Memory {
    public:
        uint8_t& operator[](uint16_t index);
        void loadRom(std::vector<char>&& buffer);
        void loadFont(std::array<uint8_t, FONT_SET_SIZE>&& fontset);
    private:
        uint8_t memory[4096]; // from 0x0 to 0xFFF
};

#endif