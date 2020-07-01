#include <iostream>
#include "chip8.hpp"

int main(int argc, char* argv[]){

	/*if(argc != 2) {
		std::cout << "Please provide a rom path" << std::endl;
		return 1;
	}*/

	try{
		Chip8 chip8;
		chip8.init("roms/Breakout.ch8"/*argv[1]*/);
		chip8.run();
	} catch(std::runtime_error error){
		std::cout << "Exception : " << error.what() << std::endl;
		return 1;
	}

	return 0;
}