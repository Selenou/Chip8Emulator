#include "cpu.hpp"
#include <algorithm>
#include <chrono>

Cpu::Cpu(std::shared_ptr<Memory> memory, std::shared_ptr<Renderer> renderer, std::shared_ptr<Input> input) : randGen(std::chrono::system_clock::now().time_since_epoch().count()){
    
    this->memory = memory;
    this->renderer = renderer;
    this->input = input;

    this->programCounter = ROM_MEMORY_LOCATION; // pc = 0x200

    // init instruction table
    std::fill_n(this->chip8InstructionTable, 0xF +1, &Cpu::OP_NULL);
    std::fill_n(this->chip8InstructionTable0, 0xF +1, &Cpu::OP_NULL);
    std::fill_n(this->chip8InstructionTable8, 0xF +1, &Cpu::OP_NULL);
    std::fill_n(this->chip8InstructionTableE, 0xF +1, &Cpu::OP_NULL);
    std::fill_n(this->chip8InstructionTableF, 0x65 + 1, &Cpu::OP_NULL);

    this->randByte = std::uniform_int_distribution<int>(0, 255);

    this->chip8InstructionTable[0x0] = &Cpu::Table_0xxx;
    this->chip8InstructionTable[0x1] = &Cpu::OP_1nnn;
    this->chip8InstructionTable[0x2] = &Cpu::OP_2nnn;
    this->chip8InstructionTable[0x3] = &Cpu::OP_3xkk;
    this->chip8InstructionTable[0x4] = &Cpu::OP_4xkk;
    this->chip8InstructionTable[0x5] = &Cpu::OP_5xy0;
    this->chip8InstructionTable[0x6] = &Cpu::OP_6xkk;
    this->chip8InstructionTable[0x7] = &Cpu::OP_7xkk;
    this->chip8InstructionTable[0x8] = &Cpu::Table_8xxx;
    this->chip8InstructionTable[0x9] = &Cpu::OP_9xy0;
    this->chip8InstructionTable[0xA] = &Cpu::OP_Annn;
    this->chip8InstructionTable[0xB] = &Cpu::OP_Bnnn;
    this->chip8InstructionTable[0xC] = &Cpu::OP_Cxkk;
    this->chip8InstructionTable[0xD] = &Cpu::OP_Dxyn;
    this->chip8InstructionTable[0xE] = &Cpu::Table_Exxx;
    this->chip8InstructionTable[0xF] = &Cpu::Table_Fxxx;

    this->chip8InstructionTable0[0x0] = &Cpu::OP_00E0;
	this->chip8InstructionTable0[0xE] = &Cpu::OP_00EE;

	this->chip8InstructionTable8[0x0] = &Cpu::OP_8xy0;
	this->chip8InstructionTable8[0x1] = &Cpu::OP_8xy1;
	this->chip8InstructionTable8[0x2] = &Cpu::OP_8xy2;
	this->chip8InstructionTable8[0x3] = &Cpu::OP_8xy3;
	this->chip8InstructionTable8[0x4] = &Cpu::OP_8xy4;
	this->chip8InstructionTable8[0x5] = &Cpu::OP_8xy5;
	this->chip8InstructionTable8[0x6] = &Cpu::OP_8xy6;
	this->chip8InstructionTable8[0x7] = &Cpu::OP_8xy7;
	this->chip8InstructionTable8[0xE] = &Cpu::OP_8xyE;

	this->chip8InstructionTableE[0x1] = &Cpu::OP_ExA1;
	this->chip8InstructionTableE[0xE] = &Cpu::OP_Ex9E;

	this->chip8InstructionTableF[0x07] = &Cpu::OP_Fx07;
	this->chip8InstructionTableF[0x0A] = &Cpu::OP_Fx0A;
	this->chip8InstructionTableF[0x15] = &Cpu::OP_Fx15;
	this->chip8InstructionTableF[0x18] = &Cpu::OP_Fx18;
	this->chip8InstructionTableF[0x1E] = &Cpu::OP_Fx1E;
	this->chip8InstructionTableF[0x29] = &Cpu::OP_Fx29;
	this->chip8InstructionTableF[0x33] = &Cpu::OP_Fx33;
	this->chip8InstructionTableF[0x55] = &Cpu::OP_Fx55;
	this->chip8InstructionTableF[0x65] = &Cpu::OP_Fx65;
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
    ((*this).*(chip8InstructionTable[firstDigit]))();
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
    this->renderer->getBuffer().fill(0x0);
}

void Cpu::OP_00EE(){
    this->stackPointer--;
    this->programCounter = this->stack[this->stackPointer];
}

void Cpu::OP_1nnn(){
    uint16_t address = this->opcode & 0x0FFFu;
    this->programCounter = address;
}

void Cpu::OP_2nnn(){
    uint16_t address = this->opcode & 0x0FFFu;
    this->stack[this->stackPointer] = this->programCounter;
    this->stackPointer++;
    this->programCounter = address;
}

void Cpu::OP_3xkk(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t byte = this->opcode & 0x00FFu;

    if(this->registers[Vx] == byte){
        this->programCounter += 2;
    }
}

void Cpu::OP_4xkk(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t byte = this->opcode & 0x00FFu;

    if(this->registers[Vx] != byte){
        this->programCounter += 2;
    }
}

void Cpu::OP_5xy0(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (this->opcode & 0x00F0u) >> 4u;

    if(this->registers[Vx] == Vy){
        this->programCounter += 2;
    }
}

