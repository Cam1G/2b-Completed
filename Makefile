CXX = clang++
CXXFLAGS = -I.
DEPS = cpu.h mmu.h assembler.h disassembler.h

2b-Completed: main.o cpu.o mmu.o assembler.o disassembler.o
	$(CXX) -o 2b-Completed main.o cpu.o mmu.o assembler.o disassembler.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o 2b-Completed
