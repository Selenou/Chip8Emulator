#include "cpu.hpp"
#include <algorithm>

Cpu::Cpu(std::shared_ptr<Memory> memory, std::shared_ptr<Renderer> renderer){
    this->memory = memory;
    this->renderer = renderer;

    this->programCounter = ROM_MEMORY_LOCATION; // pc = 0x200

    // init instruction table
    std::fill_n(this->chip8InstructionTable, 0xF +1, &Cpu::OP_NULL);
    std::fill_n(this->chip8InstructionTable0, 0xF +1, &Cpu::OP_NULL);
    std::fill_n(this->chip8InstructionTable8, 0xF +1, &Cpu::OP_NULL);
    std::fill_n(this->chip8InstructionTableE, 0xF +1, &Cpu::OP_NULL);
    std::fill_n(this->chip8InstructionTableF, 0x65 + 1, &Cpu::OP_NULL);

    chip8InstructionTable[0x0] = &Cpu::Table_0xxx;
    chip8InstructionTable[0x1] = &Cpu::OP_1nnn;
    chip8InstructionTable[0x2] = &Cpu::OP_2nnn;
    chip8InstructionTable[0x3] = &Cpu::OP_3xkk;
    chip8InstructionTable[0x4] = &Cpu::OP_4xkk;
    chip8InstructionTable[0x5] = &Cpu::OP_5xy0;
    chip8InstructionTable[0x6] = &Cpu::OP_6xkk;
    chip8InstructionTable[0x7] = &Cpu::OP_7xkk;
    chip8InstructionTable[0x8] = &Cpu::Table_8xxx;
    chip8InstructionTable[0x9] = &Cpu::OP_9xy0;
    chip8InstructionTable[0xA] = &Cpu::OP_Annn;
    chip8InstructionTable[0xB] = &Cpu::OP_Bnnn;
    chip8InstructionTable[0xC] = &Cpu::OP_Cxkk;
    chip8InstructionTable[0xD] = &Cpu::OP_Dxyn;
    chip8InstructionTable[0xE] = &Cpu::Table_Exxx;
    chip8InstructionTable[0xF] = &Cpu::Table_Fxxx;

    chip8InstructionTable0[0x0] = &Cpu::OP_00E0;
	chip8InstructionTable0[0xE] = &Cpu::OP_00EE;

	chip8InstructionTable8[0x0] = &Cpu::OP_8xy0;
	chip8InstructionTable8[0x1] = &Cpu::OP_8xy1;
	chip8InstructionTable8[0x2] = &Cpu::OP_8xy2;
	chip8InstructionTable8[0x3] = &Cpu::OP_8xy3;
	chip8InstructionTable8[0x4] = &Cpu::OP_8xy4;
	chip8InstructionTable8[0x5] = &Cpu::OP_8xy5;
	chip8InstructionTable8[0x6] = &Cpu::OP_8xy6;
	chip8InstructionTable8[0x7] = &Cpu::OP_8xy7;
	chip8InstructionTable8[0xE] = &Cpu::OP_8xyE;

	chip8InstructionTableE[0x1] = &Cpu::OP_ExA1;
	chip8InstructionTableE[0xE] = &Cpu::OP_Ex9E;

	chip8InstructionTableF[0x07] = &Cpu::OP_Fx07;
	chip8InstructionTableF[0x0A] = &Cpu::OP_Fx0A;
	chip8InstructionTableF[0x15] = &Cpu::OP_Fx15;
	chip8InstructionTableF[0x18] = &Cpu::OP_Fx18;
	chip8InstructionTableF[0x1E] = &Cpu::OP_Fx1E;
	chip8InstructionTableF[0x29] = &Cpu::OP_Fx29;
	chip8InstructionTableF[0x33] = &Cpu::OP_Fx33;
	chip8InstructionTableF[0x55] = &Cpu::OP_Fx55;
	chip8InstructionTableF[0x65] = &Cpu::OP_Fx65;
}

void Cpu::performCycle(){
    this->fetchNextInstruction();
    this->execute();
    this->updateTimers();
}

void Cpu::fetchNextInstruction(){
    this->opcode = (*this->memory)[this->programCounter];       // opcode = 0xAB
    this->opcode <<= 8u;                                        // opcode = 0xAB00
    this->opcode |= (*this->memory)[this->programCounter + 1];  // opcode = 0xABCD

    this->programCounter += 2;
}

void Cpu::execute(){

    int firstDigit = (this->opcode & 0xF000u) >> 12; // 0xABCD => 0xA

    //((*this).*(chip8InstructionTable[0]))();
}

void Cpu::updateTimers(){
    if (this->delayTimer > 0){
        this->delayTimer--;
    }
}

void Cpu::Table_0xxx(){
    ((*this).*(chip8InstructionTable0[this->opcode & 0x000Fu]))();
}

void Cpu::Table_8xxx(){
    ((*this).*(chip8InstructionTable8[this->opcode & 0x000Fu]))();
}

void Cpu::Table_Exxx(){
    ((*this).*(chip8InstructionTableE[this->opcode & 0x000Fu]))();
}

void Cpu::Table_Fxxx(){
    ((*this).*(chip8InstructionTableF[this->opcode & 0x00FFu]))();
}

void Cpu::OP_NULL(){
    // Do nothing
}

void Cpu::OP_00E0(){
    printf("hello");
}

void Cpu::OP_00EE(){
    printf("hello");
}

void Cpu::OP_1nnn(){
    printf("hello");
}

void Cpu::OP_2nnn(){
    printf("hello");
}

void Cpu::OP_3xkk(){
    printf("hello");
}

void Cpu::OP_4xkk(){
    printf("hello");
}

void Cpu::OP_5xy0(){
    printf("hello");
}

void Cpu::OP_6xkk(){
    printf("hello");
}

void Cpu::OP_7xkk(){
    printf("hello");
}

void Cpu::OP_8xy0(){
    printf("hello");
}

void Cpu::OP_8xy1(){
    printf("hello");
}

void Cpu::OP_8xy2(){
    printf("hello");
}

void Cpu::OP_8xy3(){
    printf("hello");
}

void Cpu::OP_8xy4(){
    printf("hello");
}

void Cpu::OP_8xy5(){
    printf("hello");
}

void Cpu::OP_8xy6(){
    printf("hello");
}

void Cpu::OP_8xy7(){
    printf("hello");
}

void Cpu::OP_8xyE(){
    printf("hello");
}

void Cpu::OP_9xy0(){
    printf("hello");
}

void Cpu::OP_Annn(){
    printf("hello");
}

void Cpu::OP_Bnnn(){
    printf("hello");
}

void Cpu::OP_Cxkk(){
    printf("hello");
}

void Cpu::OP_Dxyn(){
    printf("hello");
}

void Cpu::OP_Ex9E(){
    printf("hello");
}

void Cpu::OP_ExA1(){
    printf("hello");
}

void Cpu::OP_Fx07(){
    printf("hello");
}

void Cpu::OP_Fx0A(){
    printf("hello");
}

void Cpu::OP_Fx15(){
    printf("hello");
}

void Cpu::OP_Fx18(){
    printf("hello");
}

void Cpu::OP_Fx1E(){
    printf("hello");
}

void Cpu::OP_Fx29(){
    printf("hello");
}

void Cpu::OP_Fx33(){
    printf("hello");
}

void Cpu::OP_Fx55(){
    printf("hello");
}

void Cpu::OP_Fx65(){
    printf("hello");
}