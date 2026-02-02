#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "rv32i.h"
#include <iostream>
#include <type_traits>


void processRType(std::string line, const Instruction* instruction);
void processIType(std::string line, const Instruction* instruction);
void processSType(std::string line, const Instruction* instruction);
void processBType(std::string line, const Instruction* instruction);
void processUType(std::string line, const Instruction* instruction);
void processJType(std::string line, const Instruction* instruction);


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
	std::string line; // Create the base string object
	std::string token;	// create base toekn
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
		// we should use the hader file for doing the following, checking if the header variable exists, and if so we know it is an instruction, and from there we should return back the struct of that object
		//		IE: for line 21, it is lui, which is an instruction, and should return (U, 011 0111, 2) (type, op code, number of oprerands)
		//		
		//		how do we do a lookup on the header file for checking to see if it exists.

		// first things first, lets get the tokens for now

		std::stringstream ss(line);
		ss >> token;

		// std::cout << token<< '\t';

		


		if(token == "#")
		{
			// std::cout << "\tit was a comment"  << std::endl;
 
		}
		else
		{
			const Instruction* instruction = getInstructions(token);

			if(instruction != nullptr){
				// std::cout << "Found the following: ";
				// std::cout << instruction->name << '\t';
				// std::cout << instruction->opcode<< '\t';
				// std::cout <<  typeToString(instruction->type)<< '\t';
				// std::cout << instruction->funct3 << '\t';
				// std::cout << instruction->funct7 << '\t';

				// this means we found a proper instructions

				switch(instruction->type){

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

void processRType(std::string line, const Instruction* instruction)
{
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
	ss >> rd; // gets rd
	ss >> rs1; 		// gets rs1
	ss >> rs2;		// gets rs2
	funct7 = instruction->funct7;
	funct3 = instruction->funct3;
	




	// std::string result;

	// result = funct7 + rs2 + rs1 + funct3 + rd + opcode;
	std::cout << std::endl;
	std::cout << "Printing important details for this line\n\t";
	std::cout << rd + "\n\t" + rs1 + "\n\t" + rs2 << std::endl;


	// while(ss >> token){
	// 	std::cout << token << std::endl;
	// }

	//std::cout << result << std::endl;
	
}

void processIType(std::string line, const Instruction* instruction)
{
	// I = imm + rs1 + funct + rd + opcode
	
}
void processSType(std::string line, const Instruction* instruction)
{
	// S =imm + rs2 + rs1 + funct3 + imm + opcode
	
}
void processBType(std::string line, const Instruction* instruction)
{
	// B = imm + rs2 + rs1 + funct3 + imm + opcode
}
void processUType(std::string line, const Instruction* instruction)
{
	// U = imm + rd + opcodew
}
void processJType(std::string line, const Instruction* instruction)
{
	// J = imm + rd + opcode	
}

