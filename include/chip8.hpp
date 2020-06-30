#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <memory>
#include "cpu.hpp"
#include "memory.hpp"
#include "renderer.hpp"
#include "input.hpp"

class Chip8 {
    public:
        Chip8(): cpu(nullptr), memory(nullptr), renderer(nullptr),input(nullptr), running(false){};

        void init(const char *romPath);
        void run();
        void stop();
    
    private:
        std::unique_ptr<Cpu> cpu;
        std::shared_ptr<Renderer> renderer;
        std::shared_ptr<Input> input;
        std::shared_ptr<Memory> memory;
        bool running;

        void loadRom(const char *romPath);
        void loadFont();
};

#endif