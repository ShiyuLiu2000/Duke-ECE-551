#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

int main(void) {
  std::map<std::string, size_t> values;
  std::string v1("pastry");
  values[v1] = 1;
  std::cout << values[v1];
  return EXIT_SUCCESS;
}
