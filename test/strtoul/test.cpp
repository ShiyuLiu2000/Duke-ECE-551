#include <cstdlib>
#include <iostream>
#include <string>

int main() {
  std::string s1("1Hello World!\n");
  std::string s2(" 123");
  std::string s3("a123");
  char * endptr1 = NULL;
  char * endptr2 = NULL;
  char * endptr3 = NULL;
  size_t a = strtoul(s1.c_str(), &endptr1, 10);
  size_t b = strtoul(s2.c_str(), &endptr2, 10);
  size_t c = strtoul(s3.c_str(), &endptr3, 10);
  std::cout << a << " " << b << " " << c << "\n";
  if (*endptr3 != '\0') {
    std::cout << "I'm super sleepy\n";
  }
  return EXIT_SUCCESS;
}
