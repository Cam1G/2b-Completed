# 2b-Completed
A CPU architecture that only has 4 instructions and is still Turing complete. This project contains an emulator for the CPU an assembler and a disassembler. This architecture is highly inefficient and is just an experiment to see if a 4 instruction CPU would be possible. 

## Table of Contents
- [Installation](#installation)
- [Features](#features)
- [Tricks](#tricks)

## Installation
```
git clone https://github.com/Cam1G/2b-completed
cd 2b-completed
make
```

## Features

**Registers**

The registers are 8 bits in size.

Register 0 is the program counter.

Register 1 contains 0.

Register 2 - 7 constains powers of 2 to make writing program easier.

**Memory**

The registers can address 256 bytes of memory so I implemented memory banking with address 0xFF being the memory address that controls which bank the CPU is using. To get an output from the CPU you write to the byte out address which is 0xFE. With 256 banks this gives 65536 addressable memory locations in total. 

**LDST** - rx, [ry]

LDST (Load-store) works by taking the value in register x and swapping it with the value in the memory address stored in register y.

**NAND** - rx, ry

NAND performed a NAND on ry and puts the result in rx.

**CMP** - rx, ry

CMP (Compare) is used to set a status flag in the CPU which represents if the two numbers compared are the same.

**ADDEQ** - rx, ry

ADDEQ (ADD if Equal To) if the status flag is true then add the two numbers and store the value in rx otherwise do nothing


## Tricks

To force an ADDEQ to add any two numbers if the flag is currently 0.

```
CMP RX, RX
ADDEQ RX, RY
```

We know RX == RX so ADDEQ will always work after this CMP.

As LDST is one instruction is hard copy values to multiple registers . The way to do this using our assembly is

```
NAND RX, R1
NAND RX, RX
ADDEQ RX, RY
```

As we know R1 is 0 NAND RX turns it into 0b11111111 and NAND-ed with itself makes 0 which you can add the value in the register you want to copy to RX.

