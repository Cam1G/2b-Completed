#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class two_b_completed_disassembler {
private:
  static const std::unordered_map<uint8_t, std::string> bin_to_opcodes;

public:
  two_b_completed_disassembler();
  std::vector<std::string> disassemble(std::vector<uint8_t> &machine_code);
};

#endif
