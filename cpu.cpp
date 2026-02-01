#include "cpu.h"
#include <algorithm>
#include <cstdint>
#include <string>
#include <utility>

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
  if (program.size() > memory.size()) {
    throw programTooLargeException();
  }

  for (int i = 0; i < program.size(); i++) {
    memory[i] = program[i];
  }
}

void two_b_completed::step() {
  const uint8_t current_instruction = memory[registers[PC_REGISTER]];
  const uint8_t opcode = current_instruction >> 6;
  const uint8_t rx = (current_instruction >> 3) & 0x7;
  const uint8_t ry = current_instruction & 0x7;
  switch (opcode) {
  case 0b00: // LDST rx, [ry]
    std::swap(registers[rx], memory[registers[ry]]);
    break;
  case 0b01: // NAND rx, ry
    registers[rx] = ~(registers[rx] & registers[ry]);
    break;
  case 0b10: // CMP rx, ry
    status_flag = registers[rx] == registers[ry];
    break;
  case 0b11: // ADDEQ rx, ry
    if (status_flag)
      registers[rx] += registers[ry];
    break;
  default:
    throw unreachableOpcodeException();
  }
  registers[PC_REGISTER]++;
}
