#ifndef CPU_H
#define CPU_H

#include <array>
#include <cstdint>
#include <stdint.h>
#include <vector>

constexpr int PC_REGISTER = 0;

class two_b_completed {
private:
  bool status_flag;
  std::array<uint8_t, 8> registers = {0, 0, 1, 2, 4, 8, 16, 64};
  std::array<uint8_t, 256> memory = {0};

public:
  two_b_completed();
  void read_program(std::vector<uint8_t> &program);
  void step();
};

#endif
