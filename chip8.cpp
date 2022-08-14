#include <iostream>
#include <stdint.h>
#include <string>
#include "chip8.h"
#include <fstream>


static unsigned int fontset[] = {
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

Chip8::Chip8(): pc(512){}
Chip8::~Chip8(){}


void Chip8::load(const char* file_path) {

  // Read binary file
  std::ifstream infile(file_path, std::ios::binary);

  if (!infile.is_open()) {
    std::cout << "Error: Could not open file\n";
  } else {

    std::cout << "Reading File...\n";
    infile.seekg(0, std::ios_base::end);
    unsigned int fileLength = (unsigned int) infile.tellg();
    std::cout << "File Length: " << fileLength << "\n";
    // Go back to beginning of file
    infile.seekg(0, std::ios_base::beg);
    char contents[fileLength];
    infile.read(contents, fileLength);
    infile.close();

    if ((4095-512) > fileLength) {

      for (unsigned int i = 0; i < fileLength; i++) {
        memory[i + 512] = (uint8_t)contents[i];
      }
    } else {
      std::cout << "Error: File too large to fit into rom!\n";
    }

  //   uint16_t op = (contents[0] << 8) | (contents[1]);
  //   uint16_t code = op & 0x00FF;
  //   printf("%04x\n", code);
  //
  //   Chip8 chip;
  //
  // 
  //   switch(code) {
  //     case 0x00e0:
  //       std::cout << "Clear Screen\n";
  //       break;
  //   }

  }
}

void Chip8::execute(uint16_t opcode) {
  printf("%04x\n", opcode & 0xF000);
  
  // Checks first byte
  switch(opcode & 0xF000) {
    case 0x0000: 
      {
        // checks last byte
        switch (opcode & 0x000F) {
          case 0x0000:
            {
              std::cout << "Clear Screen" << std::endl;
              for (unsigned int i = 0; i < 2048; i++) {
                display[i] = 0;
              }
              break;
            }
        }
        break;
      }
    case 0x1000: 
      {
        std::cout << "Jump to instruction\n";
        pc = opcode & 0x0FFF;
        break;
      }
    case 0x6000:
      {
        std::cout << "Set reguster VX\n";
        // Second byte contains register number for V[X] set to
        // NN <- the last 2 bytes of opcode
        registers[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
        break;
      }
    case 0x7000:
      {
        std::cout << "Add val to VX\n";
        registers[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
        break;
      }
    case 0xA000:
      {
        std::cout << "Set index register I\n";
        break;
      }
    case 0xD000:
      {
        std::cout << "Display/Draw pixel\n";
        uint16_t x = registers[(opcode & 0x0F00)] % 64;
        uint16_t y = registers[(opcode & 0x00F0)] % 32;
        uint16_t n = registers[(opcode & 0x000F)];

        registers[15] = 0;

        for (unsigned short i = 0; i < n; i++) {

        }
        break;
      }
    default:
      std::cout << "Could not determine opcode\n";
      break;
  }
  pc += 2;
  
}