void Cpu::OP_6xkk(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
    uint8_t byte = this->opcode & 0x00FFu;

    this->registers[Vx] = byte;
}

void Cpu::OP_7xkk(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
    uint8_t byte = this->opcode & 0x00FFu;

    this->registers[Vx] += byte;
}

void Cpu::OP_8xy0(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (this->opcode & 0x00F0u) >> 4u;

	this->registers[Vx] = this->registers[Vy];
}

void Cpu::OP_8xy1(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (this->opcode & 0x00F0u) >> 4u;

	this->registers[Vx] |= this->registers[Vy];
}

void Cpu::OP_8xy2(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (this->opcode & 0x00F0u) >> 4u;

	this->registers[Vx] &= this->registers[Vy];
}

void Cpu::OP_8xy3(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (this->opcode & 0x00F0u) >> 4u;

	this->registers[Vx] ^= this->registers[Vy];
}

void Cpu::OP_8xy4(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (this->opcode & 0x00F0u) >> 4u;

    uint16_t sum = this->registers[Vx] + this->registers[Vy];

    this->registers[0xF] = sum > 255U ? 1 : 0;
    this->registers[Vx] = sum & 0xFFu;
}

void Cpu::OP_8xy5(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (this->opcode & 0x00F0u) >> 4u;

    this->registers[0xF] = this->registers[Vx] > this->registers[Vy] ? 1 : 0;
    this->registers[Vx] -= this->registers[Vy];
}

void Cpu::OP_8xy6(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;

	this->registers[0xF] = this->registers[Vx] & 0x1u;
	this->registers[Vx] >>= 1;
}

void Cpu::OP_8xy7(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (this->opcode & 0x00F0u) >> 4u;

	this->registers[0xF] = this->registers[Vy] > this->registers[Vx] ? 1 : 0;
	this->registers[Vx] = this->registers[Vy] - this->registers[Vx];
}

void Cpu::OP_8xyE(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;

	this->registers[0xF] = (this->registers[Vx] & 0x80u) >> 7u;
	this->registers[Vx] <<= 1;
}

void Cpu::OP_9xy0(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (this->opcode & 0x00F0u) >> 4u;

	if (this->registers[Vx] != this->registers[Vy])
	{
		this->programCounter += 2;
	}
}

void Cpu::OP_Annn(){
	this->indexRegister = this->opcode & 0x0FFFu;
}

void Cpu::OP_Bnnn(){
    this->programCounter = this->registers[0] + (this->opcode & 0x0FFFu);
}

void Cpu::OP_Cxkk(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t byte = this->opcode & 0x00FFu;

	registers[Vx] = (static_cast<uint8_t>(this->randByte(this->randGen))) & byte;
}

void Cpu::OP_Dxyn(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (this->opcode & 0x00F0u) >> 4u;
	uint8_t height = this->opcode & 0x000Fu;

    uint8_t xPos = this->registers[Vx] % VIDEO_WIDTH;
	uint8_t yPos = this->registers[Vy] % VIDEO_HEIGHT;

    this->registers[0xF] = 0;

    for (unsigned int row = 0; row < height; row++){

        uint8_t spriteByte = (*this->memory)[this->indexRegister + row];

        for (unsigned int col = 0; col < 8; col++){

            uint8_t spritePixel = spriteByte & (0x80u >> col);
            uint32_t* screenPixel = &this->renderer->getBuffer()[(yPos + row) * VIDEO_WIDTH + (xPos + col)];

            if (spritePixel){
				if (*screenPixel == 0xFFFFFFFF)
				{
					this->registers[0xF] = 1;
				}

				*screenPixel ^= 0xFFFFFFFF;
			}
        }
    }
}

void Cpu::OP_Ex9E(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;

	uint8_t key = this->registers[Vx];

	if (this->input->isPressed(key))
	{
		this->programCounter += 2;
	}
}

void Cpu::OP_ExA1(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;

	uint8_t key = this->registers[Vx];

	if (!this->input->isPressed(key))
	{
		this->programCounter += 2;
	}
}

void Cpu::OP_Fx07(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	this->registers[Vx] = this->delayTimer;
}

void Cpu::OP_Fx0A(){
    printf("hello");
}

void Cpu::OP_Fx15(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	this->delayTimer = this->registers[Vx];
}

void Cpu::OP_Fx18(){
    //TODO : sound timer
}

void Cpu::OP_Fx1E(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	this->indexRegister += this->registers[Vx];
}

void Cpu::OP_Fx29(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t digit = this->registers[Vx];

	this->indexRegister = 5 * digit;
}

void Cpu::OP_Fx33(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;
	uint8_t value = this->registers[Vx];

	// Ones-place
	(*this->memory)[this->indexRegister + 2] = value % 10;
	value /= 10;

	// Tens-place
	(*this->memory)[this->indexRegister + 1] = value % 10;
	value /= 10;

	// Hundreds-place
	(*this->memory)[this->indexRegister] = value % 10;
}

void Cpu::OP_Fx55(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= Vx; i++)
	{
		(*this->memory)[this->indexRegister + i] = this->registers[i];
	}
}

void Cpu::OP_Fx65(){
    uint8_t Vx = (this->opcode & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= Vx; ++i)
	{
		this->registers[i] = (*this->memory)[this->indexRegister + i];
	}
}