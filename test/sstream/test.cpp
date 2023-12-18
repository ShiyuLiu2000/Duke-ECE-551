#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char ** argv) {
  std::stringstream s;
  std::ifstream myFile(argv[1]);
  std::string line;
  while (std::getline(myFile, line).good()) {
    s << line << "\n";
  }
  myFile.close();
  std::cout << s.str();
  return EXIT_SUCCESS;
}
