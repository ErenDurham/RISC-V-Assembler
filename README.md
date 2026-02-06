# Project: RISC-V Assembler Implementation

## Overview
This project implements a fully functional assembler for the RISC-V RV32I instruction set architecture (ISA). The software automates the translation of assembly source code (`.s`) into machine-readable binary (`.bin`) and hexadecimal text (`.hex.txt`) formats. It features a robust parsing engine capable of handling memory initialization, label resolution, and standard assembly directives.

## Core Functionality

### 1. Instruction Translation
The assembler parses and converts all standard RV32I instruction formats (**R, I, S, B, U, J**) into their 32-bit binary equivalents.

The translation logic decomposes instructions into their constituent fields—opcode, destination register (`rd`), function codes (`funct3`, `funct7`), source registers (`rs1`, `rs2`), and immediates—and concatenates them based on the specific instruction format.

#### Translation Example: `addi` (I-Type)
For the instruction `addi t0, x0, 5`:

* **Type:** I-Type (Immediate Arithmetic)
* **Components:**
    * Immediate: `5`
    * Source Register (`rs1`): `x0`
    * Destination Register (`rd`): `t0`
    * Function: `add immediate`

**Bitwise Decomposition:**

| Field | Value | Binary Representation |
| :--- | :--- | :--- |
| **imm[11:0]** | `0x005` | `0000 0000 0101` |
| **rs1[4:0]** | `0x00` | `0000 0` |
| **funct3[2:0]** | `0x0` | `000` |
| **rd[4:0]** | `0x05` | `0010 1` |
| **opcode[6:0]** | `0x13` | `001 0011` |

**Result:**

Hex: 0x00500293

Binary: 00000000010100000000001010010011

---

## Interface and Usage

### Command Line Interface
The tool is designed to be invoked via the command line, accepting a base path and the target assembly file.
