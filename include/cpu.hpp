#ifndef CPP_HPP
#define CPP_HPP

#include "stdint.h"
#include <memory>
#include <random>
#include "memory.hpp"
#include "renderer.hpp"
#include "input.hpp"

class Cpu {
    public:
        Cpu(std::shared_ptr<Memory> memory, std::shared_ptr<Renderer> renderer, std::shared_ptr<Input> input);
        void performCycle();

    private:
        uint16_t    programCounter; // holds the address of the next instruction to execute
        uint8_t     registers[16];  // V0 -> VF, VF is used as a flag
        uint16_t    indexRegister;  // store memory addresses for use in operations
        uint16_t    stack[16];      // keep track of the order of execution
        uint8_t     stackPointer;   // tell us where in the 16-levels of stack our most recent value was placed
        uint16_t    opcode;
        uint8_t     delayTimer;

        std::default_random_engine randGen;
	    std::uniform_int_distribution<int> randByte;

        std::shared_ptr<Memory> memory;
        std::shared_ptr<Renderer> renderer;
        std::shared_ptr<Input> input;

        void fetchNextInstruction();
        void execute();
        void updateTimers();

        void OP_NULL(); // CLS
        void OP_00E0(); // CLS
        void OP_00EE(); // RET
        void OP_1nnn(); // JP address
        void OP_2nnn(); // CALL address
        void OP_3xkk(); // SE Vx, byte        
        void OP_4xkk(); // SNE Vx, byte        
        void OP_5xy0(); // SE Vx, Vy       
        void OP_6xkk(); // LD Vx, byte       
        void OP_7xkk(); // ADD Vx, byte      
        void OP_8xy0(); // LD Vx, Vy  
        void OP_8xy1(); // OR Vx, Vy  
        void OP_8xy2(); // AND Vx, Vy       
        void OP_8xy3(); // XOR Vx, Vy        
        void OP_8xy4(); // ADD Vx, Vy       
        void OP_8xy5(); // SUB Vx, Vy        
        void OP_8xy6(); // SHR Vx       
        void OP_8xy7(); // SUBN Vx, Vy        
        void OP_8xyE(); // SHL Vx       
        void OP_9xy0(); // SNE Vx, Vy        
        void OP_Annn(); // LD I, address       
        void OP_Bnnn(); // JP V0, address        
        void OP_Cxkk(); // RND Vx, byte        
        void OP_Dxyn(); // DRW Vx, Vy, height       
        void OP_Ex9E(); // SKP Vx        
        void OP_ExA1(); // SKNP Vx        
        void OP_Fx07(); // LD Vx, DT        
        void OP_Fx0A(); // LD Vx, K       
        void OP_Fx15(); // LD DT, Vx       
        void OP_Fx18(); // LD ST, Vx        
        void OP_Fx1E(); // ADD I, Vx        
        void OP_Fx29(); // LD F, Vx       
        void OP_Fx33(); // LD B, Vx       
        void OP_Fx55(); // LD [I], Vx
        void OP_Fx65(); // LD Vx, [I]

        void Table_0xxx();
        void Table_8xxx();
        void Table_Exxx();
        void Table_Fxxx();

        typedef void (Cpu::*instructionTable)();

        instructionTable chip8InstructionTable[0xF +1];             // Base table
        instructionTable chip8InstructionTable0[0xF +1];            // Special table
        instructionTable chip8InstructionTable8[0xF +1];            // Arithmetic table
        instructionTable chip8InstructionTableE[0xF +1];            // Skip table
        instructionTable chip8InstructionTableF[0x65 + 1];          // Timers and Keyboard table
};

#endif