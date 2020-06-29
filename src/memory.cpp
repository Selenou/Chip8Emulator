#include "memory.hpp"
#include <array>

uint8_t Memory::operator[](uint16_t index){
    return this->memory[index];
}

void Memory::loadRom(std::vector<char>&& buffer){
    uint8_t *iterator = std::begin(this->memory);
    std::advance(iterator, ROM_MEMORY_LOCATION);
    std::copy(buffer.begin(), buffer.end(), iterator);
}

void Memory::loadFont(std::array<uint8_t, FONT_SET_SIZE>&& fontset){
    uint8_t *iterator = std::begin(this->memory);
    std::copy(fontset.begin(), fontset.end(), iterator);
}