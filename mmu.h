#ifndef MMU_H
#define MMU_H

#include <array>
#include <cstdint>

constexpr int BANK_SIZE = 256;
constexpr int BANK_COUNT = 256;

class two_b_completed_mmu {
private:
  uint8_t current_bank = 0;
  std::array<uint8_t, BANK_SIZE * BANK_COUNT> memory = {0};

public:
  two_b_completed_mmu();
  uint8_t read(uint8_t address);
  void write(uint8_t address, uint8_t data);
};

#endif
