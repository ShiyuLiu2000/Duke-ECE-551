#include <algorithm>  // std::sort
#include <cstdlib>    // EXIT_SUCCESS
#include <fstream>    // std::ifstream
#include <iostream>   // std::istream
#include <vector>     // std::vector

// read lines from file stream and store them into vector
std::vector<std::string> getFileLines(std::istream & stream) {
  std::vector<std::string> ans;
  std::string line;
  while (std::getline(stream, line).good()) {
    ans.push_back(line);
  }
  return ans;
}

// sort lines using std::sort
void sortLines(std::vector<std::string> & lines) {
  std::sort(lines.begin(), lines.end());
}

// print lines
// prefer const reference to pass by value to avoid redundant object copying
void printLines(const std::vector<std::string> & lines) {
  for (size_t i = 0; i < lines.size(); i++) {
    std::cout << lines[i] << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::vector<std::string> lines = getFileLines(std::cin);
    sortLines(lines);
    printLines(lines);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream fileStream(argv[i]);
      if (!fileStream.good()) {
        std::cerr << "Cannot open file: " << argv[i] << std::endl;
        exit(EXIT_FAILURE);  // don't forget to exit explicitly!!
      }
      std::vector<std::string> lines = getFileLines(fileStream);
      sortLines(lines);
      printLines(lines);
      fileStream.close();
    }
  }
  return EXIT_SUCCESS;
}
