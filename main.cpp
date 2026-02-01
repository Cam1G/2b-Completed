#include "cpu.h"

int main() {
  two_b_completed cpu;

  std::vector<uint8_t> program = {
      // Copy R2 to R4
      0b01'100'001, // NAND R4, R1
      0b01'100'100, // NAND R4, R4
      0b11'100'010, // ADDEQ R4, R2

      0b01'100'011, // NAND R4, R3
      0b01'010'100, // NAND R2, R4
      0b01'011'100, // NAND R4, R3
      0b01'010'011, // NAND R4, R2
  };

  cpu.read_program(program);

  return 0;
}
