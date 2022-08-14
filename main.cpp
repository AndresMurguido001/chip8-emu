#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include "chip8.h"

int main(int argc, char *argv[]) {


  Chip8 chip8 = Chip8();

  chip8.load(argv[1]);


  for (int i = 0; i < 96; i++) {

    // This appends the 2 bytes of the opcode into the format
    // 0x1234
    uint16_t opcode = chip8.memory[chip8.pc] << 8 | chip8.memory[chip8.pc + 1];

    chip8.execute(opcode);
  }

  return 0;

}
