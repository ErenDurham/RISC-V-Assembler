#include <fstream>
#include <iostream>
#include <string>


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
  std::string line;
  while (std::getline(inputFile, line)) {
    std::cout << line << std::endl;
  }

  // Close the file (optional as destructor closes it, but good practice)
  inputFile.close();

  return 0;
}
