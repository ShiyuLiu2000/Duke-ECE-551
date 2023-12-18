#include <cstdlib>
#include <iostream>
#include <string>

int main() {
  std::string s("0123456789");
  std::string s1 = s.substr(0, 3);
  size_t ind = s.find_first_of('4');
  std::string s2 = s.substr(ind, s.size() - 1);
  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
  return EXIT_SUCCESS;
}
