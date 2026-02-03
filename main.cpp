#include "assembler.h"
#include "cpu.h"
#include "disassembler.h"
#include "mmu.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Incorrect number of arguments";
    return 1;
  }

  std::string command = argv[1];
  std::string file_name = argv[2];

  if (command == "dis") {
    std::ifstream machine_code_file(file_name, std::ios::binary);

    if (!machine_code_file.is_open()) {
      std::cout << "File doesn't exist \n";
      return 1;
    }

    // Reads binary file into machine_code vector
    char current_instruction;
    std::vector<uint8_t> machine_code;
    while ((current_instruction = machine_code_file.get()) != EOF) {
      machine_code.push_back((uint8_t)current_instruction);
    }
    machine_code_file.close();

    two_b_completed_disassembler disassembler;
    std::vector<std::string> program = disassembler.disassemble(machine_code);
    // Creates new text file with the disassembled program
    std::string new_file_name = file_name.substr(0, file_name.find("."));
    std::ofstream out(new_file_name + ".2b");
    for (const std::string &line : program)
      out << line << "\n";
    out.close();

  } else if (command == "asm" || command == "emu") {
    // Reads program file into the program vector
    std::vector<std::string> program;
    std::ifstream program_file(file_name);

    if (!program_file.is_open()) {
      std::cout << "File doesn't exist \n";
      return 1;
    }

    std::string current_line;
    while (std::getline(program_file, current_line)) {
      program.push_back(current_line);
    }
    program_file.close();

    two_b_completed_assembler assembler;
    std::vector<uint8_t> machine_code = assembler.assemble(program);

    if (command == "asm") {
      // Writes the assembled program to a binary file
      std::string new_file_name = file_name.substr(0, file_name.find("."));
      std::ofstream out(new_file_name + ".bin", std::ios::binary);
      out.write((char *)machine_code.data(), machine_code.size());
      out.close();
    } else if (command == "emu") {
      two_b_completed cpu;
      cpu.read_program(machine_code);
      // Since there is no halt instruction we just run the program to the end
      // of the bank 0
      for (int i = 0; i < BANK_SIZE; i++)
        cpu.step();
    }
  } else {
    std::cout << "Incorrect command";
    return 1;
  }

  return 0;
}
