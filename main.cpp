#include "assembler.h"
#include "cpu.h"
#include <cstdint>

int main() {
  two_b_completed cpu;

  std::vector<std::string> test = {
      "NAND R4, R1", "NAND R4, R4", "ADDEQ R4, R2", "NAND R4, R3",
      "NAND R2, R4", "NAND R4, R3", "NAND R4, R2",
  };
  two_b_completed_assembler assembler;
  std::vector<uint8_t> program = assembler.assemble(test);
  cpu.read_program(program);

  cpu.step();

  return 0;
}
