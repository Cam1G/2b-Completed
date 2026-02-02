#include "disassembler.h"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

const std::unordered_map<uint8_t, std::string>
    two_b_completed_disassembler::bin_to_opcodes = {
        {0b00, "LDST"}, {0b01, "NAND"}, {0b10, "CMP"}, {0b11, "ADDEQ"}};

two_b_completed_disassembler::two_b_completed_disassembler() {}

// The issue is there is no way of discerning data from instruction so I
// interpret all data as instruction
std::vector<std::string>
two_b_completed_disassembler::disassemble(std::vector<uint8_t> &machine_code) {
  std::vector<std::string> program;
  for (int line = 0; line < machine_code.size(); line++) {
    std::string instruction = "";
    instruction += bin_to_opcodes.at(machine_code[line] >> 6);
    instruction += ' ';
    uint8_t rx = machine_code[line] >> 3 & 0x7;
    instruction += 'R' + std::to_string(rx);
    uint8_t ry = machine_code[line] & 0x7;
    instruction += ',';
    instruction += " R" + std::to_string(ry);
    program.push_back(instruction);
  }

  return program;
}
