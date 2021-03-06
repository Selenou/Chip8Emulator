#include "chip8.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <chrono>

void Chip8::init(const char *romPath){
    this->memory = std::make_shared<Memory>();
    this->renderer = std::make_shared<Renderer>();
	this->input = std::make_shared<Input>();

	this->cpu = std::make_unique<Cpu>(this->memory, this->renderer, this->input);

    this->loadRom(romPath);
	this->loadFont();
}

void Chip8::run(){
	float cycleDelay = 3 ; // ms
	this->running = true;
	auto lastCycleTime = std::chrono::high_resolution_clock::now();

	while(this->running){
		bool shouldStop = this->input->update();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

		if(shouldStop){
			this->stop();
		}

		if (dt > cycleDelay){
			lastCycleTime = currentTime;
			this->cpu->performCycle();
			this->renderer->render();
		}
	}
}

void Chip8::stop(){
	this->running = false;
}

void Chip8::loadRom(const char *romPath){
    std::ifstream romFile(romPath, std::ios::binary); 
	if (romFile.is_open()){
		auto romIt = std::istreambuf_iterator<char>(romFile);
		auto eos = std::istreambuf_iterator<char>();
		std::vector<char> romData(romIt, eos);

		this->memory->loadRom(std::move(romData));
	} else {
        throw std::runtime_error("Failed to open rom file");
	}
}

void Chip8::loadFont(){
	std::array<uint8_t, 80> fontset {
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	this->memory->loadFont(std::move(fontset));
}