#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>  // std::ifstream

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream file(fname, std::ios_base::binary);
  uint64_t * ans = new uint64_t[257]();
  char c;
  while (file.get(c).good()) {
    unsigned int index = static_cast<unsigned char>(c);
    ans[index]++;
  }
  ans[256] = 1;
  file.close();
  return ans;
}
