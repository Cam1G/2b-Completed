#include "mmu.h"
#include <cstdint>
#include <iostream>

two_b_completed_mmu::two_b_completed_mmu() {}

uint8_t two_b_completed_mmu::read(uint8_t address) {
  return memory[(current_bank * BANK_SIZE) + address];
}

void two_b_completed_mmu::write(uint8_t address, uint8_t data) {
  if (address == BANK_SWITCHING_ADDRESS)
    current_bank = data;
  else if (address == BYTE_OUT_ADDRESS)
    std::cout << +data << "\n";
  else
    memory[(current_bank * BANK_SIZE) + address] = data;
}
