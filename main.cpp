#include "rv32i.h"
#include <bitset>
#include <fstream>
#include <iostream>
#include <sstream>
#include <type_traits>


void processRType(std::string line, const Instruction *instruction);
void processIType(std::string line, const Instruction *instruction);
void processSType(std::string line, const Instruction *instruction);
void processBType(std::string line, const Instruction *instruction);
void processUType(std::string line, const Instruction *instruction);
void processJType(std::string line, const Instruction *instruction);

// Global map to store label addresses
static std::unordered_map<std::string, int32_t> SymbolTable;
int PC;

int main() {
  // The filename to read
  std::string filename = "add_shift.s";

  // Open the file
  std::ifstream inputFile(filename);

  // Check if the file opened successfully
  if (!inputFile.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return 1;
  }

  // Read and print line by line
  std::string line;  // Create the base string object
  std::string token; // create base toekn
  int lineNum = 0;
  while (std::getline(inputFile, line)) {

    std::cout << lineNum << ": \t|";
    std::cout << line;
    // for (char c : line) {
    // 	std::cout << c << std::endl;
    // }
    lineNum++;

    // Here we should have it such that it check what type of line it is:
    // the types are:
    //	Function (ie main:)
    //	instruction (add)
    //	comment (#)
    //	and for now, unknown
    // Let start with creating
    // we should use the hader file for doing the following, checking if the
    // header variable exists, and if so we know it is an instruction, and from
    // there we should return back the struct of that object
    //		IE: for line 21, it is lui, which is an instruction, and should
    // return (U, 011 0111, 2) (type, op code, number of oprerands)
    //
    //		how do we do a lookup on the header file for checking to see if
    // it exists.

    // first things first, lets get the tokens for now

    std::stringstream ss(line);
    ss >> token;

    // std::cout << token<< '\t';

    if (token == "#") {
      // std::cout << "\tit was a comment"  << std::endl;

    } else {
      const Instruction *instruction = getInstructions(token);

      if (instruction != nullptr) {
        // std::cout << "Found the following: ";
        // std::cout << instruction->name << '\t';
        // std::cout << instruction->opcode<< '\t';
        // std::cout <<  typeToString(instruction->type)<< '\t';
        // std::cout << instruction->funct3 << '\t';
        // std::cout << instruction->funct7 << '\t';

        // this means we found a proper instructions

        switch (instruction->type) {

        case InstructionType::R:
          processRType(line, instruction);
          break;
        case InstructionType::I:
          processIType(line, instruction);
          break;
        case InstructionType::S:
          processSType(line, instruction);
          break;
        case InstructionType::B:
          processBType(line, instruction);
          break;
        case InstructionType::U:
          processUType(line, instruction);
          break;
        case InstructionType::J:
          processJType(line, instruction);
          break;
        default:
          std::cout << "defaulting";
          break;
        }
      }
    }
    std::cout << std::endl;
    // now we do checks to see what type of thing it is
  }

  // Close the file (optional as destructor closes it, but good practice)
  inputFile.close();

  return 0;
}

std::string registerToBinary(const std::string registerName) {
  std::unordered_map<std::string, int> registerMap = {
      {"zero", 0}, {"ra", 1},  {"sp", 2},  {"gp", 3},  {"tp", 4},  {"t0", 5},
      {"t1", 6},   {"t2", 7},  {"s0", 8}, // s0 or fp
      {"s1", 9},   {"a0", 10}, {"a1", 11}, {"a2", 12}, {"a3", 13}, {"a4", 14},
      {"a5", 15},  {"a6", 16}, {"a7", 17}, {"s2", 18}, {"s3", 19}, {"s4", 20},
      {"s5", 21},  {"s6", 22}, {"s7", 23}, {"s8", 24}, {"s9", 25}, {"s10", 26},
      {"s11", 27}, {"t3", 28}, {"t4", 29}, {"t5", 30}, {"t6", 31},

  };

  int binary = registerMap[registerName];
  return std::bitset<5>(binary).to_string();
}

