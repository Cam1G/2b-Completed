#include "assembler.h"
#include <cstdint>
#include <string>
#include <vector>

class incorrectInstructionFormatException : public std::exception {
private:
  std::string msg = "The instruction is not in an acceptable format.";

public:
  const char *what() { return msg.c_str(); }
};

class literalOutOfRangeException : public std::exception {
private:
  std::string msg = "The literal is too large to fit in 8 bits.";

public:
  const char *what() { return msg.c_str(); }
};

class opcodeDoesNotExistException : public std::exception {
private:
  std::string msg = "This opcode doesn't exist";

public:
  const char *what() { return msg.c_str(); }
};

const std::unordered_map<std::string, uint8_t>
    two_b_completed_assembler::opcodes = {
        {"LDST", 0b00}, {"NAND", 0b01}, {"CMP", 0b10}, {"ADDEQ", 0b11}};

two_b_completed_assembler::two_b_completed_assembler() {}

std::vector<uint8_t>
two_b_completed_assembler::assemble(std::vector<std::string> &program) {
  std::vector<uint8_t> binary;
  for (int line = 0; line < program.size(); line++) {
    // Read for a hex value
    if (program[line].substr(0, 2) == "0x") {
      uint hex_value = stoi(program[line].substr(2), nullptr, 16);
      if (hex_value > 255)
        throw literalOutOfRangeException();

      binary.push_back((uint8_t)hex_value);
    } else {
      int space_index = program[line].find(' ');
      int comma_index = program[line].find(',');
      // No space or comma means incorrect format
      if (space_index == -1 || comma_index == -1)
        throw incorrectInstructionFormatException();

      std::string opcode = program[line].substr(0, space_index);
      // Takes a substring from after the space (no R) until the comma
      std::string rx =
          program[line].substr(space_index + 2, comma_index - space_index - 2);
      std::string ry = program[line].substr(comma_index + 3);
      // Returns true if the opcode doesn't exist
      if (opcodes.count(opcode) == 0)
        throw opcodeDoesNotExistException();

      // Shifts the registers and opcode to the correct places
      uint8_t binary_instruction =
          (opcodes.at(opcode) << 6) | stoi(rx) << 3 | stoi(ry);
      binary.push_back(binary_instruction);
    }
  }
  return binary;
}
