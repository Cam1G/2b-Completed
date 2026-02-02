#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class two_b_completed_assembler {
private:
  static const std::unordered_map<std::string, uint8_t> opcodes_to_bin;

public:
  two_b_completed_assembler();
  std::vector<uint8_t> assemble(std::vector<std::string> &program);
};

#endif
