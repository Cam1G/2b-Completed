#include "cpu.h"
#include "mmu.h"
#include <cstdint>
#include <iostream>
#include <string>

class programTooLargeException : public std::exception {
private:
  std::string msg = "Program too large to be read into memory.";

public:
  const char *what() { return msg.c_str(); }
};

class unreachableOpcodeException : public std::exception {
private:
  std::string msg = "Opcode is impossible in the instruction set.";

public:
  const char *what() { return msg.c_str(); }
};

two_b_completed::two_b_completed() { two_b_completed::status_flag = true; }

void two_b_completed::read_program(std::vector<uint8_t> &program) {
  if (program.size() > BANK_SIZE) {
    throw programTooLargeException();
  }

  for (int i = 0; i < program.size(); i++) {
    mmu.write(i, program[i]);
  }
}

void two_b_completed::step() {
  const uint8_t current_instruction = mmu.read(registers[PC_REGISTER]);
  const uint8_t opcode = current_instruction >> 6;
  const uint8_t rx = (current_instruction >> 3) & 0x7;
  const uint8_t ry = current_instruction & 0x7;
  switch (opcode) {
  case 0b00: { // LDST rx, [ry]
    uint8_t temp = mmu.read(registers[ry]);
    mmu.write(registers[ry], registers[rx]);
    registers[rx] = temp;
    break;
  }
  case 0b01: // nand rx, ry
    registers[rx] = ~(registers[rx] & registers[ry]);
    break;
  case 0b10: // cmp rx, ry
    status_flag = registers[rx] == registers[ry];
    break;
  case 0b11: // addeq rx, ry
    if (status_flag)
      registers[rx] += registers[ry];
    break;
  default:
    throw unreachableOpcodeException();
  }

  registers[PC_REGISTER]++;
}
