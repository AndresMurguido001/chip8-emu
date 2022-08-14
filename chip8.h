#ifndef CHIP8_H
#define CHIP8_H
#include <stdint.h>

class Chip8 {
  
  public:
    uint8_t memory[4096];
    uint8_t display[64 * 32];
    int pc;
    uint16_t I;
    uint16_t stack;
    uint8_t delay;
    uint8_t sound;
    uint8_t registers[16];

  Chip8();
  ~Chip8();
  void execute(uint16_t opcode);
  void load(const char* file_name);
};

#endif