void processRType(std::string line, const Instruction *instruction) {
  // R = funct 7 + rs2 + rs1 + funct3 + rd + opcode
  std::stringstream ss(line);
  std::string token;
  std::string rd;
  std::string rs1;
  std::string rs2;
  std::string funct7;
  std::string funct3;
  std::string opcode;

  // parse lin
  ss >> token; // gets instruction name
  ss >> rd;
  if (!rd.empty() && rd.back() == ',') // remove commas
    rd.pop_back();

  ss >> rs1;
  if (!rs1.empty() && rs1.back() == ',')
    rs1.pop_back();

  ss >> rs2;
  if (!rs2.empty() && rs2.back() == ',')
    rs2.pop_back();

  // get binary registers
  std::string binary_rd = registerToBinary(rd);
  std::string binary_rs1 = registerToBinary(rs1);
  std::string binary_rs2 = registerToBinary(rs2);

  // turn the functs into binary using bitset
  std::string binary_funct7 = std::bitset<7>(instruction->funct7).to_string();
  std::string binary_funct3 = std::bitset<3>(instruction->funct3).to_string();
  std::string binary_opcode = std::bitset<7>(instruction->opcode).to_string();

  // // result = funct7 + rs2 + rs1 + funct3 + rd + opcode;
  // std::cout << std::endl;
  // std::cout << "Printing important details for this line\n\t";
  // std::cout << rd + "\n\t" + rs1 + "\n\t" + rs2 << std::endl;

  // get final result
  std::string binaryResult = binary_funct3 + binary_rs2 + binary_rs1 +
                             binary_funct7 + binary_rd + binary_opcode;
}

void processIType(std::string line, const Instruction *instruction) {
  // I = imm + rs1 + funct + rd + opcode
}
void processSType(std::string line, const Instruction *instruction) {
  // S =imm + rs2 + rs1 + funct3 + imm + opcode
}

void processBType(std::string line, const Instruction *instruction) {
  
  // B = imm12 + imm10_5 + rs2 + rs1 + funct3 + imm4_1 + imm11 + opcode
  std::stringstream ss(line);
  std::string token;
  std::string rs1;
  std::string rs2;
  std::string label;

  // Parse line: beq rs1, rs2, label
  ss >> token; // gets instruction name (beq, bne, etc.)
  ss >> rs1;
  if (!rs1.empty() && rs1.back() == ',')
    rs1.pop_back();

  ss >> rs2;
  if (!rs2.empty() && rs2.back() == ',')
    rs2.pop_back();

  ss >> label;

  // Collect rs1 and rs2 register values
  const Register* reg1 = getRegister(rs1);
  uint32_t rs1_b = 0;
  if (reg1 != nullptr) {
    rs1_b = reg1->address;
  } else {
    std::cout << "Register not found: " << rs1 << "\n";
  }
  const Register* reg2 = getRegister(rs2);
  uint32_t rs2_b = 0;
  if (reg2 != nullptr) {
    rs2_b = reg2->address;
  } else {
    std::cout << "Register not found: " << rs2 << "\n";
  }

  // Get funct3 from instruction struct
  uint32_t funct3_b = instruction->funct3;

  // Get Label address from global map
  auto it = SymbolTable.find(label);
  uint32_t label_b = 0;
  if (it != SymbolTable.end()) {
    label_b = it->second;
  } else {
    std::cout << "Label not found: " << label << "\n";
  }

  // Compute offset (label address - PC), then >> 1
  int32_t offset = label_b - PC;
  int32_t imm = offset >> 1;

  // Extract immediate fields
  uint32_t imm12   = (imm >> 12) & 0x1;
  uint32_t imm11   = (imm >> 11) & 0x1;
  uint32_t imm10_5 = (imm >> 5)  & 0x3F;
  uint32_t imm4_1  = (imm >> 1)  & 0xF;

  // Build instruction: imm12[31] + imm10_5[30:25] + rs2[24:20] + rs1[19:15] + funct3[14:12] + imm4_1[11:8] + imm11[7] + opcode[6:0]
  uint32_t inst = 0;
  inst |= (imm12   << 31);
  inst |= (imm10_5 << 25);
  inst |= (rs2_b   << 20);
  inst |= (rs1_b   << 15);
  inst |= (funct3_b << 12);
  inst |= (imm4_1  << 8);
  inst |= (imm11   << 7);
  inst |= instruction->opcode; // B-type opcode is 0x63 (0b1100011)

  // Output results
  std::string binInst = std::bitset<32>(inst).to_string();
  std::string hexInst = binaryToHex(inst);

  std::cout << "\tBinary: " << binInst << " | Hex: " << hexInst << std::endl;
}

void processUType(std::string line, const Instruction *instruction) {
  // U = imm + rd + opcodew
}
void processJType(std::string line, const Instruction *instruction) {
  // J = imm + rd + opcode
}
